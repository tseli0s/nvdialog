/*
 *  The MIT License (MIT)
 *
 *  Copyright (c) 2025 the NvDialog contributors
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

#ifndef __nvdialog_cocoa_h__
#define __nvdialog_cocoa_h__ 1

#include "nvdialog.h"
#include "nvdialog_typeimpl.h"

/* Shows a dialog box using Cocoa */
NvdDialogBox *nvd_dialog_box_cocoa(const char *title, const char *message,
                                   NvdDialogType type);

/* Open file dialog using Cocoa */
NvdFileDialog *nvd_open_file_dialog_cocoa(const char *title,
                                          const char *file_extensions);

/* Open file dialog using Cocoa */
NvdFileDialog *nvd_save_file_dialog_cocoa(const char *title,
                                          const char *default_filename);

NvdFileDialog *nvd_open_folder_dialog_cocoa(const char *title,
                                            const char *default_filename);

/* Creates a dialog box with the usual yes, no and cancel buttons. */
NvdQuestionBox *nvd_question_cocoa(const char *title, const char *question,
                                   NvdQuestionButton buttons);

NvdNotification *nvd_notification_cocoa(const char *title, const char *msg,
                                        NvdNotifyType type);

NvdAboutDialog *nvd_about_dialog_cocoa(const char *name, const char *desc,
                                       const char *imgpath);

void nvd_about_dialog_set_licence_link_cocoa(NvdAboutDialog *dialog,
                                             const char *license_link,
                                             const char *txt);

void nvd_show_dialog_cocoa(NvdDialogBox *dialog);
void nvd_show_about_dialog_cocoa(NvdAboutDialog *dialog);
void nvd_get_file_location_cocoa(NvdFileDialog *dlg, const char **out);
NvdReply nvd_get_reply_cocoa(NvdQuestionBox *box);
void nvd_send_notification_cocoa(NvdNotification *notification);

void *nvd_dialog_box_get_raw_cocoa(NvdDialogBox *dlg);
void *nvd_about_dialog_get_raw_cocoa(NvdAboutDialog *dlg);
void *nvd_dialog_question_get_raw_cocoa(NvdQuestionBox *dlg);
void *nvd_open_file_dialog_get_raw_cocoa(NvdFileDialog *dlg);
void nvd_add_notification_action_cocoa(NvdNotification *notification,
                                       const char *action, int value_to_set,
                                       int *value_to_return);

#endif /* __nvdialog_cocoa_h__ */
