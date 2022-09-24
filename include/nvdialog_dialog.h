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

#ifdef __nvdialog_dialog_h__
#error[ NVDIALOG ] Header file included twice, only include <nvdialog/nvdialog.h>
#endif /* __nvdialog_dialog_h__ */

#ifndef __nvdialog_dialog_h__
#define __nvdialog_dialog_h__ 1

#ifndef __nvdialog_h__
#error[ NVDIALOG ] Please only include <nvdialog.h> and no other headers.
#endif /* __nvdialog_h__ */

#include "nvdialog_types.h"

/**
 * @brief Creates a question dialog box with the given parameters.
 * This function creates a dialog box containing a question with a few
 * buttons such as:
 * - Yes / No
 * - Yes / No / Cancel
 * - Yes / Cancel
 * @return The NvdReply on success, else -1 -- Check @ref nvd_get_error() for
 * more.
 * @since  v0.1.1
 */
NvdReply nvd_dialog_question_new(const char *title, const char *question,
                                 NvdQuestionButton button);

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

/**
 * @brief Shows an 'About application' dialog box.
 * @details This function displays a dialog box similar to 'About' menus in
 * other applications. It will display the application name, a brief description
 * of the application, the logo (If specified)
 * @param name Your application name.
 * @param description A short description of the application, describing what it
 * does.
 * @param license_text A short license text. Eg. for MIT licensed software, you
 * could use something like: [App name] is licensed under the MIT license. See
 * [license link] for details.
 * @param logo Nullable value that can specify a filename to load as the
 * application logo.
 * @note This function does not use GtkAboutDialog on Unix.
 * @return NULL on failure.
 */
NvdDialogBox *nvd_about_dialog_new(const char *name, const char *description,
                                   const char *license_text, const char *logo);

#endif /* __nvdialog_dialog_h__ */
