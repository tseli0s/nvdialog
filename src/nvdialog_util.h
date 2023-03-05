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

/**
 * @brief Places NULL bytes to @ref p until @ref size is reached.
 * Can be useful for uninitialized variables / fields.
 * @param p The pointer to write NULL bytes to.
 * @param size The amount of bytes to write.
 * @returns 0 on success, -1 if p is NULL, 1 if size is 0.
 * @note This function does no bound checking. It's up to you to ensure
 * the function won't write more bytes than the total owned bytes of @ref p
 */
int nvd_zero_memory(void* p, size_t size);

/**
 * @brief Returns the length of a C string.
 * @param str The string to find the length of.
 * @note This function is only implemented as a faster alternative
 * to `strlen`, for large strings.
 * @return The length of the string as a `size_t`.
 */
inline size_t nvd_strlen(const char* str) {
    size_t size = 0;

    #pragma unroll /* This saves the most time basically. */
    for (int i = 0; str[i] != '\0'; i++) {
        size = i;
    }
    return size;
}

/**
 * @brief A wrapper around malloc with library-oriented error handling.
 * @param size The amount of memory the pointer needs to have.
 * @note  You still need to check for NULL when using this function.
 * @return A pointer to heap-allocated memory of size @ref size , or NULL on failure.
 */
void* nvd_malloc(size_t size);

/**
 * @brief A wrapper around calloc with library-oriented error handling.
 * @param size The amount of memory the pointer needs to have.
 * @note  You still need to check for NULL when using this function.
 * @return A pointer to heap-allocated memory of size @ref size , or NULL on failure.
 * The pointer returned has all memory zeroed.
 */
void* nvd_calloc();

#endif /* __nvdialog_util_h__ */