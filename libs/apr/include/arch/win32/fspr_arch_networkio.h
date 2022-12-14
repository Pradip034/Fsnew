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

#ifndef NETWORK_IO_H
#define NETWORK_IO_H

#include "fspr_network_io.h"
#include "fspr_general.h"
#include "fspr_poll.h"
#ifdef _MSC_VER
#undef MCAST_JOIN_SOURCE_GROUP
#endif

typedef struct sock_userdata_t sock_userdata_t;
struct sock_userdata_t {
    sock_userdata_t *next;
    const char *key;
    void *data;
};

struct fspr_socket_t {
    fspr_pool_t         *pool;
    SOCKET              socketdes;
    int                 type; /* SOCK_STREAM, SOCK_DGRAM */
    int                 protocol;
    fspr_sockaddr_t     *local_addr;
    fspr_sockaddr_t     *remote_addr;
    int                 timeout_ms; /* MUST MATCH if timeout > 0 */
    fspr_interval_time_t timeout;
    fspr_int32_t         disconnected;
    int                 local_port_unknown;
    int                 local_interface_unknown;
    int                 remote_addr_unknown;
    fspr_int32_t         options;
    fspr_int32_t         inherit;
#if APR_HAS_SENDFILE
    /* As of 07.20.04, the overlapped structure is only used by 
     * fspr_socket_sendfile and that's where it will be allocated 
     * and initialized.
     */
    OVERLAPPED         *overlapped;
#endif
    sock_userdata_t    *userdata;

    /* if there is a timeout set, then this pollset is used */
    fspr_pollset_t *pollset;
};

#ifdef _WIN32_WCE
#ifndef WSABUF
typedef struct _WSABUF {
    u_long      len;     /* the length of the buffer */
    char FAR *  buf;     /* the pointer to the buffer */
} WSABUF, FAR * LPWSABUF;
#endif
#else
/* Not sure if this is the right place to define this */
#define HAVE_STRUCT_IPMREQ
#endif

fspr_status_t status_from_res_error(int);

const char *fspr_inet_ntop(int af, const void *src, char *dst, fspr_size_t size);
int fspr_inet_pton(int af, const char *src, void *dst);
void fspr_sockaddr_vars_set(fspr_sockaddr_t *, int, fspr_port_t);

#define fspr_is_option_set(skt, option)  \
    (((skt)->options & (option)) == (option))

#define fspr_set_option(skt, option, on) \
    do {                                 \
        if (on)                          \
            (skt)->options |= (option);         \
        else                             \
            (skt)->options &= ~(option);        \
    } while (0)

#endif  /* ! NETWORK_IO_H */

