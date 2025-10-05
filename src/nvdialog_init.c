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

#include "nvdialog_init.h"

#include <string.h>
#include "nvdialog_dialog.h"
#include "nvdialog_error.h"
#if defined(NVD_USE_GTK4)
#define NVD_GTK4_IMPL
#include "backend/adw/nvdialog_adw.h"
#include <gtk/gtk.h>
#elif defined(_WIN32)
#define NVD_WIN32_IMPL 1
#include "backend/win32/nvdialog_win32.h"
#elif defined(NVD_USE_COCOA)
#define NVD_COCOA_IMPL
#include "backend/cocoa/nvdialog_cocoa.h"
#elif defined(NVD_HAIKU_TARGET)
#include "backend/hku/nvdialog_hku.h"
#else
#define NVD_GTK3_IMPL
#include "backend/gtk/nvdialog_gtk.h"
#endif /* NVD_USE_GTK4 */

#if defined(NVD_GTK4_IMPL)
int nvd_init_gtk4(NvdBackendMask *mask) {
        if (!gtk_init_check(NULL, NULL)) return -NVD_NO_DISPLAY;

        nvd_error_message("You seem to be running libadwaita as the backend. If you're a developer, please use the gtk backend on Linux instead. Ignore this message otherwise.");
        nvd_error_message("** NOTE ** The gtk backend will be used by NvDialog to ensure stability.");

        mask->dialog_box = nvd_dialog_box_adw;
        mask->show_dialog = nvd_show_dialog_adw;
        mask->set_accept_text = NULL; /* Won't work on it I just want to make clear that it doesn't work until I get rid of this backend. */
        mask->question = nvd_question_adw;
        mask->get_reply = nvd_get_reply_adw;
        mask->about_dialog = nvd_about_dialog_adw;
        mask->show_about_dialog = nvd_show_about_dialog_adw;
        mask->about_dialog_set_version = NULL;
        mask->about_dialog_set_license = nvd_about_dialog_set_license_link_adw;
        mask->open_file_dialog = nvd_open_file_dialog_adw;
        mask->save_file_dialog = nvd_save_file_dialog_adw;
        mask->open_folder_dialog = NULL;
        mask->get_file_location = nvd_get_file_location_adw;
        mask->notification = nvd_notification_adw;
        mask->send_notification = nvd_send_notification_adw;
        mask->add_notification_action = nvd_add_notification_action_adw;

        return 0;
}
#endif

#if defined(NVD_GTK3_IMPL)
int nvd_init_gtk3(NvdBackendMask *mask) {
        if (!gtk_init_check(NULL, NULL)) {
                nvd_set_error(NVD_BACKEND_FAILURE);
                if (!getenv("DISPLAY")) return -NVD_NO_DISPLAY;
                return -NVD_BACKEND_FAILURE;
        }

        mask->dialog_box = nvd_dialog_box_gtk;
        mask->show_dialog = nvd_show_dialog_gtk;
        mask->set_accept_text = nvd_dialog_box_set_accept_text_gtk;
        mask->question = nvd_question_gtk;
        mask->get_reply = nvd_get_reply_gtk;
        mask->input_box = nvd_input_box_gtk;
        mask->show_input_box = nvd_show_input_box_gtk;
        mask->input_box_get_string = nvd_input_box_get_string_gtk;
        mask->about_dialog = nvd_about_dialog_gtk;
        mask->show_about_dialog = nvd_show_about_dialog_gtk;
        mask->about_dialog_set_version = nvd_about_dialog_set_version_gtk;
        mask->about_dialog_set_license = nvd_about_dialog_set_license_link_gtk;
        mask->open_file_dialog = nvd_open_file_dialog_gtk;
        mask->save_file_dialog = nvd_save_file_dialog_gtk;
        mask->open_folder_dialog = nvd_open_folder_dialog_gtk;
        mask->get_file_location = nvd_get_file_location_gtk;
        mask->notification = nvd_notification_gtk;
        mask->send_notification = nvd_send_notification_gtk;
        mask->add_notification_action = nvd_add_notification_action_gtk;

        return 0;
}
#endif

#if defined(NVD_WIN32_IMPL)
int nvd_init_win32(NvdBackendMask *mask) {
        mask->dialog_box = nvd_dialog_box_win32;
        mask->show_dialog = nvd_show_dialog_win32;
        mask->set_accept_text = nvd_dialog_box_set_accept_text_win32;
        mask->question = nvd_question_win32;
        mask->get_reply = nvd_get_reply_win32;
        mask->input_box = nvd_input_box_win32;
        mask->show_input_box = nvd_show_input_box_win32;
        mask->input_box_get_string = nvd_input_box_get_string_win32;
        mask->about_dialog = nvd_about_dialog_win32;
        mask->show_about_dialog = nvd_show_about_dialog_win32;
        mask->about_dialog_set_version = nvd_about_dialog_set_version_win32;
        mask->about_dialog_set_license = NULL;
        mask->open_file_dialog = nvd_open_file_dialog_win32;
        mask->save_file_dialog = nvd_save_file_dialog_win32;
        mask->open_folder_dialog = nvd_open_folder_dialog_win32;
        mask->get_file_location = nvd_get_file_location_win32;
        mask->notification = nvd_notification_win32;
        mask->send_notification = nvd_send_notification_win32;
        mask->add_notification_action = nvd_add_notification_action_win32;

        return 0;
}
#endif

#if defined(NVD_COCOA_IMPL)
int nvd_init_cocoa(NvdBackendMask *mask) {
        #ifdef _NVD_USE_GNUSTEP /* Only required on GNUstep */
        nvd_create_cocoa_app();
        #endif

        mask->dialog_box = nvd_dialog_box_cocoa;
        mask->show_dialog = nvd_show_dialog_cocoa;
        mask->set_accept_text = NULL;
        mask->question = nvd_question_cocoa;
        mask->get_reply = nvd_get_reply_cocoa;
        mask->input_box = nvd_input_box_cocoa;
        mask->show_input_box = nvd_show_input_box_cocoa;
        mask->input_box_get_string = nvd_input_box_get_string_cocoa;
        mask->about_dialog = nvd_about_dialog_cocoa;
        mask->show_about_dialog = nvd_show_about_dialog_cocoa;
        mask->about_dialog_set_version = NULL;
        mask->about_dialog_set_license = NULL;
        mask->open_file_dialog = nvd_open_file_dialog_cocoa;
        mask->save_file_dialog = nvd_save_file_dialog_cocoa;
        mask->open_folder_dialog = nvd_open_folder_dialog_cocoa;
        mask->get_file_location = nvd_get_file_location_cocoa;
        mask->notification = nvd_notification_cocoa;
        mask->send_notification = nvd_send_notification_cocoa;
        mask->add_notification_action = nvd_add_notification_action_cocoa;

        return 0;
}
#endif

#if defined(NVD_HAIKU_TARGET)
int nvd_init_hku(NvdBackendMask *mask) {
        mask->dialog_box = nvd_dialog_box_hku;
        mask->show_dialog = nvd_show_dialog_hku;
        mask->set_accept_text = nvd_dialog_box_set_accept_text_hku;
        mask->question = nvd_question_hku;
        mask->get_reply = nvd_get_reply_hku;
        mask->input_box = nvd_input_box_hku;
        mask->show_input_box = nvd_show_input_box_hku;
        mask->input_box_get_string = nvd_input_box_get_string_hku;
        mask->about_dialog = nvd_about_dialog_hku;
        mask->show_about_dialog = nvd_show_about_dialog_hku;
        mask->about_dialog_set_version = nvd_about_dialog_set_version_hku;
        mask->about_dialog_set_license = NULL;
        mask->open_file_dialog = nvd_open_file_dialog_hku;
        mask->save_file_dialog = nvd_save_file_dialog_hku;
        mask->open_folder_dialog = nvd_open_folder_dialog_hku;
        mask->get_file_location = nvd_get_file_location_hku;
        mask->notification = nvd_notification_hku;
        mask->send_notification = nvd_send_notification_hku;
        mask->add_notification_action = nvd_add_notification_action_hku;

        return 0;
}
#endif

int nvd_init_backends(NvdBackendMask *mask) {
#if defined(NVD_GTK4_IMPL)
        return nvd_init_gtk4(mask);
#elif defined(NVD_GTK3_IMPL)
        return nvd_init_gtk3(mask);
#elif defined(NVD_WIN32_IMPL)
        return nvd_init_win32(mask);
#elif defined(NVD_HAIKU_TARGET)
        return nvd_init_hku(mask);
#elif defined(NVD_COCOA_IMPL)
        return nvd_init_cocoa(mask);
#endif

        return -1;
}