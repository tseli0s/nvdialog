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
#include "nvdialog_win32.h"
#include <stdlib.h>

NvdInputBox *nvd_input_box_win32(const char *title, const char *message) {
        NvdInputBox *obj = malloc(sizeof(NvdInputBox));
        const char *default_msg = "Enter your text below...";
        obj->title = nvd_string_new(title);
        if (!message)
                obj->content = nvd_string_new(default_msg);
        else
                obj->content = nvd_string_new(message);

        obj->window_handle = NULL;
        obj->user_input = NULL;
}

void nvd_show_input_box_win32(NvdInputBox *box) {
        return; // todo
}

NvdDynamicString *nvd_input_box_get_string_win32(NvdInputBox *box) {
        return box->window_handle;
}
