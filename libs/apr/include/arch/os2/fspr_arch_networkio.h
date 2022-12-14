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

#include "fspr_private.h"
#include "fspr_network_io.h"
#include "fspr_general.h"
#include "fspr_arch_os2calls.h"
#include "fspr_poll.h"

#if APR_HAVE_NETDB_H
#include <netdb.h>
#endif

typedef struct sock_userdata_t sock_userdata_t;
struct sock_userdata_t {
    sock_userdata_t *next;
    const char *key;
    void *data;
};

struct fspr_socket_t {
    fspr_pool_t *pool;
    int socketdes;
    int type;
    int protocol;
    fspr_sockaddr_t *local_addr;
    fspr_sockaddr_t *remote_addr;
    fspr_interval_time_t timeout;
    int nonblock;
    int local_port_unknown;
    int local_interface_unknown;
    int remote_addr_unknown;
    fspr_int32_t options;
    fspr_int32_t inherit;
    sock_userdata_t *userdata;

    /* if there is a timeout set, then this pollset is used */
    fspr_pollset_t *pollset;
};

/* Error codes returned from sock_errno() */
#define SOCBASEERR              10000
#define SOCEPERM                (SOCBASEERR+1)             /* Not owner */
#define SOCESRCH                (SOCBASEERR+3)             /* No such process */
#define SOCEINTR                (SOCBASEERR+4)             /* Interrupted system call */
#define SOCENXIO                (SOCBASEERR+6)             /* No such device or address */
#define SOCEBADF                (SOCBASEERR+9)             /* Bad file number */
#define SOCEACCES               (SOCBASEERR+13)            /* Permission denied */
#define SOCEFAULT               (SOCBASEERR+14)            /* Bad address */
#define SOCEINVAL               (SOCBASEERR+22)            /* Invalid argument */
#define SOCEMFILE               (SOCBASEERR+24)            /* Too many open files */
#define SOCEPIPE                (SOCBASEERR+32)            /* Broken pipe */
#define SOCEOS2ERR              (SOCBASEERR+100)            /* OS/2 Error */

const char *fspr_inet_ntop(int af, const void *src, char *dst, fspr_size_t size);
int fspr_inet_pton(int af, const char *src, void *dst);
void fspr_sockaddr_vars_set(fspr_sockaddr_t *, int, fspr_port_t);

#endif  /* ! NETWORK_IO_H */

