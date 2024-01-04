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

#ifndef __nvd_error_h__
#define __nvd_error_h__

#include "nvdialog.h"
#include "nvdialog_macros.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

#if !defined(_WIN32) || defined(linux) || defined(__gnu_linux__)
#define TERMINAL_PREFIX "\x1B[92m\x1b[1mlibnvdialog:\x1b[0m"

#else

#define TERMINAL_PREFIX "libnvdialog:"
#endif /* UNIX_PREFIX */

#define NVD_PRINT_CURRENT_ERROR nvd_print(nvd_stringify_error(nvd_get_error()))

/* Formats an error message to print to stderr / stdout */
NVD_INTERNAL_FUNCTION const char *nvd_fmt_error_message(const char *fmt);

/* Sets the error code of the library */
NVD_INTERNAL_FUNCTION void nvd_set_error(NvdError error);

/* Prints the error message given to stdout */
NVD_DEPRECATED(
    "This function has been deprecated in favor of nvd_error_message. "
    "Please use that instead of this function.")
void nvd_print(const char *msg);

/*
 * A function that allows printing an error message to stderr, with support for
 * variadic arguments, proper formatting and easier integration with the
 * library.
 */
void nvd_error_message(const char *fmt, ...);

/*
 * Aborts execution if memory cannot be allocated on the heap.
 * This function cancels out the NVD_OUT_OF_MEMORY error code,
 * so the former may be deprecated soon in favor of this.
 */
void nvd_out_of_memory();

/*
 * Prints a message to stdout.
 * This function will only be useful if NvDialog is built with this
 * option. It is also not used for error messages, just some debugging.
 */
void nvd_message(const char *fmt, ...);

#endif /* __nvd_error_h__ */