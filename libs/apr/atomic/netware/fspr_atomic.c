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
#include "fspr_atomic.h"

#include <stdlib.h>

APR_DECLARE(fspr_status_t) fspr_atomic_init(fspr_pool_t *pool)
{
    return APR_SUCCESS;
}

APR_DECLARE(fspr_uint32_t) fspr_atomic_add32(volatile fspr_uint32_t *mem, fspr_uint32_t val)
{
    return atomic_xchgadd((unsigned long *)mem,(unsigned long)val);
}

APR_DECLARE(void) fspr_atomic_sub32(volatile fspr_uint32_t *mem, fspr_uint32_t val)
{
    atomic_sub((unsigned long *)mem,(unsigned long)val);
}

APR_DECLARE(fspr_uint32_t) fspr_atomic_inc32(volatile fspr_uint32_t *mem)
{
    return atomic_xchgadd((unsigned long *)mem, 1);
}

APR_DECLARE(void) fspr_atomic_set32(volatile fspr_uint32_t *mem, fspr_uint32_t val)
{
    *mem = val;
}

APR_DECLARE(fspr_uint32_t) fspr_atomic_read32(volatile fspr_uint32_t *mem)
{
    return *mem;
}

APR_DECLARE(fspr_uint32_t) fspr_atomic_cas32(volatile fspr_uint32_t *mem, fspr_uint32_t with,fspr_uint32_t cmp)
{
    return atomic_cmpxchg((unsigned long *)mem,(unsigned long)cmp,(unsigned long)with);
}

APR_DECLARE(fspr_uint32_t) fspr_atomic_xchg32(volatile fspr_uint32_t *mem, fspr_uint32_t val)
{
    return atomic_xchg((unsigned long *)mem,(unsigned long)val);
}

APR_DECLARE(int) fspr_atomic_dec32(volatile fspr_uint32_t *mem) 
{
    return (atomic_xchgadd((unsigned long *)mem, 0xFFFFFFFF) - 1);
}

APR_DECLARE(void *) fspr_atomic_casptr(volatile void **mem, void *with, const void *cmp)
{
    return (void*)atomic_cmpxchg((unsigned long *)mem,(unsigned long)cmp,(unsigned long)with);
}
