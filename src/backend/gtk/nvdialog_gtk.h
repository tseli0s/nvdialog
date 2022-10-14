/*
 *  The MIT License (MIT)
 *
 *  Copyright (c) 2022 Aggelos Tselios
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

#include "dialogs/nvdialog_about_dialog.h"
#include "dialogs/nvdialog_dialog_box.h"
#include "dialogs/nvdialog_file_dialog.h"
#include <gtk/gtk.h>

/* Shows a simple dialog box using libadwaita. */
NvdDialogBox *nvd_dialog_box_gtk(const char *title, const char *message,
                                 NvdDialogType type);

/* Opens a file dialog using libadwaita. */
NvdFileDialog *nvd_open_file_dialog_gtk(const char *title,
                                        const char *file_extensions);

/* Creates a dialog box with the usual yes, no and cancel buttons. */
NvdQuestionBox *nvd_question_gtk(const char *title, const char *question,
                                 NvdQuestionButton buttons);

/* Shows the dialog box given to the system. */
void nvd_show_dialog_gtk(NvdDialogBox *dialog);

/* Shows the dialog box and returns the reply given. */
NvdReply nvd_get_reply_gtk(NvdQuestionBox *box);

/*
 * About dialog box using libadwaita.
 * TODO: Add functions within NvDialog to allow adding additional
 * elements to the dialog box.
 */
NvdAboutDialog *nvd_about_dialog_gtk(const char *appname, const char *brief,
                                     const char *logo);

/*
 * Shows the dialog given to the system.
 */
void nvd_show_about_dialog_gtk(NvdAboutDialog *dialog);

/*
 * Sets the version of the application in the About dialog box
 * passed as the parameter.
 */
void nvd_about_dialog_set_version_gtk(NvdAboutDialog *dialog, const char *version);
#endif /* __nvdialog_adw_h__ */