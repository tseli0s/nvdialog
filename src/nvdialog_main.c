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

#include "nvdialog_assert.h"
#include "nvdialog_error.h"
#include <stdint.h>
#include <stdio.h>
#ifndef _WIN32
#include "backend/nvdialog_adw.h"
#include "backend/nvdialog_gtk.h"
#endif /* _WIN32 */

#if defined(_WIN32)
#include "backend/nvdialog_win32.h"
#endif /* _WIN32 */

#include "nvdialog.h"
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct _NvdDialogBox {
        void *window_handle;
        const char *msg;
        const char *content;
        NvdDialogType type;
};

struct _NvdContext {
        AdwApplication *application;
        bool initialized, ready;
        const char *domain;
        uint32_t flags;
};

/*
 * The default domain name used for libadwaita applications.
 * This variable is modified from nvd_set_domain_name().
 */
static char *nvd_domain_name = "io.androgr.libnvdialog";

inline int nvd_set_domain_name(char *domain) { nvd_domain_name = domain; }

NvdContext *nvd_bind_context(void) {
        return NULL; /* Currently unimplemented, awaiting for libadwaita
                        backend. */
}

int nvd_init(char *program) {
#ifndef _WIN32
        if (!getenv("DISPLAY")) {
                nvd_set_error(NVD_NO_DISPLAY);
                NVD_PRINT_CURRENT_ERROR;
                return -1;
        }
/* Apparently in Gtk4 the gtk_init function doesn't require any arguments. */
#ifndef NVD_USE_GTK4
        int __argc__ = 1;
        char **__argv__ = {
            &program,
        };
        gtk_init(&__argc__, &__argv__);
#else
        gtk_init();
#endif /* NVD_USE_GTK4 */
#endif /* _WIN32 */
        return 0;
}

const char *nvd_open_file_dialog_new(const char *title,
                                     const char *file_extensions) {
#if !defined(_WIN32)
#ifndef NVD_USE_GTK4
        const char *data = nvd_open_file_dialog_gtk(title, file_extensions);
        return data;
#else
        return nvd_open_file_dialog_adw(title, file_extensions);
#endif /* NVD_USE_GTK4 */
#else
        return nvd_open_file_dialog_win32(title, file_extensions);
#endif /* _WIN32 */
}

NvdDialogBox *nvd_dialog_box_new(const char *title, const char *message,
                                 NvdDialogType type) {
#if !defined(_WIN32)
#ifndef NVD_USE_GTK4
        NvdDialogBox *dialog = nvd_create_gtk_dialog(title, message, type);
        if (!dialog)
                nvd_set_error(NVD_INTERNAL_ERROR);
        return dialog;
#else
        NvdDialogBox *dialog = nvd_create_adw_dialog(title, message, type);
        if (!dialog)
                nvd_set_error(NVD_INTERNAL_ERROR);
        return dialog;
#endif /* NVD_USE_GTK4 */
#else
        nvd_create_win32_dialog(title, message, type);
#endif /* _WIN32 */
}

NvdReply nvd_dialog_question_new(const char *title, const char *question,
                                 NvdQuestionButton button) {
#if !defined(_WIN32)
#if !defined(NVD_USE_GTK4)
        return nvd_question_gtk(title, question, button);
#else
        return 0; /* Unimplemented */
#endif /* NVD_USE_GTK4 */
#else
        nvd_question_win32(title, question, button);
#endif /* _WIN32 */
        return -1;
}