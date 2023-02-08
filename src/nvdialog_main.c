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

/* 
 * As honest as I can, I couldn't care less
 * about safety from a 30 year old function.
 */
#define _CRT_SECURE_NO_WARNINGS

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
#elif NVD_USE_COCOA
#include "backend/cocoa/nvdialog_cocoa.h"
#else
#include "backend/gtk/nvdialog_gtk.h"
#endif /* NVD_USE_GTK4 */
#else
#include "backend/win32/nvdialog_win32.h"
#endif /* _WIN32 */
#include "nvdialog_types.h"
#include <stdint.h>

static char *nvd_app_name = "NvDialog Application";
static char *nvd_argv_0   = NULL;

static bool nvd_initialized              = false;
static NvdParentWindow nvd_parent_window = NULL;
static uint8_t nvd_times_initialized     = 0;

const char *nvd_get_argv() { return nvd_argv_0; }

static int nvd_check_libnotify(void) {
        #if defined (NVD_USE_GTK4) || defined (NVD_PLATFORM_LINUX)
        void *lib = dlopen("/usr/lib/libnotify.so", RTLD_LAZY);
        if (!lib) {
                nvd_error_message("Couldn't load libnotify.so: %s", dlerror());
                return -1;
        } else {
                /* 
                 * This is just to check if we can use libnotify, and stop here if not
                 * instead of causing it later in the program.
                 */
                gboolean (*nvd_notify_init)(char*) = dlsym(lib, "notify_init");
                if (!nvd_notify_init) {
                        dlclose(lib);
                        nvd_error_message("libnotify is missing 'notify_init' symbol (Perhaps incompatible version?): %s", dlerror());
                        return -1;
                }

                if (!nvd_notify_init(nvd_app_name)) {
                        dlclose(lib);
                        nvd_error_message("Checking libnotify failed.");
                        return -1;
                }
        }
        dlclose(lib); /* We are going to load it seperately once needed. */
        #endif /* NVD_USE_GTK4 || NVD_PLATFORM_LINUX */
        return 0;
}

int nvd_init(char *program) {
        if (nvd_initialized) {
                nvd_set_error(NVD_ALREADY_INITIALIZED);
                return -NVD_ALREADY_INITIALIZED;
        }
#if defined (__linux__)
        setlinebuf(stdout); /* Windows doesn't support this call (Yet?) */
        setlinebuf(stderr);
#endif /* __linux__ */
        nvd_argv_0 = program;
#if !defined(_WIN32) && !defined(NVD_USE_COCOA)

/* Apparently in Gtk4 the gtk_init function doesn't require any arguments. */
#if !defined(NVD_USE_GTK4)
        int    __argc__ = 1;
        char **__argv__ = {
            &program,
        };
        gtk_init(&__argc__, &__argv__);

        if (getenv("NVD_NO_NOTIFS") == NULL || atoi(getenv("NVD_NO_NOTIFS"))) {
                /* Since this function used to be inlined here, make it easy for us and just return what it returns. */
                return nvd_check_libnotify();
        }
#else
        if (getenv("NVD_NO_NOTIFS") == NULL || atoi(getenv("NVD_NO_NOTIFS"))) {
                /* Since this function used to be inlined here, make it easy for us and just return what it returns. */
                return nvd_check_libnotify();
        }
        adw_init();
#endif /* NVD_USE_GTK4 */
#endif /* _WIN32 && NVD_USE_COCOA */
        nvd_initialized = true;
        return 0;
}

void nvd_set_application_name(const char *application_name) {
        nvd_app_name = (char*) application_name;
}

const char *nvd_get_application_name() { return nvd_app_name; }

NvdFileDialog *nvd_open_file_dialog_new(const char *title,
                                        const char *file_extensions) {
#if !defined(_WIN32) && !defined(NVD_USE_COCOA)
#if !defined(NVD_USE_GTK4)
        return nvd_open_file_dialog_gtk(title, file_extensions);
#else
        return nvd_open_file_dialog_adw(title, file_extensions);
#endif /* NVD_USE_GTK4 */
#elif defined(NVD_USE_COCOA)
	return nvd_open_file_dialog_cocoa(title, file_extensions);
#else
        return nvd_open_file_dialog_win32(title, file_extensions);
#endif /* _WIN32 && NVD_USE_COCOA */
}

NvdDialogBox *
nvd_dialog_box_new(const char *title, const char *message, NvdDialogType type) {
#if !defined(_WIN32) && !defined(NVD_USE_COCOA)
#if !defined(NVD_USE_GTK4)
        NvdDialogBox *dialog = nvd_dialog_box_gtk(title, message, type);
        if (!dialog)
                nvd_set_error(NVD_INTERNAL_ERROR);
        return dialog;
#else
        NvdDialogBox *dialog = nvd_dialog_box_adw(title, message, type);
        if (!dialog)
                nvd_set_error(NVD_INTERNAL_ERROR);
        return dialog;
#endif /* NVD_USE_GTK4 */
#elif defined(NVD_USE_COCOA)
	return nvd_dialog_box_cocoa(title, message, type);
#else
        return nvd_dialog_box_win32(title, message, type);
#endif /* _WIN32 && NVD_USE_COCOA */
}

NvdQuestionBox *nvd_dialog_question_new(const char       *title,
                                        const char       *question,
                                        NvdQuestionButton button) {
#if !defined(_WIN32) && !defined(NVD_USE_COCOA)
#if !defined(NVD_USE_GTK4)
        return nvd_question_gtk(title, question, button);
#else
        return nvd_question_adw(title, question, button);
#endif /* NVD_USE_GTK4 */
#elif defined(NVD_USE_COCOA)
	return nvd_question_cocoa(title, question, button);
#else
        return nvd_question_win32(title, question, button);
#endif /* _WIN32 */
        return NULL;
}

NvdReply nvd_get_reply(NvdQuestionBox *question) {
#if defined(NVD_USE_GTK4)
        return nvd_get_reply_adw(question);
#elif defined(NVD_USE_COCOA)
	return nvd_get_reply_cocoa(question);
#elif defined(_WIN32)
        return nvd_get_reply_win32(question);
#else
        return nvd_get_reply_gtk(question);
#endif /* NVD_USE_GTK4 */
}

NvdAboutDialog *nvd_about_dialog_new(const char *name,
                                     const char *description,
                                     const char *logo_path) {
#if defined(_WIN32)
        return nvd_about_dialog_win32(name, description, logo_path);
#elif defined(NVD_USE_COCOA)
	return nvd_about_dialog_cocoa(name, description, logo_path);
#else
#if !defined(NVD_USE_GTK4)
        return nvd_about_dialog_gtk(name, description, logo_path);
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
#elif defined(NVD_USE_COCOA)
	nvd_show_dialog_cocoa(dialog);
#elif !defined(NVD_USE_GTK4)
        nvd_show_dialog_gtk(dialog);
#else
        return;
#endif
}

void nvd_show_about_dialog(NvdAboutDialog *dialog) {
#if defined(_WIN32)
        nvd_show_about_dialog_win32(dialog);
#elif defined(NVD_USE_COCOA)
	return;
#elif defined(NVD_USE_GTK4)
        nvd_show_about_dialog_adw(dialog);
#else
        nvd_show_about_dialog_gtk(dialog);
#endif /* _WIN32 */
}

void nvd_about_dialog_set_version(NvdAboutDialog *dialog, const char *version) {
#if defined(NVD_USE_GTK4)
        nvd_about_dialog_set_version_adw(dialog, version);
#elif defined(_WIN32) || defined(NVD_USE_COCOA)
#else
        nvd_about_dialog_set_version_gtk(dialog, version);
#endif /* NVD_USE_GTK4 */
}

void nvd_get_file_location(NvdFileDialog *dialog, const char **savebuf) {
#if defined(_WIN32)
        nvd_get_file_location_win32(dialog, savebuf);
#elif defined(NVD_USE_COCOA)
	nvd_get_file_location_cocoa(dialog, savebuf);
#elif defined(NVD_USE_GTK4)
        nvd_get_file_location_adw(dialog, (char**) savebuf);
#else
        nvd_get_file_location_gtk(dialog, savebuf);
#endif /* _WIN32 */
}

NvdFileDialog *nvd_save_file_dialog_new(const char *title,
                                        const char *default_filename) {
#if defined(_WIN32)
        return nvd_save_file_dialog_win32(title, default_filename);
#elif defined(NVD_USE_COCOA)
	return nvd_save_file_dialog_cocoa(title, default_filename);
#elif defined(NVD_USE_GTK4)
        return nvd_save_file_dialog_adw(title, default_filename);
#else
        return nvd_save_file_dialog_gtk(title, default_filename);
#endif /* _WIN32 */
}

void nvd_about_dialog_set_license_link(NvdAboutDialog *dialog,
                                       const char *license_link,
                                       const char *txt) {
#if defined  (_WIN32)
        nvd_about_dialog_set_license_link_win32(dialog, license_link, txt);
#elif defined(NVD_USE_COCOA)
	nvd_about_dialog_set_licence_link_cocoa(dialog, license_link, txt);
#elif defined(NVD_USE_GTK4)
        nvd_about_dialog_set_license_link_adw(dialog, license_link, txt);
#else
        nvd_about_dialog_set_license_link_gtk(dialog, license_link, txt);
#endif
}

NvdNotification *nvd_notification_new(const char *title,
                                      const char *msg,
                                      NvdNotifyType type) {
#if   defined(_WIN32)
        return nvd_notification_win32(title, msg, type);
#elif defined(NVD_USE_COCOA)
	return nvd_notification_cocoa(title, msg, type);
#elif defined(NVD_USE_GTK4)
        return nvd_notification_adw(title, msg, type);
#else
        return nvd_notification_gtk(title, msg, type);
#endif /* _WIN32 */
}

void nvd_delete_notification(NvdNotification *notification) {
        NVD_ASSERT(notification != NULL);
        free(notification); /* TODO: For each backend, handle cleanup properly. */
}

void nvd_send_notification(NvdNotification *notification) {
#if   defined(_WIN32)
        nvd_send_notification_win32(notification);
#elif defined(NVD_USE_COCOA)
	nvd_send_notification_cocoa(notification);
#elif defined(NVD_USE_GTK4)
        nvd_send_notification_adw(notification);
#else
        nvd_send_notification_gtk(notification);
#endif /* _WIN32 */
}

NvdCSSBackend nvd_get_css_backend() {
#if   defined(NVD_USE_GTK4)
        return NVD_GTK4_CSS_BACKEND;
#elif defined(_WIN32) || defined(NVD_USE_COCOA)
        return NVD_NO_CSS_BACKEND;
#else
        return NVD_GTK3_CSS_BACKEND;
#endif /* NVD_USE_GTK4 */
}

NvdCSSManager *nvd_css_manager_new() {
#if   defined(NVD_USE_GTK4)
        return nvd_css_manager_adw();
#elif defined(_WIN32) || defined(NVD_USE_COCOA)
        return NULL;
#else
        return nvd_css_manager_gtk();
#endif /* NVD_USE_GTK4 */
}

int nvd_css_manager_attach_stylesheet(NvdCSSManager *mgr, const char *filename) {
#if   defined(NVD_USE_GTK4)
        return nvd_css_manager_attach_stylesheet_adw(mgr, filename);
#elif defined(_WIN32) || defined(NVD_USE_COCOA)
        nvd_set_error(NVD_BACKEND_INVALID);
        return -1;
#else
        return nvd_css_manager_attach_stylesheet_gtk(mgr, filename);
#endif /* NVD_USE_GTK4 */
}

int nvd_css_manager_use_style(NvdCSSManager *mgr, void *raw_handle) {
#if   defined(NVD_USE_GTK4)
        return nvd_css_manager_use_style_adw(mgr, raw_handle);
#elif defined(_WIN32) || defined(NVD_USE_COCOA)
        nvd_set_error(NVD_BACKEND_INVALID);
        return -1;
#else
        return nvd_css_manager_use_style_gtk(mgr, raw_handle);
#endif /* NVD_USE_GTK4 */
}

void *nvd_dialog_box_get_raw(NvdDialogBox *dialog) {
#if     defined(NVD_USE_GTK4)
        return nvd_dialog_box_get_raw_adw(dialog);
#elif defined(NVD_USE_COCOA)
	return nvd_dialog_box_get_raw_cocoa(dialog);
#elif   defined(_WIN32)
        return NULL;
#else
        return nvd_dialog_box_get_raw_gtk(dialog);
#endif  /* NVD_USE_GTK4 */
}

void *nvd_about_dialog_get_raw(NvdAboutDialog *dialog) {
#if     defined(NVD_USE_GTK4)
        return nvd_about_dialog_get_raw_adw(dialog);
#elif   defined(_WIN32)
        return NULL; /* Windows dialogs are created immediately, no windows are held beforehand. */
#elif   defined(NVD_USE_COCOA)
        return nvd_about_dialog_get_raw_cocoa(dialog);
#else
        return nvd_about_dialog_get_raw_gtk(dialog);
#endif  /* NVD_USE_GTK4 */
}

void *nvd_dialog_question_get_raw(NvdQuestionBox *dialog) {
#if     defined(NVD_USE_GTK4)
        return nvd_dialog_question_get_raw_adw(dialog);
#elif   defined(NVD_USE_COCOA)
	return nvd_dialog_question_get_raw_cocoa(dialog);
#elif   defined(_WIN32)
        return NULL;
#else
        return nvd_dialog_question_get_raw_gtk(dialog);
#endif  /* NVD_USE_GTK4 */
}

void *nvd_open_file_dialog_get_raw(NvdFileDialog *dialog) {
#if     defined(NVD_USE_GTK4)
        return nvd_open_file_dialog_get_raw_adw(dialog);
#elif defined(NVD_USE_COCOA)
	return nvd_open_file_dialog_get_raw_cocoa(dialog);
#elif   defined(_WIN32)
        return NULL;
#else
        return nvd_open_file_dialog_get_raw_gtk(dialog);
#endif  /* NVD_USE_GTK4 */
}

void nvd_add_notification_action(NvdNotification* notification,
                                 const char* action,
                                 int  value_to_set,
                                 int* value_to_return) {
#if defined(NVD_USE_GTK4)
        nvd_add_notification_action_adw(notification, action, value_to_set, value_to_return);
#elif defined(NVD_USE_COCOA)
        nvd_add_notification_action_cocoa(notification, action, value_to_set, value_to_return);
#elif defined(_WIN32)
        nvd_add_notification_action_win32(notification, action, value_to_set, value_to_return);
#else
        return nvd_add_notification_action_gtk(notification, action, value_to_set, value_to_return);
#endif /* NVD_USE_GTK4 */
}
