/* Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "fspr.h"
#include "fspr_private.h"
#include "fspr_general.h"
#include "fspr_strings.h"
#include "fspr_arch_thread_rwlock.h"
#include "fspr_portable.h"

static fspr_status_t thread_rwlock_cleanup(void *data)
{
    fspr_thread_rwlock_t *rwlock = (fspr_thread_rwlock_t *)data;

    NXRwLockFree (rwlock->rwlock);
    return APR_SUCCESS;
} 

APR_DECLARE(fspr_status_t) fspr_thread_rwlock_create(fspr_thread_rwlock_t **rwlock,
                                                   fspr_pool_t *pool)
{
    fspr_thread_rwlock_t *new_rwlock = NULL;
   
	NXHierarchy_t hierarchy = 1;   //for libc NKS NXRwLockAlloc
	NXLockInfo_t *info;			   //for libc NKS NXRwLockAlloc

    new_rwlock = (fspr_thread_rwlock_t *)fspr_pcalloc(pool, sizeof(fspr_thread_rwlock_t));
	
	if(new_rwlock ==NULL) {
        return APR_ENOMEM;
    }     
    new_rwlock->pool = pool;
    
    info = (NXLockInfo_t *)fspr_pcalloc(pool, sizeof(NXLockInfo_t));
    new_rwlock->rwlock = NXRwLockAlloc(hierarchy, info);
    if(new_rwlock->rwlock == NULL)
        return APR_ENOMEM;

    fspr_pool_cleanup_register(new_rwlock->pool, new_rwlock, thread_rwlock_cleanup,
                              fspr_pool_cleanup_null);
    *rwlock = new_rwlock;

    return APR_SUCCESS;
}

APR_DECLARE(fspr_status_t) fspr_thread_rwlock_rdlock(fspr_thread_rwlock_t *rwlock)
{
    NXRdLock(rwlock->rwlock);
    return APR_SUCCESS;
}

APR_DECLARE(fspr_status_t) fspr_thread_rwlock_tryrdlock(fspr_thread_rwlock_t *rwlock)
{
    if (!NXTryRdLock(rwlock->rwlock))
        return APR_EBUSY;
    return APR_SUCCESS;
}

APR_DECLARE(fspr_status_t) fspr_thread_rwlock_wrlock(fspr_thread_rwlock_t *rwlock)
{
    NXWrLock(rwlock->rwlock);
    return APR_SUCCESS;
}

APR_DECLARE(fspr_status_t) fspr_thread_rwlock_trywrlock(fspr_thread_rwlock_t *rwlock)
{
    if (!NXTryWrLock(rwlock->rwlock))
        return APR_EBUSY;
    return APR_SUCCESS;
}

APR_DECLARE(fspr_status_t) fspr_thread_rwlock_unlock(fspr_thread_rwlock_t *rwlock)
{
    NXRwUnlock(rwlock->rwlock);
    return APR_SUCCESS;
}

APR_DECLARE(fspr_status_t) fspr_thread_rwlock_destroy(fspr_thread_rwlock_t *rwlock)
{
    fspr_status_t stat;
    if ((stat = thread_rwlock_cleanup(rwlock)) == APR_SUCCESS) {
        fspr_pool_cleanup_kill(rwlock->pool, rwlock, thread_rwlock_cleanup);
        return APR_SUCCESS;
    }
    return stat;
}

APR_POOL_IMPLEMENT_ACCESSOR(thread_rwlock)

