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

#include "nvdialog_string.h"
#include "nvdialog_assert.h"
#include "nvdialog_util.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/* The default capacity of a string. This doesn't affect anything other than how often we will have to reallocate. */
#define NVD_DEFAULT_STRING_CAPACITY (32)

struct _NvdDynamicString {
    size_t len;
    size_t capacity;
    char *buffer;
};

NvdDynamicString *nvd_string_new(const char *data) {
    NvdDynamicString *obj = malloc(sizeof(NvdDynamicString));
    NVD_RETURN_IF_NULL(obj);
    if (data) {
        size_t datalen = strlen(data);
        obj->buffer = malloc(datalen + 1);
        obj->len = datalen;
        obj->capacity = (datalen + 1);
        memcpy(obj->buffer, data, datalen);
        obj->buffer[datalen] = '\0';
    } else {
        obj->buffer = calloc(1, NVD_DEFAULT_STRING_CAPACITY);
        obj->capacity = NVD_DEFAULT_STRING_CAPACITY;
        obj->len = 0;
    }

    return obj;
}

void nvd_string_set_data(NvdDynamicString *string, const char *data) {
    NVD_ASSERT_FATAL(string != NULL);
    NVD_ASSERT_FATAL(data != NULL);

    size_t len = strlen(data);

    if ((len + 1) > string->capacity) {
        size_t new_capacity = string->capacity + len + NVD_DEFAULT_STRING_CAPACITY;
        string->buffer = realloc(string->buffer, new_capacity);
        string->capacity = new_capacity;
        string->len = len;
    }
    memcpy(string->buffer, data, len);
    string->buffer[len] = '\0';
}

NvdDynamicString *nvd_duplicate_string(NvdDynamicString *other) {
    NVD_ASSERT_FATAL(other != NULL);

    NvdDynamicString *string = malloc(sizeof(NvdDynamicString));
    string->buffer = malloc(other->capacity);
    string->capacity = other->capacity;
    string->len = other->len;

    memcpy(string->buffer, other->buffer, string->len + 1);
    return string;
}

const char *nvd_string_to_cstr(NvdDynamicString *string) {
    NVD_ASSERT_FATAL(string != NULL);
    /* The implementation only uses C-approved `char`s and NULL-terminates buffer for ease of use, so we can just return this. */
    return string->buffer;
}

void nvd_string_reserve(NvdDynamicString *string, size_t bytes) {
    if (bytes > string->capacity) {
        string->buffer = realloc(string->buffer, bytes);
        string->capacity = bytes;
    }
}

size_t nvd_strlen(NvdDynamicString *string) {
    return string->len;
}

void nvd_string_clear(NvdDynamicString *string) {
    nvd_zero_memory(string->buffer, string->capacity);
    string->len = 0;
}

void nvd_delete_string(NvdDynamicString *string) {
    if (!string) return;

    free(string->buffer);
    free(string);
}