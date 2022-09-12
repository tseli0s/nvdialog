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

#ifndef __nvdialog_gtk_h__
#define __nvdialog_gtk_h__

#include "nvdialog.h"
#include <gtk/gtk.h>

/*
 * Creates a window that asks for a file using Gtk3.
 * This function is incomplete and will not be used.
 */
const char *nvd_open_file_dialog_gtk(const char *title,
                                     const char *file_extensions);

/*
 * Creates a simple dialog window using Gtk3.
 * TODO: Add an Ok button to the dialog window.
 */
void *nvd_create_gtk_dialog(const char *title, const char *message,
                            NvdDialogType type);

/*
 * Creates a question dialog window using Gtk3.
 * NOTE: This function is experimental.
 */
NvdReply nvd_question_gtk(const char *title, const char *question,
                          NvdQuestionButton button);
#endif /* __nvdialog_gtk_h__ */
