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
#include <stdlib.h>
#include <wchar.h>

#include "impl/nvdialog_typeimpl.h"
#include "nvdialog_assert.h"
#include "nvdialog_error.h"
#include "nvdialog_string.h"
#include "nvdialog_util.h"
#include "nvdialog_widestr.h"

#define NVD_DEFAULT_WSTRING_LEN (48)

/* Apparently things are different between Unix and Windows so we have to do
 * this by hand for some platforms. Might as well do it for all of them. */
static wchar_t *nvd_strdup_wide(const wchar_t *str) {
	if (!str) return NULL;
	size_t len = wcslen(str);
	wchar_t *buffer = nvd_malloc((len + 1) * sizeof(wchar_t));

	memcpy(buffer, str, (len + 1) * sizeof(wchar_t));
	return buffer;
}

NvdWideString *nvd_wide_string_new(const wchar_t *buffer) {
	NvdWideString *string = nvd_calloc(1, sizeof(NvdWideString));
	NVD_ASSERT(string != NULL);

	if (buffer) {
		string->buffer = nvd_strdup_wide(buffer);
		string->len = wcslen(buffer);
		string->mem_usage =
			string->len * sizeof(wchar_t) + sizeof(wchar_t);
	} else {
		size_t allocsize = (NVD_DEFAULT_WSTRING_LEN * sizeof(wchar_t));
		string->buffer = nvd_malloc(allocsize + sizeof(wchar_t));
		string->len = 0;
		string->mem_usage = allocsize + sizeof(wchar_t);
		nvd_zero_memory(string->buffer, allocsize + sizeof(wchar_t));
	}

	return string;
}

NvdDynamicString *nvd_wide_to_c_str(NvdWideString *str) {
	if (!str || !str->buffer) return NULL;

	size_t needed = wcstombs(NULL, str->buffer, 0);
	if (needed == (size_t)-1) return NULL;

	char *buffer = nvd_malloc(needed + 1);
	wcstombs(buffer, str->buffer, needed + 1);

	NvdDynamicString *out = nvd_string_new(buffer);
	free(buffer);
	return out;
}

NVD_API size_t nvd_wide_strlen(NvdWideString *string) {
	if (!string) return 0;
	return wcslen(string->buffer);
}

wchar_t *nvd_get_internal_wide_string(NvdWideString *str) {
	if (!str) return NULL;
	return str->buffer;
}

void nvd_delete_wide_string(NvdWideString *str) {
	if (!str) return;

	if (str->buffer) free(str->buffer);

	free(str);
}
