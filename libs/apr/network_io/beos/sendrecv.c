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

#include "fspr_private.h"
#if BEOS_BONE /* BONE uses the unix code - woohoo */
#include "../unix/sendrecv.c"
#else
#include "fspr_arch_networkio.h"
#include "fspr_time.h"

static fspr_status_t wait_for_io_or_timeout(fspr_socket_t *sock, int for_read)
{
    struct timeval tv, *tvptr;
    fd_set fdset;
    int srv;

    do {
        FD_ZERO(&fdset);
        FD_SET(sock->socketdes, &fdset);
        if (sock->timeout < 0) {
            tvptr = NULL;
        }
        else {
            tv.tv_sec = sock->timeout / APR_USEC_PER_SEC;
            tv.tv_usec = sock->timeout % APR_USEC_PER_SEC;
            tvptr = &tv;
        }
        srv = select(sock->socketdes + 1,
            for_read ? &fdset : NULL,
            for_read ? NULL : &fdset, 
            NULL,
            tvptr);
            /* TODO - timeout should be smaller on repeats of this loop */
    } while (srv == -1 && errno == EINTR);

    if (srv == 0) {
        return APR_TIMEUP;
    }
    else if (srv < 0) {
        return errno;
    }
    return APR_SUCCESS;
}

#define SEND_WAIT APR_USEC_PER_SEC / 10

APR_DECLARE(fspr_status_t) fspr_socket_send(fspr_socket_t *sock, const char *buf,
                                          fspr_size_t *len)
{
    fspr_ssize_t rv;
	
    do {
        rv = send(sock->socketdes, buf, (*len), 0);
    } while (rv == -1 && errno == EINTR);

    if (rv == -1 && errno == EWOULDBLOCK && sock->timeout > 0) {
        fspr_int32_t snooze_val = SEND_WAIT;
        fspr_int32_t zzz = 0;  
        
        do {
            rv = send(sock->socketdes, buf, (*len), 0);
            if (rv == -1 && errno == EWOULDBLOCK){
                fspr_sleep (snooze_val);
                zzz += snooze_val;
                snooze_val += SEND_WAIT;
                /* have we passed our timeout value */
                if (zzz > (sock->timeout * APR_USEC_PER_SEC))
                    break;
            }
        } while (rv == -1 && (errno == EINTR || errno == EWOULDBLOCK));
    }
    if (rv == -1) {
        *len = 0;
        return errno;
    }
    (*len) = rv;

    return APR_SUCCESS;
}

APR_DECLARE(fspr_status_t) fspr_socket_recv(fspr_socket_t *sock, char *buf, 
                                          fspr_size_t *len)
{
    fspr_ssize_t rv;
   
    do {
        rv = recv(sock->socketdes, buf, (*len), 0);
    } while (rv == -1 && errno == EINTR);

    if (rv == -1 && errno == EWOULDBLOCK && sock->timeout > 0) {
        fspr_status_t arv = wait_for_io_or_timeout(sock, 1);
        if (arv != APR_SUCCESS) {
            *len = 0;
            return arv;
        }
        else {
            do {
                rv = recv(sock->socketdes, buf, (*len), 0);
            } while (rv == -1 && errno == EINTR);
        }
    }
    if (rv == -1) {
        (*len) = 0;
        return errno;
    }
    (*len) = rv;
    if (rv == 0)
        return APR_EOF;
    return APR_SUCCESS;
}

/* BeOS doesn't have writev for sockets so we use the following instead...
 */
APR_DECLARE(fspr_status_t) fspr_socket_sendv(fspr_socket_t * sock, 
                                           const struct iovec *vec,
                                           fspr_int32_t nvec, fspr_size_t *len)
{
    *len = vec[0].iov_len;
    return fspr_socket_send(sock, vec[0].iov_base, len);
}

APR_DECLARE(fspr_status_t) fspr_socket_sendto(fspr_socket_t *sock, 
                                            fspr_sockaddr_t *where,
                                            fspr_int32_t flags, const char *buf,
                                            fspr_size_t *len)
{
    fspr_ssize_t rv;

    do {
        rv = sendto(sock->socketdes, buf, (*len), flags,
                    (const struct sockaddr*)&where->sa,
                    where->salen);
    } while (rv == -1 && errno == EINTR);

    if (rv == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)
        && sock->timeout != 0) {
        fspr_status_t arv = wait_for_io_or_timeout(sock, 0);
        if (arv != APR_SUCCESS) {
            *len = 0;
            return arv;
        } else {
            do {
                rv = sendto(sock->socketdes, buf, (*len), flags,
                            (const struct sockaddr*)&where->sa,
                            where->salen);
            } while (rv == -1 && errno == EINTR);
        }
    }
    if (rv == -1) {
        *len = 0;
        return errno;
    }
    *len = rv;
    return APR_SUCCESS;
}

APR_DECLARE(fspr_status_t) fspr_socket_recvfrom(fspr_sockaddr_t *from,
                                              fspr_socket_t *sock,
                                              fspr_int32_t flags, char *buf,
                                              fspr_size_t *len)
{
    fspr_ssize_t rv;

    if (from == NULL){
        return APR_ENOMEM;
        /* Not sure if this is correct.  Maybe we should just allocate
           the memory??
         */
    }

    do {
        rv = recvfrom(sock->socketdes, buf, (*len), flags,
                      (struct sockaddr*)&from->sa, &from->salen);
    } while (rv == -1 && errno == EINTR);

    if (rv == -1 && (errno == EAGAIN || errno == EWOULDBLOCK) &&
        sock->timeout != 0) {
        fspr_status_t arv = wait_for_io_or_timeout(sock, 1);
        if (arv != APR_SUCCESS) {
            *len = 0;
            return arv;
        } else {
            do {
                rv = recvfrom(sock->socketdes, buf, (*len), flags,
                              (struct sockaddr*)&from->sa, &from->salen);
                } while (rv == -1 && errno == EINTR);
        }
    }
    if (rv == -1) {
        (*len) = 0;
        return errno;
    }

    (*len) = rv;
    if (rv == 0)
        return APR_EOF;

    return APR_SUCCESS;
}

#endif /* ! BEOS_BONE */
