/*
 *  The MIT License (MIT)
 *
 *  Copyright (c) 2024 Aggelos Tselios
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

#include "nvdialog.h"
#include "dialogs/nvdialog_dialog_box.h"
#include "dialogs/nvdialog_file_dialog.h"
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

#if defined(linux) || defined(__linux__) || defined(__linux)
#if defined(NVD_SANDBOX_SUPPORT)
#include "backend/sandbox/nvdialog_sbx.h"
#endif /* NVD_SANDBOX_SUPPORT */
#endif /* linux */

#include "impl/nvdialog_typeimpl.h"
#include "nvdialog_types.h"
#include "nvdialog_util.h"
#include <stdint.h>

/* Safeguard for Windows basically, since CMake handles other platforms. Thanks MSVC :) */
#if __STDC_VERSION__ <= 2011L || !defined(__STDC_VERSION__)
#error NvDialog needs to be built using C11. If your compiler does not support it, you should use another version.
#endif /* __STDC_VERSION__ */

/* 
 * A helper macro to check if NvDialog has been
 * initialized before proceeding with the actual implementation.
 */
#define NVD_IF_NOT_INITIALIZED(...) \
        if (nvd_initialized != true) { \
                NVD_ASSERT(nvd_initialized == true); \
                nvd_set_error(NVD_NOT_INITIALIZED); \
                __VA_ARGS__ ; \
        }

NVD_THREAD_LOCAL(char* nvd_app_name               ) = "NvDialog Application";
NVD_THREAD_LOCAL(bool nvd_initialized             ) = false;
NVD_THREAD_LOCAL(bool nvd_is_process_container    ) = false;
NVD_THREAD_LOCAL(NvdParentWindow nvd_parent_window) = NULL;
NVD_THREAD_LOCAL(char* nvd_libnotify_path         ) = NULL; // Initialized in nvd_init

const char *nvd_get_argv() { return NULL; }

static int nvd_check_libnotify(void) {
        #if defined (NVD_USE_GTK4) || defined (NVD_PLATFORM_LINUX)
        void *lib = dlopen(nvd_libnotify_path, RTLD_LAZY);
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
        nvd_initialized = true;
        return 0;
}

int nvd_init() {
        if (nvd_initialized) {
                nvd_set_error(NVD_ALREADY_INITIALIZED);
                return -NVD_ALREADY_INITIALIZED;
        }
        #if defined(NVD_SANDBOX_SUPPORT)
        nvd_is_process_container = nvd_is_sandboxed();
        if (nvd_is_process_container) {
                nvd_error_message("NOTE: NvDialog has detected being run in a container. "
                                  "This is still a work in progress.");
        }
        #endif /* NVD_SANDBOX_SUPPORT */
#if defined (__linux__)
        nvd_libnotify_path = nvd_get_libnotify_path();
        if (!nvd_libnotify_path) {
                nvd_error_message("nvd_libnotify_path is NULL, setting it to /usr/lib/libnotify.so as a fallback.");
                nvd_libnotify_path = "/usr/lib/libnotify.so";
        }

        setlinebuf(stdout); /* Windows doesn't support this call (Yet?) */
        setlinebuf(stderr);
#endif /* __linux__ */
#if !defined(_WIN32) && !defined(NVD_USE_COCOA)

#if !defined(NVD_USE_GTK4)
        if (!gtk_init_check(NULL, NULL)) {
                if (!getenv("DISPLAY")) nvd_set_error(NVD_NO_DISPLAY);
                else nvd_set_error(NVD_BACKEND_FAILURE);
                return (int) -nvd_get_error();
        }

        if (getenv("NVD_NO_NOTIFS") == NULL || atoi(getenv("NVD_NO_NOTIFS"))) {
                /* Since this function used to be inlined here, make it easy for us and just return what it returns. */
                return nvd_check_libnotify();
        }
#else
        int result = 0;
        if (!gtk_init_check()) {
                /*
                 * Most likely a Gtk4 failure occurs because there's no display.
                 * Since Gtk won't just tell us what went wrong we'll assume that
                 * the display is not available.
                 */
                nvd_set_error(NVD_NO_DISPLAY);
                return -NVD_NO_DISPLAY;
        }
        if (getenv("NVD_NO_NOTIFS") == NULL || atoi(getenv("NVD_NO_NOTIFS"))) {
                /* Since this function used to be inlined here, make it easy for us and just return what it returns. */
                result = nvd_check_libnotify();
        }
        adw_init();
        nvd_initialized = true;
        return result;
#endif /* NVD_USE_GTK4 */
#endif /* _WIN32 && NVD_USE_COCOA */

        nvd_initialized = true;
        return 0;
}

NVD_INTERNAL_FUNCTION const char* nvd_path_to_libnotify() {
        return nvd_libnotify_path;
}

void nvd_set_application_name(const char *application_name) {
        nvd_app_name = (char*) application_name;
}

const char *nvd_get_application_name() { return nvd_app_name; }

NvdFileDialog *nvd_open_file_dialog_new(const char *title,
                                        const char *file_extensions) {
        NVD_IF_NOT_INITIALIZED(return NULL);

        #if defined(__linux__) && !defined(NVD_USE_GTK4)
        if (nvd_is_process_container) return nvd_open_file_dialog_sbx(title, file_extensions);
        else return nvd_open_file_dialog_gtk(title, file_extensions);
        
        #elif defined(__linux__) && defined(NVD_USE_GTK4)
        return nvd_open_file_dialog_adw(title, file_extensions);

        #elif defined(__APPLE__)
        return nvd_open_file_dialog_cocoa(title, file_extensions);

        #elif defined(_WIN32)
        return nvd_open_file_dialog_win32(title, file_extensions);

        #else
        #error Unable to find appropriate backend implementation.
        #endif /* __linux__ */
}

NvdDialogBox *
nvd_dialog_box_new(const char *title, const char *message, NvdDialogType type) {
        NVD_IF_NOT_INITIALIZED(return NULL);

        #if defined(__linux__) && !defined(NVD_USE_GTK4)
        if (nvd_is_process_container) return nvd_dialog_box_sbx(title, message, type);
        else return nvd_dialog_box_gtk(title, message, type);
        
        #elif defined(__linux__) && defined(NVD_USE_GTK4)
        return nvd_dialog_box_adw(title, message, type);

        #elif defined(__APPLE__)
        return nvd_dialog_box_cocoa(title, message, type);

        #elif defined(_WIN32)
        return nvd_dialog_box_win32(title, message, type);

        #else
        #error Unable to find appropriate backend implementation.
        #endif /* __linux__ */
}

NvdQuestionBox *nvd_dialog_question_new(const char       *title,
                                        const char       *question,
                                        NvdQuestionButton button) {
        NVD_IF_NOT_INITIALIZED(return NULL);

        #if defined(__linux__) && !defined(NVD_USE_GTK4)
        if (nvd_is_process_container) return nvd_question_sbx(title, question, button);
        else return nvd_question_gtk(title, question, button);
        
        #elif defined(__linux__) && defined(NVD_USE_GTK4)
        return nvd_question_adw(title, question, button);

        #elif defined(__APPLE__)
        return nvd_question_cocoa(title, question, button);

        #elif defined(_WIN32)
        return nvd_question_win32(title, question, button);

        #else
        #error Unable to find appropriate backend implementation.
        #endif /* __linux__ */
}

/*
 * FIXME: NvdReply, like all enums, does not have an "invalid" variant to be used when
 * the library fails. This leaves failing code to be used like everything went fine.
 * In this case, we are working around this by casting a negative variant of NvdError
 * into the return type and returning it.
 * The best solution is to simply add new variants into those enums. The next best
 * solution is to assert that the reply is actually valid.
 */
NvdReply nvd_get_reply(NvdQuestionBox *question) {
        NVD_IF_NOT_INITIALIZED(return ((NvdReply) -NVD_NOT_INITIALIZED));
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
        NVD_IF_NOT_INITIALIZED(return NULL);
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

int nvd_set_parent(NvdParentWindow parent) {
        if (!parent) return -1;
        else nvd_parent_window = parent;
        return 0;
}

NvdParentWindow nvd_get_parent(void) { return nvd_parent_window; }

void nvd_delete_parent() { nvd_parent_window = NULL; }

void nvd_free_object(void *obj) {
        NVD_ASSERT(obj != NULL);
        free(obj);
}

void nvd_show_dialog(NvdDialogBox *dialog) {
        NVD_ASSERT(dialog != NULL);
        NVD_IF_NOT_INITIALIZED(return);
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
        NVD_ASSERT(dialog != NULL);
        NVD_IF_NOT_INITIALIZED(return);
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
        NVD_ASSERT(dialog != NULL);
        NVD_IF_NOT_INITIALIZED(return);

        if (!version) return;
#if defined(NVD_USE_GTK4)
        nvd_about_dialog_set_version_adw(dialog, version);
#elif defined(_WIN32) || defined(NVD_USE_COCOA)
#else
        nvd_about_dialog_set_version_gtk(dialog, version);
#endif /* NVD_USE_GTK4 */
}

void nvd_get_file_location(NvdFileDialog *dialog, const char **savebuf) {
        NVD_ASSERT(dialog != NULL);
        NVD_IF_NOT_INITIALIZED(return);
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
        NVD_ASSERT(title != NULL);
        NVD_IF_NOT_INITIALIZED(return NULL);
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
        NVD_IF_NOT_INITIALIZED(return);
        NVD_ASSERT_FATAL(dialog != NULL);
        NVD_ASSERT(license_link != NULL);
        NVD_ASSERT(txt != NULL);
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
        NVD_IF_NOT_INITIALIZED(return NULL);
        NVD_ASSERT(title != NULL);
        NVD_ASSERT(msg != NULL);

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
        if (notification->destructor)
                notification->destructor(notification);
        free(notification);
}

void nvd_send_notification(NvdNotification *notification) {
        NVD_IF_NOT_INITIALIZED(return);
        NVD_ASSERT(notification != NULL);
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

void *nvd_dialog_box_get_raw(NvdDialogBox *dialog) {
        NVD_ASSERT_FATAL(dialog != NULL);
        NVD_IF_NOT_INITIALIZED(return NULL);
        return dialog->window_handle;
}

void *nvd_about_dialog_get_raw(NvdAboutDialog *dialog) {
        NVD_ASSERT_FATAL(dialog != NULL);
        NVD_IF_NOT_INITIALIZED(return NULL);
        return dialog->raw;
}

void *nvd_dialog_question_get_raw(NvdQuestionBox *dialog) {
        NVD_ASSERT_FATAL(dialog != NULL);
        NVD_IF_NOT_INITIALIZED(return NULL);
        return dialog->window_handle;
}

void *nvd_open_file_dialog_get_raw(NvdFileDialog *dialog) {
        NVD_ASSERT_FATAL(dialog != NULL);
        NVD_IF_NOT_INITIALIZED(return NULL);
        return dialog->raw;
}

void nvd_add_notification_action(NvdNotification* notification,
                                 const char* action,
                                 int  value_to_set,
                                 int* value_to_return) {
        NVD_IF_NOT_INITIALIZED(return);
        NVD_ASSERT(action != NULL);
        NVD_ASSERT(value_to_return != NULL);
        
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

void nvd_dialog_box_set_accept_text(NvdDialogBox* dialog, const char* text) {
	NVD_ASSERT(text != NULL); // Not fatal because some backends may allow it. Although discouraged.
	dialog->accept_label = (char*) text;
	#if defined(__linux__) || defined(linux)
        #if !defined(NVD_USE_GTK4)
	nvd_gtk_update_accept_label(dialog);
        #else
        // TODO: Implement this for libadwaita too
        #endif /* NVD_USE_GTK4 */
	#endif /* __linux__ */
}
