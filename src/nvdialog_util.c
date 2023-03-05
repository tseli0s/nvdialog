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

#include "nvdialog_util.h"
#include "nvdialog_error.h"
#include "nvdialog_assert.h"

int nvd_zero_memory(void* p, size_t size) {
    if (size <= 0) return 1;
    if (!p) return -1;

    size_t i = 0;

    #pragma unroll
    while (i != size) {
        ((char*)p)[i] = '\0';
        i++;
    }
    return 0;
}

void* nvd_malloc(size_t size) {
    if (size < 0) {
        nvd_set_error(NVD_INVALID_PARAM);
        return NULL;
    }

    void* p = malloc(size);
    if (p == NULL) {
        NVD_ASSERT(p != NULL); /* For the error message. */
        return NULL;
    }

    return p;
}

void* nvd_calloc(size_t size) {
    NVD_ASSERT(size > 0);

    void* calloc_ptr = nvd_malloc(size);
    if (calloc_ptr) {
        nvd_zero_memory(calloc_ptr, size);
        return calloc_ptr;
    }
    else return NULL;
}