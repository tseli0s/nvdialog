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

#define _POSIX_C_SOURCE 200809L

#include "nvdialog_error.h"

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nvdialog_macros.h"
#include "nvdialog_string.h"

NVD_THREAD_LOCAL(NvdError ___error) = NVD_NO_ERROR;

NVD_INTERNAL_FUNCTION void nvd_set_error(NvdError error) {
        ___error = error;
}

NvdError nvd_get_error(void) {
        return ___error;
}

NvdDynamicString *nvd_stringify_error(NvdError err) {
        static const char *messages[] = {
                [NVD_NO_ERROR] = "No error",
                [NVD_NO_DISPLAY] = "No display/desktop detected, make sure X11/Wayland is up and running.",
                [NVD_BACKEND_FAILURE] = "Failed to initialize one of the backends.",
                [NVD_INVALID_PARAM] = "Invalid parameter passed to a function.",
                [NVD_NOT_INITIALIZED] = "The library wasn't initialized.",
                [NVD_ALREADY_INITIALIZED] = "The library has already been initialized.",
                [NVD_STRING_EMPTY] = "Passed an empty string as a parameter.",
                [NVD_FILE_INACCESSIBLE] = "Attempted to read an inaccessible file.",
                [NVD_BACKEND_INVALID] = "Invalid or corrupt backend, make sure your system is up to date.",
                [NVD_OUT_OF_MEMORY] = "No memory left on the host machine.",
                [NVD_INTERNAL_ERROR] = "Internal or unexpected library error - Open an issue on GitHub."
        };

        if (err >= sizeof(messages)/sizeof(*messages) || !messages[err]) {
                nvd_set_error(NVD_INVALID_PARAM);
                return NULL;
        }

        NvdDynamicString *str = nvd_string_new(messages[err]);
        return str;
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


void nvd_out_of_memory() {
        nvd_error_message("%s%d%s%s", "Host machine out of memory: (errno ",
                          errno, strerror(errno), "). Aborting execution");
        nvd_set_error(NVD_OUT_OF_MEMORY); /* Like described in the header, this
                                             is pretty useless. */
        abort();
}

void nvd_message(const char *fmt, ...) {
        va_list args;
        va_start(args, fmt);

        char buffer[NVD_BUFFER_SIZE];

        /* To make clang-tidy happy :) */
        if (snprintf(buffer, sizeof(buffer), "%s %s\n", TERMINAL_PREFIX, fmt) <
            1)
                abort();
        vfprintf(stdout, buffer, args);

        va_end(args);
        fflush(stdout);
}