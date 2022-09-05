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

#include "nvd_error.h"
#include <stdio.h>

#define MAXBUF 4096
#if !defined(_WIN32) || defined(linux) || defined(__gnu_linux__)
#define TERMINAL_PREFIX "\x1B[97m\x1b[1mlibnvdialog:"

#else

#define TERMINAL_PREFIX "libnvdialog:"
#endif /* UNIX_PREFIX */

static NvdError ___error = NVD_NO_ERROR;

NVD_INTERNAL_FUNCTION const char *nvd_fmt_error_message(const char *fmt) {
        assert(fmt != NULL);
        char buffer[MAXBUF];
        sprintf(buffer, "%s %s", TERMINAL_PREFIX, fmt);
        char *ptr = buffer;
        return ptr;
}

NVD_INTERNAL_FUNCTION NVD_FORCE_INLINE void nvd_set_error(NvdError error) {
        NvdError *ptr = &___error;
        *ptr = error;
}

NVD_FORCE_INLINE uint32_t nvd_get_error(void) { return ___error; }

const char *nvd_stringify_error(NvdError err) {
        char *error = NULL;
        switch (err) {
        case NVD_NO_ERROR:
                return NULL;
        case NVD_NO_DISPLAY:
                error = "No display found (Is X.org or a Wayland compositor "
                        "running?)";
                break;
        case NVD_INVALID_PARAM:
                error = "Invalid parameter passed.";
                break;
        case NVD_NOT_INITIALIZED:
                error = "The library wasn't initialized.";
                break;
        case NVD_STRING_EMPTY:
                error = "Passed empty string as a parameter.";
                break;
        case NVD_OUT_OF_MEMORY:
                error = "No memory left on the host machine.";
                break;
        case NVD_INTERNAL_ERROR:
                error = "Internal library error - Open an issue on GitHub.";
                break;
        default:
                return NULL;
        }
        return error;
}

void nvd_print(const char*msg)
{
        fprintf(stderr, "%s", msg);
}