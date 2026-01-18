/*
 *  The MIT License (MIT)
 *
 *  Copyright (c) 2026 Aggelos Tselios
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

#ifndef __nvdialog_widestr_h__
#define __nvdialog_widestr_h__ 1

#include <limits.h>
#include <wchar.h>

#include "nvdialog_platform.h"
#include "nvdialog_string.h"

#define NVD_WCHAR_BITS (sizeof(wchar_t) * CHAR_BIT)

/**
 * @brief A wide character based string.
 * @details Wide characters are character representations that use more than one
 * byte per character, allowing support for large character sets such as
 * Unicode.
 * @note Windows uses 16 bit characters as wide characters, whereas most other
 * operating systems use 32 bits. See @ref NVD_WCHAR_BITS to know how many bits
 * does each character use.
 * @sa NvdDynamicString (the regular C string equivalent)
 * @since x.x.x (TODO)
 * @ingroup WideString
 */
typedef struct _NvdWideString NvdWideString;

/**
 * @brief Allocates an @ref NvdWideString out of a wide character buffer.
 * @since x.x.x (TODO)
 * @return An @ref NvdWideString on success, or NULL on failure; Call @ref
 * nvd_get_error for details.
 * @ingroup WideString
 */
NVD_API NvdWideString *nvd_wide_string_new(const wchar_t *buffer);

/**
 * @brief Tries to cast a wide string to a regular string, if possible.
 * @warning There's no guarantee that this function will succeed. You should
 * check the return value and validate the string's data before using them.
 * @since x.x.x (TODO)
 * @return An @ref NvdDynamicString with C-style contents on success, or NULL on
 * failure; Call @ref nvd_get_error for details.
 * @ingroup WideString
 */
NVD_API NvdDynamicString *nvd_wide_to_c_str(NvdWideString *str);

/**
 * @brief Returns the length of the given `NvdWideString`.
 * @param string The string whose length will be measured. Must not be `NULL`.
 * @returns The number of characters in the string, excluding the
 * null-terminator.
 * @since x.x.x (TODO)
 * @ingroup WideString
 */
NVD_API size_t nvd_wide_strlen(NvdWideString *string);

/**
 * @brief Returns the internal wide character buffer of the given @ref
 * NvdWideString.
 * @since x.x.x (TODO)
 * @ingroup WideString
 * @return The internal wide character buffer of the given @ref NvdWideString or
 * NULL on failure.
 */
NVD_API wchar_t *nvd_get_internal_wide_string(NvdWideString *str);

/**
 * @brief Deallocates the @ref NvdWideString given.
 * @since x.x.x (TODO)
 * @ingroup WideString
 */
NVD_API void nvd_delete_wide_string(NvdWideString *str);

#endif /* __nvdialog_widestr_h__ */
