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

#ifndef __nvdialog_adw_h__
#define __nvdialog_adw_h__

#define GDK_DISABLE_DEPRECATED
#define GTK_DISABLE_DEPRECATED

#include "nvdialog.h"
#include "nvdialog_typeimpl.h"
#include "dialogs/nvdialog_about_dialog.h"
#include "dialogs/nvdialog_dialog_box.h"
#include "dialogs/nvdialog_file_dialog.h"
#include "nvdialog_notification.h"
#include <adwaita.h>

/* Shows a simple dialog box using libadwaita. */
NvdDialogBox *nvd_dialog_box_adw(const char *title,
                                 const char *message,
                                 NvdDialogType type);

/* Opens a file dialog using libadwaita. */
NvdFileDialog *nvd_open_file_dialog_adw(const char *title,
                                        const char *file_extensions);

/* Save file dialog. */
NvdFileDialog *nvd_save_file_dialog_adw(const char *title,
                                        const char *default_filename);

/* 
 * Returns the filename chosen from the file dialog given to
 * the parameter 'savebuf'. This function is also used to show the
 * actual dialog.
 */
void nvd_get_file_location_adw(NvdFileDialog *dialog, char **savebuf);

/* Creates a dialog box with the usual yes, no and cancel buttons. */
NvdQuestionBox *nvd_question_adw(const char       *title,
                                 const char       *question,
                                 NvdQuestionButton buttons);

/* Shows the dialog box given to the system. */
void nvd_show_dialog_adw(NvdDialogBox *dialog);

/* Shows the dialog box and returns the reply given. */
NvdReply nvd_get_reply_adw(NvdQuestionBox *box);

/*
 * About dialog box using libadwaita.
 */
NvdAboutDialog *
nvd_about_dialog_adw(const char *appname, const char *brief, const char *logo);

/*
 * Shows the dialog given to the system.
 */
void nvd_show_about_dialog_adw(NvdAboutDialog *dialog);

/* Sets the license link for the dialog. */
void nvd_about_dialog_set_license_link_adw(NvdAboutDialog *dialog,
                                           const char *license_link,
                                           const char *txt);
/*
 * Sets the version of the application in the About dialog box
 * passed as the parameter.
 */
void nvd_about_dialog_set_version_adw(NvdAboutDialog *dialog, const char *version);

/*
 * A notification object using the Adwaita backend.
*/
NvdNotification *nvd_notification_adw(const char   *title,
                                        const char   *msg,
                                        NvdNotifyType type);
                                
/*
 * Sends the notification to the system.
*/
void nvd_send_notification_adw(NvdNotification *notification);

/* Pretty self-explanatory; See the headers otherwise. */
void *nvd_about_dialog_get_raw_adw    (NvdAboutDialog *dialog);
void *nvd_dialog_box_get_raw_adw      (NvdDialogBox   *dialog);
void *nvd_dialog_question_get_raw_adw (NvdQuestionBox *dialog);
void *nvd_open_file_dialog_get_raw_adw(NvdFileDialog  *dialog);

/*
 * Sets the specified action for the notification.
 * (Adwaita implementation)
*/
void nvd_add_notification_action_adw(NvdNotification* notification,
                                     const char* action,
                                     int  value_to_set,
                                     int* value_to_return);

#endif /* __nvdialog_adw_h__ */