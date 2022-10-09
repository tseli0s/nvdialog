/*
 *  The MIT License (MIT)
 *
 *  Copyright (c) 2022 Aggelos Tselios
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

#ifndef __nvdialog_assert_h__
#define __nvdialog_assert_h__

#include "nvdialog.h"
#include "nvdialog_macros.h"
#include "nvdialog_error.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void __attribute__((format(printf, 1, 2)))
nvd_print_assert(const char *msg, ...) {
        va_list args;
        va_start(args, msg);

        char buffer[NVD_BUFFER_SIZE * 16]; /* I know. Huge buffer. But we could
                                              be dealing with worse things. */
        sprintf(buffer, "%s \x1B[1m%s\x1B[0m", TERMINAL_PREFIX, msg);
        vfprintf(stderr, buffer, args);

        va_end(args);
        fflush(stderr);
}

#define NVD_STRING(s) #s

#define NVD_ASSERT(eq)                                                         \
        do {                                                                   \
                if (!(eq)) {                                                   \
                        nvd_print_assert(                                      \
                            "Assertion failure: %s\n  Line: %d\n  Filename: "  \
                            "%s\n  Function: %s\n",                            \
                            NVD_STRING(eq), __LINE__, __FILE__, NVD_FN_IDENT);            \
                }                                                              \
        } while (0)

/* This is supposed to be called only when the library cannot be used anymore.
 */
#define NVD_ASSERT_FATAL(eq)                                                   \
        do {                                                                   \
                if (!(eq)) {                                                   \
                        nvd_print_assert("**CRITICAL ASSERTION FAILURE**: "    \
                                         "%s\n  Line: %d\n  Filename: "        \
                                         "%s\n  Function: %s\n",               \
                                         #eq, __LINE__, __FILE__, __func__);   \
                }                                                              \
                abort();                                                       \
        } while (0)

#endif /* __nvdialog_assert_h__ */