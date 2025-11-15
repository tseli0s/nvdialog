/*
 *  The MIT License (MIT)
 *
 *  Copyright (c) 2025 Aggelos Tselios
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
#include <stddef.h>
#include "nvdialog_string.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#if defined(__unix__) || defined(__APPLE__)
#include <sys/types.h>
#include <unistd.h>
#else
#include <windows.h>  // Has to be included apparently
#endif                /* NVD_PLATFORM_UNIX */

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
 * @brief Writes @ref size bytes to @ref ptr to ensure proper initialization.
 * @param ptr A pointer to the data structure where the NULL bytes will be
 * written.
 * @param size The amount of NULL bytes to write before stopping.
 */
void nvd_zero_memory(void* ptr, size_t size);

/**
 * @brief An identifier to match a new process ID spawned by @ref
 * nvd_create_process
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
 * @note On Windows, this function does nothing. You should use `CreateProcess`
 * manually instead, which is guaranteed to work as expected.
 * @since v0.7.0
 * @sa @ref NvdProcessID
 */
NvdProcessID nvd_create_process(void);

/**
 * @brief Returns a boolean to indicate whether the host is running the
 * application through a container (eg. Flatpak). It's accuracy generally varies
 * and the definition is actually pretty hacky.
 * @note NvDialog does not consider Windows as a sandboxed environment
 * regardless of what's the actual case.
 * @attention As a general rule, most macOS applications are sandboxed, and
 * either way, it wouldn't change anything. This function won't return true on
 * macOS **EVER**.
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
 * @brief A wrapper around `malloc` that checks if the allocation succeeded and properly fails otherwise.
 *
 * This wrapper essentially factorizes the usual routine for checking an allocation success: If the pointer returned
 * is NULL, then set NVD_OUT_OF_MEMORY as the error, print a message and die. Instead of repeating the same check
 * everywhere, this function wraps it nicely for us.
 *
 * @sa nvd_calloc
 * @since v0.10.1
 */
void *nvd_malloc(size_t size);

/**
 * @brief A wrapper around `calloc` that checks if the allocation succeeded and properly fails otherwise.
 * For more details, see @ref nvd_malloc
 * @since v0.10.1
 * @sa nvd_malloc
 */
void *nvd_calloc(size_t n_items, size_t size_each);

#endif /* __nvdialog_util_h__ */
