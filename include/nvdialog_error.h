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

#include "nvdialog_string.h"
#ifndef __nvdialog_error_h__
#define __nvdialog_error_h__ 1

#include "nvdialog_platform.h"

/**
 * @brief The enumerator containing most
 * errors the library can handle.
 * @sa @ref nvd_stringify_error
 */
typedef enum {
        NVD_NO_ERROR = 0,
        NVD_NO_DISPLAY,
        NVD_BACKEND_FAILURE,
        NVD_INVALID_PARAM,
        NVD_NOT_INITIALIZED,
        NVD_BACKEND_INVALID,
        NVD_FILE_INACCESSIBLE,
        NVD_STRING_EMPTY,
        NVD_OUT_OF_MEMORY,
        NVD_INTERNAL_ERROR,
        NVD_ALREADY_INITIALIZED,
} NvdError;

/**
 * @brief Returns the current error code of the library.
 *
 * The error code has to be manually be transformed into a string
 * using @ref nvd_stringify_error. Else, use the @ref NvdError enum to check for
 * the error manually.
 *
 * @ingroup Error
 * @returns The error code (Will be automatically 0 if no errors were
 * encountered).
 */
NVD_API NvdError nvd_get_error(void);

/**
 * @brief Transforms an error code into a string representation, that can be
 * used to print errors to the console.
 * @returns A @ref NvdDynamicString containing the error as a string, or NULL in case of failure or invalid parameter.
 * @ingroup Error
 * @note Pre v0.10 code may not work with this function due to different return types.
 */
NVD_API NvdDynamicString *nvd_stringify_error(NvdError err);

#endif /* __nvdialog_error_h__ */