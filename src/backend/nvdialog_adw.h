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
#define __nvdialog_adw_h__ 1

#ifdef NVD_USE_GTK4

#include "nvdialog.h"
#include <adwaita.h>

/*
 * Opens a "Open File" dialog using Gtk4 and libadwaita.
 * This function is mostly experimental like the entire backend.
 */
const char *nvd_open_file_dialog_adw(const char *title,
                                     const char *file_extensions);

/*
 * Creates a message dialog using Gtk4 and libadwaita.
 * This function uses a much more newer look, so it may not be very
 * consistent across different library builds.
 */
NvdDialogBox *nvd_create_adw_dialog(const char *title, const char *message,
                                    const NvdDialogType type);

#endif /* NVD_USE_GTK4 */
#endif /* __nvdialog_gtk_h__ */