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

#include "fspr_arch_file_io.h"
#include "fspr_file_io.h"
#include "fspr_lib.h"
#include <string.h>
#include <io.h>


static fspr_status_t setptr(fspr_file_t *thefile, unsigned long pos )
{
    long newbufpos;
    ULONG rc;

    if (thefile->direction == 1) {
        fspr_status_t rv = fspr_file_flush(thefile);

        if (rv != APR_SUCCESS) {
            return rv;
        }

        thefile->bufpos = thefile->direction = thefile->dataRead = 0;
    }

    newbufpos = pos - (thefile->filePtr - thefile->dataRead);
    if (newbufpos >= 0 && newbufpos <= thefile->dataRead) {
        thefile->bufpos = newbufpos;
        rc = 0;
    } else {
        rc = DosSetFilePtr(thefile->filedes, pos, FILE_BEGIN, &thefile->filePtr );

        if ( !rc )
            thefile->bufpos = thefile->dataRead = 0;
    }

    return APR_FROM_OS_ERROR(rc);
}



APR_DECLARE(fspr_status_t) fspr_file_seek(fspr_file_t *thefile, fspr_seek_where_t where, fspr_off_t *offset)
{
    if (!thefile->isopen) {
        return APR_EBADF;
    }

    thefile->eof_hit = 0;

    if (thefile->buffered) {
        int rc = EINVAL;
        fspr_finfo_t finfo;

        switch (where) {
        case APR_SET:
            rc = setptr(thefile, *offset);
            break;

        case APR_CUR:
            rc = setptr(thefile, thefile->filePtr - thefile->dataRead + thefile->bufpos + *offset);
            break;

        case APR_END:
            rc = fspr_file_info_get(&finfo, APR_FINFO_NORM, thefile);
            if (rc == APR_SUCCESS)
                rc = setptr(thefile, finfo.size + *offset);
            break;
        }

        *offset = thefile->filePtr - thefile->dataRead + thefile->bufpos;
        return rc;
    } else {
        switch (where) {
        case APR_SET:
            where = FILE_BEGIN;
            break;

        case APR_CUR:
            where = FILE_CURRENT;
            break;

        case APR_END:
            where = FILE_END;
            break;
        }

        return APR_FROM_OS_ERROR(DosSetFilePtr(thefile->filedes, *offset, where, (ULONG *)offset));
    }
}



APR_DECLARE(fspr_status_t) fspr_file_trunc(fspr_file_t *fp, fspr_off_t offset)
{
    int rc = DosSetFileSize(fp->filedes, offset);

    if (rc != 0) {
        return APR_FROM_OS_ERROR(rc);
    }

    if (fp->buffered) {
        return setptr(fp, offset);
    }

    return APR_SUCCESS;
}
