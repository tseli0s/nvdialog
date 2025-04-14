#include "nvdialog_init.h"
#include <string.h>
#if defined (NVD_USE_GTK4)
#define NVD_GTK4_IMPL
#include "backend/adw/nvdialog_adw.h"
#elif defined (_WIN32)
#define NVD_WIN32_IMPL 1
#include "backend/win32/nvdialog_win32.h"
#elif defined(NVD_USE_COCOA)
#define NVD_COCOA_IMPL
#include "backend/cocoa/nvdialog_cocoa.h"
#else
#define NVD_GTK3_IMPL
#include "backend/gtk/nvdialog_gtk.h"
#endif /* NVD_USE_GTK4 */

#if defined(NVD_GTK4_IMPL)
int nvd_init_gtk4(NvdBackendMask *mask) {
    if (!gtk_init_check()) return -NVD_NO_DISPLAY;
    adw_init();

    mask->dialog_box = nvd_dialog_box_adw;
    mask->show_dialog = nvd_show_dialog_adw;
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
        if (!getenv("DISPLAY"))
            return -NVD_NO_DISPLAY;
        return -NVD_BACKEND_FAILURE;
    }

    mask->dialog_box = nvd_dialog_box_gtk;
    mask->show_dialog = nvd_show_dialog_gtk;
    mask->question = nvd_question_gtk;
    mask->get_reply = nvd_get_reply_gtk;
    mask->about_dialog = nvd_about_dialog_gtk;
    mask->show_about_dialog = nvd_show_about_dialog_gtk;
    mask->about_dialog_set_version = nvd_about_dialog_set_version_gtk;
    mask->about_dialog_set_license = nvd_about_dialog_set_license_link_gtk;
    mask->open_file_dialog = nvd_open_file_dialog_gtk;
    mask->save_file_dialog = nvd_save_file_dialog_gtk;
    mask->open_folder_dialog = nvd_open_folder_dialog_gtk;
    mask->get_file_location = (void (*)(NvdFileDialog*, char**)) nvd_get_file_location_gtk; // Cast necessary because I am an idiot
    mask->notification = nvd_notification_gtk;
    mask->send_notification = nvd_send_notification_gtk;
    mask->add_notification_action = nvd_add_notification_action_gtk;
}
#endif

#if defined(NVD_WIN32_IMPL)
int nvd_init_win32(NvdBackendMask *mask) {
    mask->dialog_box = nvd_dialog_box_win32;
    mask->show_dialog = nvd_show_dialog_win32;
    mask->question = nvd_question_win32;
    mask->get_reply = nvd_get_reply_win32;
    mask->about_dialog = nvd_about_dialog_win32;
    mask->show_about_dialog = nvd_show_about_dialog_win32;
    mask->about_dialog_set_version = nvd_about_dialog_set_version_win32;
    mask->about_dialog_set_license = NULL;
    mask->open_file_dialog = nvd_open_file_dialog_win32;
    mask->save_file_dialog = nvd_save_file_dialog_win32;
    mask->open_folder_dialog = NULL;
    mask->get_file_location = (void (*)(NvdFileDialog*, char**)) nvd_get_file_location_win32;
    mask->notification = nvd_notification_win32;
    mask->send_notification = nvd_send_notification_win32;
    mask->add_notification_action = nvd_add_notification_action_win32;

    return 0;
}
#endif

#if defined(NVD_COCOA_IMPL)
int nvd_init_cocoa(NvdBackendMask *mask) {
    mask->dialog_box = nvd_dialog_box_cocoa;
    mask->show_dialog = nvd_show_dialog_cocoa;
    mask->question = nvd_question_cocoa;
    mask->get_reply = nvd_get_reply_cocoa;
    mask->about_dialog = nvd_about_dialog_cocoa;
    mask->show_about_dialog = nvd_show_about_dialog_cocoa;
    mask->about_dialog_set_version = NULL;
    mask->about_dialog_set_license = NULL;
    mask->open_file_dialog = nvd_open_file_dialog_cocoa;
    mask->save_file_dialog = nvd_save_file_dialog_cocoa;
    mask->open_folder_dialog = nvd_open_folder_dialog_cocoa;
    mask->get_file_location = (void (*)(NvdFileDialog*, char**)) nvd_get_file_location_cocoa;
    mask->notification = nvd_notification_cocoa;
    mask->send_notification = nvd_send_notification_cocoa;
    mask->add_notification_action = nvd_add_notification_action_cocoa;

    return 0;
}
#endif

int nvd_init_backends(NvdBackendMask *mask) {
    #if defined(NVD_GTK4_IMPL)
    return nvd_init_gtk4(mask);
    #elif defined (NVD_GTK3_IMPL)
    return nvd_init_gtk3(mask);
    #elif defined(NVD_WIN32_IMPL)
    return nvd_init_win32(mask);
    #elif defined(NVD_COCOA_IMPL)
    return nvd_init_cocoa(mask);
    #endif

    return -1;
}