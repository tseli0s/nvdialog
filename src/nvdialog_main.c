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

#include "backend/nvdialog_adw.h"
#include "backend/nvdialog_gtk.h"
#include "nvdialog.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct NvdDialogBox {
        void *window_handle;
        const char *msg;
        const char *content;
        NvdDialogType type;
};

uint32_t nvd_init(char *program) {
        int __argc = 1;
        char **__argv = {
            &program,
        };
        gtk_init(&__argc, &__argv);
}

NvdDialogBox *nvd_dialog_box_new(const char *title, const char *message,
                                 NvdDialogType type) {
#if !defined(_WIN32)
#ifdef __NVDIALOG_EXPERIMENTAL
        if (getenv("NVDIALOG_USE_LEGACY_GTK") &&
            !strcmp(getenv("NVDIALOG_USE_LEGACY_GTK"), "1")) {
#endif /* __NVDIALOG_EXPERIMENTAL */
                void *dialog = nvd_create_gtk_dialog(title, message, type);
                assert(dialog != NULL);
#ifdef __NVDIALOG_EXPERIMENTAL
        } else {
#endif /* __NVDIALOG_EXPERIMENTAL */
                // void *__dialog = nvd_create_adw_dialog(title, message, type);
                // assert(__dialog != NULL);
#ifdef __NVDIALOG_EXPERIMENTAL
        }
#endif /* __NVDIALOG_EXPERIMENTAL */
#endif /* _WIN32 */
}