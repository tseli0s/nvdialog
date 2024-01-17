/*
 *  The MIT License (MIT)
 *
 *  Copyright (c) 2024 Aggelos Tselios
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
#include <stdbool.h>

#if defined (unix) || defined(__APPLE__)
#include <sys/types.h>
#include <unistd.h>
#else
#include <windows.h> // Has to be included apparently
#include <processthreadsapi.h>
#endif /* NVD_PLATFORM_UNIX */

/**
 * @brief A data structure to hold information about a Linux
 * distribution. It should be returned by @ref nvd_get_distribution_info;
 */
typedef struct _NvdDistroInfo {
    char* name;
    long version_m;
    long version_s;
} NvdDistroInfo;

/**
 * @brief An identifier to match a new process ID spawned by @ref nvd_create_process
 * @details Similar to the `pid_t` type (And similarly defined), this type
 * keeps the process ID for a forked process.
 * @sa @ref nvd_create_process
 * @since v0.7.0
 */
typedef signed long NvdProcessID;

/**
 * @brief Creates a new process by forking.
 * @details This function is used to fork the current process.
 * On success, the @ref is returned to the parent, and 0 is returned to 
 * the child.
 * @note On Windows, this function does nothing. You should use `CreateProcess` manually
 * instead, which is guaranteed to work as expected.
 * @since v0.7.0
 * @sa @ref NvdProcessID
 */
NvdProcessID nvd_create_process(void);

/**
 * @brief Returns a boolean to indicate whether the host is running the application through
 * a container (eg. Flatpak). It's accuracy generally varies and the definition is actually
 * pretty hacky.
 * @note NvDialog does not consider Windows as a sandboxed environment regardless of what's the actual case.
 * @attention As a general rule, most macOS applications are sandboxed, and either way, it wouldn't change anything. This function won't return true on macOS **EVER**.
 * @since v0.7.0
 */
bool nvd_is_sandboxed(void);

/**
 * @brief Splits a string of words separated by a semicolon into separate words.
 *
 * This function takes a string of words separated by a semicolon, and splits
 * it into separate words. The words are returned as an array of char pointers,
 * with a null pointer indicating the end of the array. The words are allocated
 * in a single block of memory, and can be freed using a single call to free().
 *
 * @param str The input string of words.
 *
 * @return An array of char pointers containing the separate words, or NULL if
 * there was an error allocating memory.
 */
char** nvd_seperate_args(const char* str);

/**
 * @brief Returns the distribution information on Linux, lik
 * @note This function will return `NULL` if the OS is not GNU/Linux. It will also only return data related
 * to the base of the distribution, NOT the exact distribution you're running (eg. on Ubuntu you will get Debian).
 * @return A @ref NvdDistroInfo filled out with all the necessary information,
 * or NULL if there is a failure (Will set the error accordingly unless not on GNU/Linux).
 */
NvdDistroInfo nvd_get_distro_branch();

/**
 * @brief Returns the path to `libnotify` on the system for `dlopen`.
 * @note Linux-only function, will not work on Windows/macOS. The pointer returned was dynamically allocated
 * and hence should be freed using `free()`.
 *
 * @return The path to libnotify on each platform if succesfull, otherwise NULL.
 */
char* nvd_get_libnotify_path();

/**
 * @brief Returns the path the library is using to find `libnotify`.
 * @note This is unrelated to @ref nvd_get_libnotify_path
 * @return A static pointer to a NULL-terminated string to the `libnotify` 's SO file path.
 */
// For convenience reasons this is the only function from this file implemented in nvdialog_main.c
const char* nvd_path_to_libnotify();

#endif /* __nvdialog_util_h__ */