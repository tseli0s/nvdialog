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

#define _POSIX_C_SOURCE 200809L

#define _CRT_SECURE_NO_WARNINGS 1
#include "dialogs/nvdialog_input_box.h"
#include "nvdialog_typeimpl.h"
#include "nvdialog_string.h"
#include "dialogs/nvdialog_dialog_box.h"
#include "dialogs/nvdialog_file_dialog.h"
#include "nvdialog.h"
#include "nvdialog_assert.h"
#include "nvdialog_error.h"
#include "nvdialog_macros.h"
#ifndef _WIN32
#include <dlfcn.h>
#ifdef NVD_USE_GTK4
#include "backend/adw/nvdialog_adw.h"
#elif defined(NVD_USE_COCOA)
#include "backend/cocoa/nvdialog_cocoa.h"
#elif defined(NVD_HAIKU_TARGET)
#include "backend/hku/nvdialog_hku.h"
#else
#endif /* NVD_USE_GTK4 */
#else
#include "backend/win32/nvdialog_win32.h"
#endif /* _WIN32 */

#include "nvdialog_init.h"
#include "nvdialog_types.h"
#include "nvdialog_util.h"

NVD_THREAD_LOCAL(char *nvd_app_name) = "NvDialog Application";
NVD_THREAD_LOCAL(bool nvd_initialized) = false;
NVD_THREAD_LOCAL(bool nvd_is_process_container) = false;
NVD_THREAD_LOCAL(NvdParentWindow nvd_parent_window) = NULL;

static NvdBackendMask mask = {0};

void nvd_set_application_name(const char *application_name) {
        nvd_app_name = (char *)application_name;
}
const char *nvd_get_application_name() { return nvd_app_name; }
int nvd_set_parent(NvdParentWindow parent) {
        nvd_parent_window = parent;
        return 0;
}
NvdParentWindow nvd_get_parent() { return nvd_parent_window; }

int nvd_init(void) {
        if (nvd_initialized) {
                nvd_set_error(NVD_ALREADY_INITIALIZED);
                return -NVD_ALREADY_INITIALIZED;
        }

#if defined(NVD_SANDBOX_SUPPORT)
        nvd_is_process_container = nvd_is_sandboxed();
#endif
        int result = nvd_init_backends(&mask);
        if (result < 0) {
                nvd_set_error((NvdError)+result);
                return result;
        }

        nvd_initialized = true;
        return 0;
}

void nvd_free_object(void *object) {
        NVD_ASSERT(object != NULL);
        free(object);
}

NvdDialogBox *nvd_dialog_box_new(const char *title, const char *message,
                                 NvdDialogType type) {
        NVD_ASSERT(title != NULL);
        NVD_ASSERT(message != NULL);
        return NVD_CHECK_FUNCTION(mask.dialog_box, title, message, type);
}

void nvd_dialog_box_set_accept_text(NvdDialogBox *dialog, const char *accept_text) {
        NVD_ASSERT(dialog != NULL);
        NVD_ASSERT(accept_text != NULL);
        NVD_TRY_CALL(mask.set_accept_text, dialog, accept_text);
}

void nvd_show_dialog(NvdDialogBox *dialog) {
        NVD_ASSERT(dialog != NULL);
        NVD_TRY_CALL(mask.show_dialog, dialog);
}

NvdInputBox *nvd_input_box_new(const char *title, const char *message) {
        NVD_ASSERT(title != NULL);
        return NVD_CHECK_FUNCTION(mask.input_box, title, message);
}

void nvd_show_input_box(NvdInputBox *box) {
        NVD_ASSERT(box != NULL);
        NVD_TRY_CALL(mask.show_input_box, box);
}

NvdDynamicString *nvd_input_box_get_string(NvdInputBox *box) {
        NVD_ASSERT(box != NULL);
        return NVD_CHECK_FUNCTION(mask.input_box_get_string, box);
}

NvdQuestionBox *nvd_dialog_question_new(const char *title, const char *message,
                                        NvdQuestionButton buttons) {
        NVD_ASSERT(title != NULL);
        NVD_ASSERT(message != NULL);
        return NVD_CHECK_FUNCTION(mask.question, title, message, buttons);
}

NvdReply nvd_get_reply(NvdQuestionBox *question) {
        NVD_ASSERT(question != NULL);
        if (mask.get_reply != NULL)
                return mask.get_reply(question);
        else
                return NVD_REPLY_CANCEL;
}

NvdAboutDialog *nvd_about_dialog_new(const char *title, const char *message,
                                     const char *icon) {
        NVD_ASSERT(title != NULL);
        NVD_ASSERT(message != NULL);
        return NVD_CHECK_FUNCTION(mask.about_dialog, title, message, icon);
}

void nvd_show_about_dialog(NvdAboutDialog *dialog) {
        NVD_ASSERT(dialog != NULL);
        NVD_TRY_CALL(mask.show_about_dialog, dialog);
}

void nvd_about_dialog_set_version(NvdAboutDialog *dialog, const char *version) {
        NVD_ASSERT(dialog != NULL);
        NVD_TRY_CALL(mask.about_dialog_set_version, dialog, version);
}

void nvd_about_dialog_set_license(NvdAboutDialog *dialog, const char *license,
                                  const char *url) {
        NVD_ASSERT(dialog != NULL);
        NVD_TRY_CALL(mask.about_dialog_set_license, dialog, license, url);
}

void nvd_dialog_set_icon(NvdAboutDialog *dialog, NvdImage *image) {
        NVD_ASSERT(dialog != NULL);
        NVD_ASSERT(image != NULL);
        dialog->image = image;
        dialog->image_from_icon = false;
        dialog->image_name = NULL;
}

NvdFileDialog *nvd_open_file_dialog_new(const char *title,
                                        const char *file_extensions) {
        NVD_ASSERT(title != NULL);
        return NVD_CHECK_FUNCTION(mask.open_file_dialog, title,
                                  file_extensions);
}

NvdFileDialog *nvd_save_file_dialog_new(const char *title,
                                        const char *default_filename) {
        NVD_ASSERT(title != NULL);
        return NVD_CHECK_FUNCTION(mask.save_file_dialog, title,
                                  default_filename);
}

NvdFileDialog *nvd_open_folder_dialog_new(const char *title,
                                          const char *default_filename) {
        NVD_ASSERT(title != NULL);
        return NVD_CHECK_FUNCTION(mask.open_folder_dialog, title,
                                  default_filename);
}

NvdDynamicString *nvd_get_file_location(NvdFileDialog *dialog) {
        NVD_ASSERT(dialog != NULL);
        return NVD_CHECK_FUNCTION(mask.get_file_location, dialog);
}

void *nvd_open_file_dialog_get_raw(NvdFileDialog *dialog) {
        return dialog->raw;
}

NvdNotification *nvd_notification_new(const char *title, const char *msg,
                                      NvdNotifyType type) {
        NVD_ASSERT(title != NULL);
        NVD_ASSERT(msg != NULL);
        return NVD_CHECK_FUNCTION(mask.notification, title, msg, type);
}

void nvd_send_notification(NvdNotification *notification) {
        NVD_ASSERT(notification != NULL);
        NVD_ASSERT(notification->raw != NULL);
        NVD_TRY_CALL(mask.send_notification, notification);
}

void nvd_delete_notification(NvdNotification *notification) {
        NVD_ASSERT(notification != NULL);
        if (notification->destructor) notification->destructor(notification);
        free(notification);
}

void nvd_add_notification_action(NvdNotification *notification,
                                 const char *action, int value_to_set,
                                 int *value_to_return) {
        NVD_ASSERT(notification != NULL);
        NVD_ASSERT(action != NULL);
        NVD_ASSERT(value_to_return != NULL);
        NVD_TRY_CALL(mask.add_notification_action, notification, action,
                     value_to_set, value_to_return);
}
