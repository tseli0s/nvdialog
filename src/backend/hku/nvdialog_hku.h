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

#pragma once

#ifndef __nvdialog_hku_h__
#define __nvdialog_hku_h__ 1

#ifdef __cplusplus
#define NVD_C_LINKAGE extern "C"
#else
#define NVD_C_LINKAGE 
#endif

/* NOTE: Don't include C++ headers here (From Haiku's API for example).
 * Keep C++ specific code in C++ translation units (.cc files)*/

#include "nvdialog.h"
#include "nvdialog_typeimpl.h"
#include "dialogs/nvdialog_dialog_box.h"
#include "dialogs/nvdialog_input_box.h"
#include "dialogs/nvdialog_file_dialog.h"
#include "dialogs/nvdialog_about_dialog.h"

#ifdef __cplusplus
extern "C" {
#endif

NvdDialogBox *nvd_dialog_box_hku(const char *title, const char *message,
                                   NvdDialogType type);

NvdInputBox *nvd_input_box_hku(const char *title, const char *message);

void nvd_show_input_box_hku(NvdInputBox *box);

NvdDynamicString *nvd_input_box_get_string_hku(NvdInputBox *box);

NvdFileDialog *nvd_open_file_dialog_hku(const char *title,
                                          const char *file_extensions);

NvdFileDialog *nvd_save_file_dialog_hku(const char *title,
                                          const char *default_filename);

NvdFileDialog *nvd_open_file_dialog_hku(const char *title,
                                          const char *default_path);
NvdFileDialog *nvd_open_folder_dialog_hku(const char *title,
                                            const char *default_path);

NvdQuestionBox *nvd_question_hku(const char *title, const char *question,
                                   NvdQuestionButton buttons);

void nvd_show_dialog_hku(NvdDialogBox *dialog);

void nvd_dialog_box_set_accept_text_hku(NvdDialogBox *dialog, const char *accept_text);

NvdReply nvd_get_reply_hku(NvdQuestionBox *box);

NvdAboutDialog *nvd_about_dialog_hku(const char *appname, const char *brief,
                                       const char *logo);

void nvd_show_about_dialog_hku(NvdAboutDialog *dialog);

void nvd_about_dialog_set_version_hku(NvdAboutDialog *dialog,
                                        const char *version);

NvdDynamicString *nvd_get_file_location_hku(NvdFileDialog *dialog);

NvdNotification *nvd_notification_hku(const char *title, const char *msg,
                                        NvdNotifyType type);

void nvd_send_notification_hku(NvdNotification *notification);

void nvd_add_notification_action_hku(NvdNotification *notification,
                                       const char *action, int value_to_set,
                                       int *value_to_return);

#ifdef __cplusplus
}
#endif

#endif /* __nvdialog_hku_h__ */
