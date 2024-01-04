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

#include "nvdialog_error.h"
#include "nvdialog_macros.h"
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

NVD_THREAD_LOCAL(NvdError ___error) = NVD_NO_ERROR;

NVD_INTERNAL_FUNCTION const char *nvd_fmt_error_message(const char *fmt) {
        assert(fmt != NULL);
        char buffer[NVDIALOG_MAXBUF];
        snprintf(buffer, sizeof(buffer), "%s %s", TERMINAL_PREFIX, fmt);
        char *ptr = buffer;
        return strdup(ptr); // Remember to free it!
}

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
NVD_INTERNAL_FUNCTION NVD_FORCE_INLINE void nvd_set_error(NvdError error) {
        NvdError *ptr = &___error;
        *ptr = error;
}
#ifdef __cplusplus
}
#endif /* __cplusplus */
NVD_FORCE_INLINE NvdError nvd_get_error(void) { return ___error; }

const char *nvd_stringify_error(NvdError err) {
        static char *error = NULL;
        switch (err) {
        case NVD_NO_ERROR:
                error = "No error";
                break;
        case NVD_NO_DISPLAY:
                error = "No display found (Is X.org or a Wayland compositor "
                        "running?)";
                break;
        case NVD_BACKEND_FAILURE:
                error = "Backend initialization was unsuccesful (Invalid parameters?).";
                break;
        case NVD_INVALID_PARAM:
                error = "Invalid parameter passed.";
                break;
        case NVD_NOT_INITIALIZED:
                error = "The library wasn't initialized.";
                break;
        case NVD_ALREADY_INITIALIZED:
                error = "The library has been already initialized.";
                break;
        case NVD_STRING_EMPTY:
                error = "Passed empty string as a parameter.";
                break;
        case NVD_FILE_INACCESSIBLE:
                error = "Attempted to read an inaccessible file.";
                break;
        case NVD_BACKEND_INVALID:
                error = "Backend library is not matching NvDialog.";
                break;
        case NVD_OUT_OF_MEMORY:
                error = "No memory left on the host machine.";
                break;
        case NVD_INTERNAL_ERROR:
                error = "Internal library error - Open an issue on GitHub.";
                break;
        default:
                nvd_set_error(NVD_INVALID_PARAM);
                return NULL;
        }
        return error;
}

void nvd_error_message(const char *fmt, ...) {
        va_list args;
        va_start(args, fmt);

        char buffer[NVD_BUFFER_SIZE];

        snprintf(buffer, sizeof(buffer), "%s %s\n", TERMINAL_PREFIX, fmt);
        vfprintf(stderr, buffer, args);

        va_end(args);
        fflush(stderr);
}

void NVD_DEPRECATED(
    "This function has been deprecated in favor of nvd_error_message. Please "
    "use that instead of this function.") nvd_print(const char *msg) {
        fprintf(stderr, "%s", msg);
}

void nvd_out_of_memory() {
        nvd_error_message("%s%d%s%s",
                          "Host machine out of memory: (errno ",
                          errno,
                          strerror(errno),
                          "). Aborting execution");
        nvd_set_error(NVD_OUT_OF_MEMORY); /* Like described in the header, this
                                             is pretty useless. */
        abort();
}

void nvd_message(const char *fmt, ...) {
        va_list args;
        va_start(args, fmt);

        char buffer[NVD_BUFFER_SIZE];

        /* To make clang-tidy happy :) */
        if (snprintf(buffer, sizeof(buffer), "%s %s\n", TERMINAL_PREFIX, fmt) < 1) abort();
        vfprintf(stdout, buffer, args);

        va_end(args);
        fflush(stdout);
}