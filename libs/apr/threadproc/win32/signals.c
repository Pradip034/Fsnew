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

#include "win32/fspr_arch_threadproc.h"
#include "win32/fspr_arch_file_io.h"
#include "fspr_thread_proc.h"
#include "fspr_file_io.h"
#include "fspr_general.h"
#if APR_HAVE_SIGNAL_H
#include <signal.h>
#endif
#include <string.h>
#if APR_HAVE_SYS_WAIT
#include <sys/wait.h>
#endif

/* Windows only really support killing process, but that will do for now. 
 *
 * ### Actually, closing the input handle to the proc should also do fine 
 * for most console apps.  This definately needs improvement...
 */
APR_DECLARE(fspr_status_t) fspr_proc_kill(fspr_proc_t *proc, int signal)
{
    if (proc->hproc != NULL) {
        if (TerminateProcess(proc->hproc, signal) == 0) {
            return fspr_get_os_error();
        }
        /* On unix, SIGKILL leaves a fspr_proc_wait()able pid lying around, 
         * so we will leave hproc alone until the app calls fspr_proc_wait().
         */
        return APR_SUCCESS;
    }
    return APR_EPROC_UNKNOWN;
}

void fspr_signal_init(fspr_pool_t *pglobal)
{
}

const char *fspr_signal_description_get(int signum)
{
    return "unknown signal (not supported)";
}

APR_DECLARE(fspr_status_t) fspr_signal_block(int signum)
{
    return APR_ENOTIMPL;
}

APR_DECLARE(fspr_status_t) fspr_signal_unblock(int signum)
{
    return APR_ENOTIMPL;
}
