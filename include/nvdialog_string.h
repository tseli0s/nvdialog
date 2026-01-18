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

#ifndef __nvdialog_string_h__
#define __nvdialog_string_h__ 1

#include <stddef.h>
#include "nvdialog_platform.h"

/**
 * @brief A shortcut macro to create a new @ref NvdDynamicString out of a simple string.
 * @since v0.10
 * @ingroup String
 */
#define NVD_STRING(s) nvd_string_new(s)
/**
 * @brief A shortcut macro to get a C string out of the @ref NvdDynamicString given.
 * @warning The returned string is only valid as long as @ref s is. See @ref nvd_string_to_cstr for details.
 * @since v0.10
 * @ingroup String
 */
#define NVD_CSTR(s) nvd_string_to_cstr(s)

/**
 * @brief A string type that can be resized, manipulated, converted and read from.
 * 
 * `NvdDynamicString` is a recent addition to the library that allows various kinds of strings
 * across various operating systems to be abstracted and represented by a single type. Whereas `const char*` is
 * widely used throughout the library, an `NvdDynamicString` is useful when strings are returned - Simple character literals cannot
 * be returned since they are allocated on the stack. It is also simple to use and convert from and to `char` buffers, making it
 * compatible with almost all existing APIs.
 * @note Do not pass this to any parameters that require a `char*` without explicit conversion (See `nvd_string_to_cstr()`).
 * @note Internally, this dynamic string maintains a capacity variable, that may allocate more memory than needed to store the string. This is done to avoid multiple allocations.
 * @since v0.10.0
 * @ingroup String
*/
typedef struct _NvdDynamicString NvdDynamicString;

/**
 * @brief Creates a new @ref NvdDynamicString and returns it, optionally with
 * the data given in `contents`.
 * @param data A C-style string to convert into a dynamic string, optional. Pass
 * NULL to create an empty `NvdDynamicString`.
 * @returns A new `NvdDynamicString` on success, otherwise `NULL` and the
 * internal error code is set.
 * @since v0.10.0
 * @note This function duplicates the string given internally, so if your string
 * is allocated on the heap, make sure to free it!
 * @ingroup String
 */
NVD_API NvdDynamicString *nvd_string_new(const char *data);

/**
 * @brief Sets the actual string inside the given @ref NvdDynamicString.
 * @param string The @ref NvdDynamicString to modify.
 * @param data The string to set as the contents of the `NvdDynamicString`.
 * @note This will discard any existing data in the string. If you wish to simply append @ref data to the string, see @ref nvd_append_to_string
 * @since v0.10.0
 * @ingroup String
*/

NVD_API void nvd_string_set_data(NvdDynamicString *string, const char *data);

/**
 * @brief Duplicates the given @ref NvdDynamicString without modifying it.
 *
 * You might find this useful when you wish to give the duplicated string in a function that needs to temporarily modify it,
 * or simply modify the string yourself without losing the original contents.
 * In most cases, reusing the same string is enough.
 * @param other The string to copy from.
 * @note The returned object is completely unique from @ref other and any modifications in one won't impact the other.
 * @since v0.10.0
 * @ingroup String
 */
NVD_API NvdDynamicString *nvd_duplicate_string(NvdDynamicString *other);

/**
 * @brief Appends the contents of `new_data` to the end of `string`.
 * @param string The `NvdDynamicString` to append to. Must not be `NULL`.
 * @param new_data The string whose contents will be appended. Must not be `NULL`.
 * @note This function automatically resizes `string` if needed.
 * @since v0.10.0
 * @ingroup String
*/
NVD_API void nvd_append_to_string(NvdDynamicString *string, NvdDynamicString *new_data);

/**
 * @brief Returns a `const char*` representation of the given `NvdDynamicString`.
 * @param string The `NvdDynamicString` to convert. Must not be `NULL`.
 * @returns A pointer to a null-terminated C string. The pointer is valid as long as the dynamic string exists and is not modified. Do NOT modify the returned buffer.
 * @note Do not modify or free the returned pointer, as it may be used elsewhere. Use `nvd_duplicate_string()` if a mutable copy is needed.
 * @since v0.10.0
 * @ingroup String
*/
NVD_API const char *nvd_string_to_cstr(NvdDynamicString *string);

/**
 * @brief Preallocates memory for at least `bytes` inside the @ref string 's data. No data will be lost.
 * @param string The string to increase the capacity of.
 * @param bytes The minimum number of bytes to reserve.
 * @note While optional and implicitly done internally when extra space is needed, this can help with performance if you know the size of the data that must be appended.
 * @since v0.10.0
 * @ingroup String
*/
NVD_API void nvd_string_reserve(NvdDynamicString *string, size_t bytes);

/**
 * @brief Returns the length of the given `NvdDynamicString`.
 * @param string The string whose length will be measured. Must not be `NULL`.
 * @returns The number of characters in the string, excluding the null-terminator.
 * @since v0.10.0
 * @ingroup String
*/
NVD_API size_t nvd_strlen(NvdDynamicString *string);

/**
 * @brief Clears the contents of the given `NvdDynamicString`.
 * @param string The string to clear. Must not be `NULL`.
 * @note Any data inside will be lost, but no additional (re)allocations will be performed.
 * @since v0.10.0
 * @ingroup String
*/
NVD_API void nvd_string_clear(NvdDynamicString *string);
/**
 * @brief Deletes the string from memory and casts it invalid to use.
 * @note For security and safety reasons, all the data of the pointer will be zeroed-out first.
 * @param string The string to delete. This function does nothing if @ref string is `NULL`
 * @since v0.10.0
 * @ingroup String
*/
NVD_API void nvd_delete_string(NvdDynamicString *string);

#endif /* __nvdialog_string_h__ */