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

#include "nvdialog_util.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nvdialog_error.h"
#include "nvdialog_macros.h"

#ifdef _WIN32
#include <io.h>
#define access _access
#else
#include <unistd.h>  // access()
#endif

static inline bool nvd_file_exists(const char* path) {
        return (access(path, 0) == 0);
}

void nvd_zero_memory(void* ptr, size_t size) { memset(ptr, 0, size); }

NvdProcessID nvd_create_process(void) {
#if defined(__unix__) || defined(__APPLE__)
        return (NvdProcessID)fork();
#else
        return (NvdProcessID)GetCurrentProcessId();
#endif
}

/*
 * For some explanation, here's my answer on StackOverflow:
 * https://stackoverflow.com/questions/75274925/is-there-a-way-to-find-out-if-i-am-running-inside-a-flatpak-appimage-or-another
 */
bool nvd_is_sandboxed(void) {
#if defined(_WIN32) || defined(NVD_USE_COCOA)
        return false;  // see documentation
#else

        if (getenv("container")) {
                return true;
        } else if (getenv("APPIMAGE")) {
                return true;
        } else if (getenv("SNAP")) {
                return true;
        }
        return false;

#endif
}

char** nvd_seperate_args(const char* str) {
        size_t count = 1;
        const char* ptr = str;
        while (*ptr != '\0') {
                if (*ptr == ';') {
                        count++;
                }
                ptr++;
        }

        char* words_buffer = (char*)nvd_malloc(strlen(str) + 1);
        char** words = (char**)nvd_malloc((count + 1) * sizeof(char*));
        if (words_buffer == NULL || words == NULL) {
                free(words_buffer);
                free(words);
                return NULL;
        }

        int i = 0;
        ptr = str;
        words[i] = words_buffer;
        while (*ptr != '\0') {
                if (*ptr == ';') {
                        *words_buffer = '\0';
                        words_buffer++;
                        i++;
                        words[i] = words_buffer;
                } else {
                        *words_buffer = *ptr;
                        words_buffer++;
                }
                ptr++;
        }
        *words_buffer = '\0';
        i++;
        words[i] = NULL;

        return words;
}

NVD_INTERNAL_FUNCTION void *nvd_malloc(size_t size) {
	void *ptr = malloc(size);
	if (!ptr) {
		nvd_error_message("nvd_malloc: Allocation failed for size %zu, possibly out of memory!", size);
		nvd_set_error(NVD_OUT_OF_MEMORY);
		return NULL;
	}

	return ptr;
}

NVD_INTERNAL_FUNCTION void *nvd_calloc(size_t n_items, size_t size_each) {
        if (size_each > SIZE_MAX / n_items) {
		nvd_error_message(
			"nvd_calloc: Warning: calculating the total allocation size (%zu * %zu) would exceed the maximum capacity of a size_t!",
			n_items, size_each
		);
                /* 
                 * Why are we not returning? Well, see here:
                 * https://drj11.wordpress.com/2008/06/04/calloc-when-multiply-overflows/
                 * The standard also doesn't say much: https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1548.pdf
                 * (go to section 7.22.3.2, the calloc function), nothing there.
                 * So just go ahead and call calloc, and see what it has to say.
                 */
	}

	void *ptr = calloc(n_items, size_each);
	if (!ptr) {
		nvd_error_message(
				"nvd_calloc: Allocation of %zu items of %zu size each (Total: %zu bytes) failed, possibly out of memory!",
				n_items, size_each, (size_t)(n_items * size_each)
		);
		nvd_set_error(NVD_OUT_OF_MEMORY);
		return NULL;
	}
	return ptr;
}

