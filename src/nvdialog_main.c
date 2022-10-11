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

#include "dialogs/nvdialog_dialog_box.h"
#include "dialogs/nvdialog_file_dialog.h"
#include "nvdialog.h"
#include "nvdialog_assert.h"
#include "nvdialog_error.h"
#include "nvdialog_macros.h"
#ifndef _WIN32
#ifdef NVD_USE_GTK4
#include "backend/adw/nvdialog_adw.h"
#else
#include "backend/adw/nvdialog_gtk.h"
#endif /* NVD_USE_GTK4 */
#else
#include "backend/win32/nvdialog_win32.h"
#endif /* _WIN32 */
#include "nvdialog_types.h"

/*
 * The default domain name used for libadwaita applications.
 * This variable is modified from nvd_set_domain_name().
 */
static char *nvd_domain_name = "io.androgr.libnvdialog";
static char *nvd_argv_0 = NULL;
static NvdParentWindow nvd_parent_window = NULL;

inline void nvd_set_domain_name(char *domain) {
        NVD_ASSERT(domain != NULL);
        nvd_domain_name = domain;
}

inline const char *nvd_get_domain_name(void) { return nvd_domain_name; }

NvdContext *nvd_bind_context(void) { return NULL; }

void nvd_delete_context(NvdContext *ctx) { free(ctx); }

const char *nvd_get_argv() { return nvd_argv_0; }

int nvd_init(char *program) {
#if !defined(_WIN32)
        setlinebuf(stdout); /* Windows doesn't support this call (Yet?) */
        setlinebuf(stderr);
#endif /* _WIN32 */
        nvd_argv_0 = program;
#if !defined(_WIN32) /* On Windows the DISPLAY variable isn't set at all */
        if (!getenv("DISPLAY")) {
                nvd_set_error(NVD_NO_DISPLAY);
                return -1;
        }
/* Apparently in Gtk4 the gtk_init function doesn't require any arguments. */
#if !defined(NVD_USE_GTK4)
        int __argc__ = 1;
        char **__argv__ = {
            &program,
        };
        gtk_init(&__argc__, &__argv__);
#else
        adw_init();
#endif /* NVD_USE_GTK4 */
#endif /* _WIN32 */
        return 0;
}

NvdFileDialog *nvd_open_file_dialog_new(const char *title,
                                        const char *file_extensions) {
#if !defined(_WIN32)
#if !defined(NVD_USE_GTK4)
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
#if !defined(NVD_USE_GTK4)
        NvdDialogBox *dialog = nvd_create_gtk_dialog(title, message, type);
        if (!dialog)
                nvd_set_error(NVD_INTERNAL_ERROR);
        return dialog;
#else
        NvdDialogBox *dialog = nvd_dialog_box_adw(title, message, type);
        if (!dialog)
                nvd_set_error(NVD_INTERNAL_ERROR);
        return dialog;
#endif /* NVD_USE_GTK4 */
#else
        nvd_create_win32_dialog(title, message, type);
        return 0;
#endif /* _WIN32 */
}

NvdQuestionBox *nvd_dialog_question_new(const char *title, const char *question,
                                        NvdQuestionButton button) {
#if !defined(_WIN32)
#if !defined(NVD_USE_GTK4)
        return nvd_question_gtk(title, question, button);
#else
        return nvd_question_adw(title, question, button);
#endif /* NVD_USE_GTK4 */
#else
        return nvd_dialog_question_win32(title, question, button);
#endif /* _WIN32 */
        return NULL;
}

NvdReply nvd_get_reply(NvdQuestionBox *question) {
#if defined(NVD_USE_GTK4)
        return nvd_get_reply_adw(question);
#elif defined(_WIN32)
        return nvd_get_reply_win32(question);
#else
        return nvd_get_reply_gtk(question);
#endif /* NVD_USE_GTK4 */
}

NvdAboutDialog *nvd_about_dialog_new(const char *name, const char *description,
                                     const char *license_text,
                                     const char *logo_path) {
#if defined(_WIN32)
        return nvd_about_dialog_win32(name, description, license_text,
                                      logo_path);
#else
#if !defined(NVD_USE_GTK4)
        return nvd_about_dialog_gtk(name, description, license_text, logo_path);
#else
        return nvd_about_dialog_adw(name, description, logo_path);
#endif /* !NVD_USE_GTK4 */
#endif /* _WIN32 */
}

inline int nvd_set_parent(NvdParentWindow parent) {
        if (!parent)
                return -1;
        else
                nvd_parent_window = parent;
        return 0;
}

NvdParentWindow nvd_get_parent(void) { return nvd_parent_window; }

void nvd_delete_parent() { nvd_parent_window = NULL; }

void nvd_free_object(void *obj) {
        NVD_ASSERT(obj != NULL);
        free(obj);
}

void nvd_show_dialog(NvdDialogBox *dialog) {
#if !defined(_WIN32) && defined(NVD_USE_GTK4)
        nvd_show_dialog_adw(dialog);
#elif defined(_WIN32)
        nvd_show_dialog_win32(dialog);
#elif !defined(NVD_USE_GTK4)
        nvd_show_dialog_gtk(dialog);
#else
        return;
#endif
}

void nvd_show_about_dialog(NvdAboutDialog *dialog) {
#if defined(_WIN32)
        nvd_show_about_dialog_adw(dialog);
#elif defined(NVD_USE_GTK4)
        nvd_show_about_dialog_adw(dialog);
#else
        nvd_show_about_dialog_gtk(dialog);
#endif /* _WIN32 */
}