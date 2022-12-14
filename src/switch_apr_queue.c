/* Copyright 2000-2005 The Apache Software Foundation or its licensors, as
 * applicable.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <switch.h>
#include <fspr.h>
#include <fspr_thread_mutex.h>
#include <fspr_thread_cond.h>

/* 
 * define this to get debug messages
 *
#define QUEUE_DEBUG
 */

struct switch_apr_queue_t {
    void              **data;
    unsigned int        nelts; /**< # elements */
    unsigned int        in;    /**< next empty location */
    unsigned int        out;   /**< next filled location */
    unsigned int        bounds;/**< max size of queue */
    unsigned int        full_waiters;
    unsigned int        empty_waiters;
    fspr_thread_mutex_t *one_big_mutex;
    fspr_thread_cond_t  *not_empty;
    fspr_thread_cond_t  *not_full;
    int                 terminated;
};

typedef struct switch_apr_queue_t switch_apr_queue_t;

#ifdef QUEUE_DEBUG
static void Q_DBG(char*msg, switch_apr_queue_t *q) {
    fprintf(stderr, "%ld\t#%d in %d out %d\t%s\n", 
                    apr_os_thread_current(),
                    q->nelts, q->in, q->out,
                    msg
                    );
}
#else
#define Q_DBG(x,y) 
#endif

/**
 * Detects when the switch_apr_queue_t is full. This utility function is expected
 * to be called from within critical sections, and is not threadsafe.
 */
#define apr_queue_full(queue) ((queue)->nelts == (queue)->bounds)

/**
 * Detects when the switch_apr_queue_t is empty. This utility function is expected
 * to be called from within critical sections, and is not threadsafe.
 */
#define apr_queue_empty(queue) ((queue)->nelts == 0)

/**
 * Callback routine that is called to destroy this
 * switch_apr_queue_t when its pool is destroyed.
 */
static fspr_status_t queue_destroy(void *data) 
{
    switch_apr_queue_t *queue = data;

    /* Ignore errors here, we can't do anything about them anyway. */

    fspr_thread_cond_destroy(queue->not_empty);
    fspr_thread_cond_destroy(queue->not_full);
    fspr_thread_mutex_destroy(queue->one_big_mutex);

    return APR_SUCCESS;
}

/**
 * Initialize the switch_apr_queue_t.
 */
fspr_status_t switch_apr_queue_create(switch_apr_queue_t **q, unsigned int queue_capacity, fspr_pool_t *a)
{
    fspr_status_t rv;
    switch_apr_queue_t *queue;
    queue = fspr_palloc(a, sizeof(switch_apr_queue_t));
    *q = queue;

    /* nested doesn't work ;( */
    rv = fspr_thread_mutex_create(&queue->one_big_mutex,
                                 APR_THREAD_MUTEX_UNNESTED,
                                 a);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    rv = fspr_thread_cond_create(&queue->not_empty, a);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    rv = fspr_thread_cond_create(&queue->not_full, a);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    /* Set all the data in the queue to NULL */
    queue->data = fspr_palloc(a, queue_capacity * sizeof(void*));
	if (!queue->data) return APR_ENOMEM;
	memset(queue->data, 0, queue_capacity * sizeof(void*));
    queue->bounds = queue_capacity;
    queue->nelts = 0;
    queue->in = 0;
    queue->out = 0;
    queue->terminated = 0;
    queue->full_waiters = 0;
    queue->empty_waiters = 0;

    fspr_pool_cleanup_register(a, queue, queue_destroy, fspr_pool_cleanup_null);

    return APR_SUCCESS;
}

/**
 * Push new data onto the queue. Blocks if the queue is full. Once
 * the push operation has completed, it signals other threads waiting
 * in apr_queue_pop() that they may continue consuming sockets.
 */
fspr_status_t switch_apr_queue_push(switch_apr_queue_t *queue, void *data)
{
    fspr_status_t rv;

    if (queue->terminated) {
        return APR_EOF; /* no more elements ever again */
    }

    rv = fspr_thread_mutex_lock(queue->one_big_mutex);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    if (apr_queue_full(queue)) {
        if (!queue->terminated) {
            queue->full_waiters++;
            rv = fspr_thread_cond_wait(queue->not_full, queue->one_big_mutex);
            queue->full_waiters--;
            if (rv != APR_SUCCESS) {
                fspr_thread_mutex_unlock(queue->one_big_mutex);
                return rv;
            }
        }
        /* If we wake up and it's still empty, then we were interrupted */
        if (apr_queue_full(queue)) {
            Q_DBG("queue full (intr)", queue);
            rv = fspr_thread_mutex_unlock(queue->one_big_mutex);
            if (rv != APR_SUCCESS) {
                return rv;
            }
            if (queue->terminated) {
                return APR_EOF; /* no more elements ever again */
            }
            else {
                return APR_EINTR;
            }
        }
    }

    queue->data[queue->in] = data;
    queue->in = (queue->in + 1) % queue->bounds;
    queue->nelts++;

    if (queue->empty_waiters) {
        Q_DBG("sig !empty", queue);
        rv = fspr_thread_cond_signal(queue->not_empty);
        if (rv != APR_SUCCESS) {
            fspr_thread_mutex_unlock(queue->one_big_mutex);
            return rv;
        }
    }

    rv = fspr_thread_mutex_unlock(queue->one_big_mutex);
    return rv;
}

/**
 * Push new data onto the queue. Blocks if the queue is full. Once
 * the push operation has completed, it signals other threads waiting
 * in apr_queue_pop() that they may continue consuming sockets.
 */
fspr_status_t switch_apr_queue_trypush(switch_apr_queue_t *queue, void *data)
{
    fspr_status_t rv;

    if (queue->terminated) {
        return APR_EOF; /* no more elements ever again */
    }

    rv = fspr_thread_mutex_lock(queue->one_big_mutex);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    if (apr_queue_full(queue)) {
        fspr_thread_mutex_unlock(queue->one_big_mutex);
        return APR_EAGAIN;
    }
    
    queue->data[queue->in] = data;
    queue->in = (queue->in + 1) % queue->bounds;
    queue->nelts++;

    if (queue->empty_waiters) {
        Q_DBG("sig !empty", queue);
        rv  = fspr_thread_cond_signal(queue->not_empty);
        if (rv != APR_SUCCESS) {
            fspr_thread_mutex_unlock(queue->one_big_mutex);
            return rv;
        }
    }

    rv = fspr_thread_mutex_unlock(queue->one_big_mutex);
    return rv;
}

/**
 * not thread safe
 */
unsigned int switch_apr_queue_size(switch_apr_queue_t *queue) {
    return queue->nelts;
}

/**
 * Retrieves the next item from the queue. If there are no
 * items available, it will block until one becomes available.
 * Once retrieved, the item is placed into the address specified by
 * 'data'.
 */
fspr_status_t switch_apr_queue_pop(switch_apr_queue_t *queue, void **data)
{
    fspr_status_t rv;

    if (queue->terminated) {
        return APR_EOF; /* no more elements ever again */
    }

    rv = fspr_thread_mutex_lock(queue->one_big_mutex);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    /* Keep waiting until we wake up and find that the queue is not empty. */
    if (apr_queue_empty(queue)) {
        if (!queue->terminated) {
            queue->empty_waiters++;
            rv = fspr_thread_cond_wait(queue->not_empty, queue->one_big_mutex);
            queue->empty_waiters--;
            if (rv != APR_SUCCESS) {
                fspr_thread_mutex_unlock(queue->one_big_mutex);
                return rv;
            }
        }
        /* If we wake up and it's still empty, then we were interrupted */
        if (apr_queue_empty(queue)) {
            Q_DBG("queue empty (intr)", queue);
            rv = fspr_thread_mutex_unlock(queue->one_big_mutex);
            if (rv != APR_SUCCESS) {
                return rv;
            }
            if (queue->terminated) {
                return APR_EOF; /* no more elements ever again */
            }
            else {
                return APR_EINTR;
            }
        }
    } 

    *data = queue->data[queue->out];
    queue->nelts--;

    queue->out = (queue->out + 1) % queue->bounds;
    if (queue->full_waiters) {
        Q_DBG("signal !full", queue);
        rv = fspr_thread_cond_signal(queue->not_full);
        if (rv != APR_SUCCESS) {
            fspr_thread_mutex_unlock(queue->one_big_mutex);
            return rv;
        }
    }

    rv = fspr_thread_mutex_unlock(queue->one_big_mutex);
    return rv;
}

/**
 * Retrieves the next item from the queue. If there are no
 * items available, it will block until one becomes available, or 
 * until timeout is elapsed. Once retrieved, the item is placed into
 * the address specified by'data'.
 */
fspr_status_t switch_apr_queue_pop_timeout(switch_apr_queue_t *queue, void **data, fspr_interval_time_t timeout)
{
    fspr_status_t rv;

    if (queue->terminated) {
        return APR_EOF; /* no more elements ever again */
    }

    rv = fspr_thread_mutex_lock(queue->one_big_mutex);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    /* Keep waiting until we wake up and find that the queue is not empty. */
    if (apr_queue_empty(queue)) {
        if (!queue->terminated) {
            queue->empty_waiters++;
            rv = fspr_thread_cond_timedwait(queue->not_empty, queue->one_big_mutex, timeout);
            queue->empty_waiters--;
			/* In the event of a timemout, APR_TIMEUP will be returned */
            if (rv != APR_SUCCESS) {
                fspr_thread_mutex_unlock(queue->one_big_mutex);
                return rv;
            }
        }
        /* If we wake up and it's still empty, then we were interrupted */
        if (apr_queue_empty(queue)) {
            Q_DBG("queue empty (intr)", queue);
            rv = fspr_thread_mutex_unlock(queue->one_big_mutex);
            if (rv != APR_SUCCESS) {
                return rv;
            }
            if (queue->terminated) {
                return APR_EOF; /* no more elements ever again */
            }
            else {
                return APR_EINTR;
            }
        }
    } 

    *data = queue->data[queue->out];
    queue->nelts--;

    queue->out = (queue->out + 1) % queue->bounds;
    if (queue->full_waiters) {
        Q_DBG("signal !full", queue);
        rv = fspr_thread_cond_signal(queue->not_full);
        if (rv != APR_SUCCESS) {
            fspr_thread_mutex_unlock(queue->one_big_mutex);
            return rv;
        }
    }

    rv = fspr_thread_mutex_unlock(queue->one_big_mutex);
    return rv;
}


/**
 * Retrieves the next item from the queue. If there are no
 * items available, return APR_EAGAIN.  Once retrieved,
 * the item is placed into the address specified by 'data'.
 */
fspr_status_t switch_apr_queue_trypop(switch_apr_queue_t *queue, void **data)
{
    fspr_status_t rv;

    if (queue->terminated) {
        return APR_EOF; /* no more elements ever again */
    }

    rv = fspr_thread_mutex_lock(queue->one_big_mutex);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    if (apr_queue_empty(queue)) {
        fspr_thread_mutex_unlock(queue->one_big_mutex);
        return APR_EAGAIN;
    } 

    *data = queue->data[queue->out];
    queue->nelts--;

    queue->out = (queue->out + 1) % queue->bounds;
    if (queue->full_waiters) {
        Q_DBG("signal !full", queue);
        rv = fspr_thread_cond_signal(queue->not_full);
        if (rv != APR_SUCCESS) {
            fspr_thread_mutex_unlock(queue->one_big_mutex);
            return rv;
        }
    }

    rv = fspr_thread_mutex_unlock(queue->one_big_mutex);
    return rv;
}

fspr_status_t switch_apr_queue_interrupt_all(switch_apr_queue_t *queue)
{
    fspr_status_t rv;
    Q_DBG("intr all", queue);    
    if ((rv = fspr_thread_mutex_lock(queue->one_big_mutex)) != APR_SUCCESS) {
        return rv;
    }
    fspr_thread_cond_broadcast(queue->not_empty);
    fspr_thread_cond_broadcast(queue->not_full);

    if ((rv = fspr_thread_mutex_unlock(queue->one_big_mutex)) != APR_SUCCESS) {
        return rv;
    }

    return APR_SUCCESS;
}

fspr_status_t switch_apr_queue_term(switch_apr_queue_t *queue)
{
    fspr_status_t rv;

    if ((rv = fspr_thread_mutex_lock(queue->one_big_mutex)) != APR_SUCCESS) {
        return rv;
    }

    /* we must hold one_big_mutex when setting this... otherwise,
     * we could end up setting it and waking everybody up just after a 
     * would-be popper checks it but right before they block
     */
    queue->terminated = 1;
    if ((rv = fspr_thread_mutex_unlock(queue->one_big_mutex)) != APR_SUCCESS) {
        return rv;
    }
    return switch_apr_queue_interrupt_all(queue);
}

