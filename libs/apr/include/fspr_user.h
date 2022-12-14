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

#ifndef APR_USER_H
#define APR_USER_H

/**
 * @file fspr_user.h
 * @brief APR User ID Services 
 */

#include "fspr.h"
#include "fspr_errno.h"
#include "fspr_pools.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup fspr_user User and Group ID Services
 * @ingroup APR 
 * @{
 */

/**
 * Structure for determining user ownership.
 */
#ifdef WIN32
typedef PSID                      fspr_uid_t;
#else
typedef uid_t                     fspr_uid_t;
#endif

/**
 * Structure for determining group ownership.
 */
#ifdef WIN32
typedef PSID                      fspr_gid_t;
#else
typedef gid_t                     fspr_gid_t;
#endif

#if APR_HAS_USER 

/**
 * Get the userid (and groupid) of the calling process
 * @param userid   Returns the user id
 * @param groupid  Returns the user's group id
 * @param p The pool from which to allocate working space
 * @remark This function is available only if APR_HAS_USER is defined.
 */
APR_DECLARE(fspr_status_t) fspr_uid_current(fspr_uid_t *userid,
                                          fspr_gid_t *groupid,
                                          fspr_pool_t *p);

/**
 * Get the user name for a specified userid
 * @param username Pointer to new string containing user name (on output)
 * @param userid The userid
 * @param p The pool from which to allocate the string
 * @remark This function is available only if APR_HAS_USER is defined.
 */
APR_DECLARE(fspr_status_t) fspr_uid_name_get(char **username, fspr_uid_t userid,
                                           fspr_pool_t *p);

/**
 * Get the userid (and groupid) for the specified username
 * @param userid   Returns the user id
 * @param groupid  Returns the user's group id
 * @param username The username to lookup
 * @param p The pool from which to allocate working space
 * @remark This function is available only if APR_HAS_USER is defined.
 */
APR_DECLARE(fspr_status_t) fspr_uid_get(fspr_uid_t *userid, fspr_gid_t *groupid,
                                      const char *username, fspr_pool_t *p);

/**
 * Get the home directory for the named user
 * @param dirname Pointer to new string containing directory name (on output)
 * @param username The named user
 * @param p The pool from which to allocate the string
 * @remark This function is available only if APR_HAS_USER is defined.
 */
APR_DECLARE(fspr_status_t) fspr_uid_homepath_get(char **dirname, 
                                               const char *username, 
                                               fspr_pool_t *p);

/**
 * Compare two user identifiers for equality.
 * @param left One uid to test
 * @param right Another uid to test
 * @return APR_SUCCESS if the fspr_uid_t strutures identify the same user,
 * APR_EMISMATCH if not, APR_BADARG if an fspr_uid_t is invalid.
 * @remark This function is available only if APR_HAS_USER is defined.
 */
#if defined(WIN32)
APR_DECLARE(fspr_status_t) fspr_uid_compare(fspr_uid_t left, fspr_uid_t right);
#else
#define fspr_uid_compare(left,right) (((left) == (right)) ? APR_SUCCESS : APR_EMISMATCH)
#endif

/**
 * Get the group name for a specified groupid
 * @param groupname Pointer to new string containing group name (on output)
 * @param groupid The groupid
 * @param p The pool from which to allocate the string
 * @remark This function is available only if APR_HAS_USER is defined.
 */
APR_DECLARE(fspr_status_t) fspr_gid_name_get(char **groupname, 
                                             fspr_gid_t groupid, fspr_pool_t *p);

/**
 * Get the groupid for a specified group name
 * @param groupid Pointer to the group id (on output)
 * @param groupname The group name to look up
 * @param p The pool from which to allocate the string
 * @remark This function is available only if APR_HAS_USER is defined.
 */
APR_DECLARE(fspr_status_t) fspr_gid_get(fspr_gid_t *groupid, 
                                      const char *groupname, fspr_pool_t *p);

/**
 * Compare two group identifiers for equality.
 * @param left One gid to test
 * @param right Another gid to test
 * @return APR_SUCCESS if the fspr_gid_t strutures identify the same group,
 * APR_EMISMATCH if not, APR_BADARG if an fspr_gid_t is invalid.
 * @remark This function is available only if APR_HAS_USER is defined.
 */
#if defined(WIN32)
APR_DECLARE(fspr_status_t) fspr_gid_compare(fspr_gid_t left, fspr_gid_t right);
#else
#define fspr_gid_compare(left,right) (((left) == (right)) ? APR_SUCCESS : APR_EMISMATCH)
#endif

#endif  /* ! APR_HAS_USER */

/** @} */

#ifdef __cplusplus
}
#endif

#endif  /* ! APR_USER_H */
