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

#pragma once
#ifndef __nvdialog_dialog_h__
#define __nvdialog_dialog_h__ 1

#include "nvdialog_types.h"

/**
 * @brief Creates a question dialog box with the given parameters.
 * This function creates a dialog box containing a question with a few
 * buttons such as:
 * - Yes / No
 * - Yes / No / Cancel
 * - Yes / Cancel
 * @return The NvdReply on success, else -1 -- Check @ref nvd_get_error() for more.
 * @since  v0.1.1
 */
int nvd_dialog_question_new(const char* title,
                                 const char *question,
                                 NvdQuestionButton button);

/**
 * @brief Shows a dialog to the system shell.
 * @param dialog The dialog to show.
 */
void nvd_show_dialog(NvdDialogBox *dialog);

/**
 * @brief Creates an open file dialog.
 * This function creates a dialog to open a file in the filesystem
 * through a GUI.
 * @param title The window title to display.
 * @param file_extensions If looking for specific file extension, put it here.
 * Else pass NULL.
 * @note INCOMPLETE FUNCTION - Do not use please.
 * @returns The filename path on success, otherwise NULL.
 */
const char *nvd_open_file_dialog_new(const char *title,
                                     const char *file_extensions);

/**
 * @brief Creates a new dialog object and returns it.
 * This function creates a simple dialog with the specified arguments,
 * and returns an opaque handle to it for use with @ref nvd_show_dialog().
 * @return The dialog handle on success, else NULL.
 */
NvdDialogBox *nvd_dialog_box_new(const char *title, const char *message,
                                 NvdDialogType type);


/**
 * @brief Shows a dialog to the system shell.
 * @param dialog The dialog to show.
 * @note Obsolete function, currently unnecessary.
 */
void nvd_show_dialog(NvdDialogBox *dialog);

#endif  /* __nvdialog_dialog_h__ */