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

#ifndef __nvdialog_sbx_h__
#define __nvdialog_sbx_h__

#include "nvdialog.h"
#include <gtk/gtk.h>
#include "nvdialog_typeimpl.h"

/* Shows a simple dialog box using Gtk3 (Sandbox version). */
NvdDialogBox *
nvd_dialog_box_sbx(const char *title, const char *message, NvdDialogType type);

/* Opens a file dialog using Gtk3 (Sandbox version).*/
NvdFileDialog *nvd_open_file_dialog_sbx(const char *title,
                                        const char *file_extensions);

NvdFileDialog *nvd_save_file_dialog_sbx(const char *title,
                                        const char *default_filename);

/* Creates a dialog box with the usual yes, no and cancel buttons. (Sandbox version) */
NvdQuestionBox *nvd_question_sbx(const char       *title,
                                 const char       *question,
                                 NvdQuestionButton buttons);

/* Shows the dialog box and returns the reply given. (Sandbox version) */
NvdReply nvd_get_reply_sbx(NvdQuestionBox *box);

/*
 * About dialog box using Gtk3. (Sandbox version)
 */
NvdAboutDialog *
nvd_about_dialog_sbx(const char *appname, const char *brief, const char *logo);

/*
 * Shows the dialog given to the system.
 * (Sandbox version)
 */
void nvd_show_about_dialog_sbx(NvdAboutDialog *dialog);

/*
 * Sets the version of the application in the About dialog box
 * passed as the parameter.
 */
void nvd_about_dialog_set_version_sbx(NvdAboutDialog *dialog,
                                      const char     *version);

/*
 * Sets a license hyperlink for the dialog given to the system,
 * using Gtk3's API.
*/
void nvd_about_dialog_set_license_link_sbx(NvdAboutDialog *dialog,
                                           const char     *license_link, 
                                           const char     *txt);

/*
 * Gets the full path of a file, and returns the path
 * inside the 'save' nested pointer passed.
 */
void nvd_get_file_location_sbx(NvdFileDialog *dialog, const char **savebuf);

/*
 * Notification using Gtk3 backend.
 * Just a copy of the Adwaita implementation.
 * (Sandbox version)
*/
NvdNotification *nvd_notification_sbx(const char   *title,
                                      const char   *msg,
                                      NvdNotifyType type);

/* Sends the notification to the system. (Sandbox version) */
void nvd_send_notification_sbx(NvdNotification *notification);

/* Pretty self-explanatory; See the headers otherwise. */
void *nvd_about_dialog_get_raw_sbx    (NvdAboutDialog *dialog);
void *nvd_dialog_box_get_raw_sbx      (NvdDialogBox   *dialog);
void *nvd_dialog_question_get_raw_sbx (NvdQuestionBox *dialog);
void *nvd_open_file_dialog_get_raw_sbx(NvdFileDialog  *dialog);

/*
 * Sets the action specified to the notification given.
 * (Gtk3 implementation / backend)
*/
void nvd_add_notification_action_sbx(NvdNotification* notification,
                                     const char* action,
                                     int  value_to_set,
                                     int* value_to_return);

#endif /* __nvdialog_sbx_h__ */