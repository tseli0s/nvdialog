/*
 *  The MIT License (MIT)
 *
 *  Copyright (c) 2023 Aggelos Tselios
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#pragma once

#ifndef __nvdialog_util_h__
#define __nvdialog_util_h__ (1)

#include <string.h>
#include <stdlib.h>

#if defined (unix) || defined(__APPLE__)
#include <sys/types.h>
#include <unistd.h>
#else
#include <processthreadsapi.h>
#endif /* NVD_PLATFORM_UNIX */

/**
 * @brief An identifier to match
 * @details Similar to the `pid_t` type (And similarly defined), this type
 * keeps the process ID for a forked process.
 * @note On Windows, this function does nothing. You should use `CreateProcess` manually
 * instead, which is guaranteed to work as expected.
 * @sa @ref nvd_create_process
 * @since v0.7.0
 */
typedef signed long NvdProcessID;

/**
 * @brief Creates a new process by forking.
 * @details This function is used to fork the current process.
 * On success, the @ref is returned to the parent, and 0 is returned to 
 * the child.
 * @since v0.7.0
 * @sa @ref NvdProcessID
 */
NvdProcessID nvd_create_process(void);

#endif /* __nvdialog_util_h__ */