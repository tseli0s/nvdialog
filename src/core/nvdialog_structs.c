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

#include "nvdialog.h"
#include <stdint.h>
#include <stdbool.h>

struct _NvdDialogBox {
        void *window_handle;
        const char *msg;
        const char *content;
        NvdDialogType type;
};

struct _NvdAboutDialog {
        void* raw;
        char* title, *contents;
        char* version;
        char* hyperlinks[6];
        short amount_of_hyperlinks;
        char* image_name;
        bool image_from_icon;
        void* buttons[4];
        short amount_of_buttons;
        void* layout;
};

struct _NvdFileDialog {
        char* filename, file_extensions;
        bool location_was_chosen;
};

struct _NvdQuestionBox {
        void* window_handle;
        char* title, *contents;
        NvdReply reply;
};

struct _NvdNotification {
        char *title;
        char *contents;
        NvdNotifyType type;
        bool shown;
        void *raw;
        void *lib;
};