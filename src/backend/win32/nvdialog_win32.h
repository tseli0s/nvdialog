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

#pragma once

#ifndef __nvdialog_win32_h__
#define __nvdialog_win32_h__ 1

#include <nvdialog.h>
#include "dialogs/nvdialog_about_dialog.h"
#include "dialogs/nvdialog_dialog_box.h"
#include "dialogs/nvdialog_file_dialog.h"
#include "nvdialog_notification.h"
#include "nvdialog_typeimpl.h"
#include <windows.h>

NvdDialogBox *nvd_dialog_box_win32(const char   *title,
                                   const char   *message,
                                   NvdDialogType type);

NvdFileDialog *nvd_open_file_dialog_win32(const char *title,
                                          const char *file_extensions);

NvdFileDialog *nvd_save_file_dialog_win32(const char *title,
                                          const char *default_filename);

NvdQuestionBox *nvd_question_win32(const char       *title,
                                   const char       *question,
                                   NvdQuestionButton buttons);

void nvd_show_dialog_win32(NvdDialogBox *dialog);

NvdReply nvd_get_reply_win32(NvdQuestionBox *box);

NvdAboutDialog *nvd_about_dialog_win32(const char *appname,
                                       const char *brief,
                                       const char *logo);

void nvd_show_about_dialog_win32(NvdAboutDialog *dialog);

void nvd_about_dialog_set_version_win32(NvdAboutDialog *dialog,
                                        const char     *version);

void nvd_get_file_location_win32(NvdFileDialog *dialog, const char** savebuf);

NvdNotification *nvd_notification_win32(const char   *title,
                                        const char   *msg,
                                        NvdNotifyType type);

void nvd_add_notification_action_win32(NvdNotification* notification,
                                     const char* action,
                                     int  value_to_set,
                                     int* value_to_return);

#endif /* __nvdialog_win32_h__ */