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

#ifndef __nvdialog_sandbox_h__
#define __nvdialog_sandbox_h__ 1

#include "nvdialog.h"
#include "dialogs/nvdialog_file_dialog.h"

#if !defined (__linux__) && defined (__linux) && defined (__gnu_linux__)
#error Sandboxed environments are not supported on this platform.
#endif /* !__linux__ */

/* Creates a file dialog in a sandboxed environment. */
NvdFileDialog *nvd_open_file_dialog_sndbx(const char *title, const char *file_extensions);

/* Creates a file dialog used for saving inside a sandboxed environment. */
NvdFileDialog *nvd_save_file_dialog_sndbx(const char *title, const char *default_filename);

/* Returns to the address pointed by 'savebuf' the filename chosen by the dialog. */
void nvd_get_file_location_sndbx(NvdFileDialog *dialog, const char **savebuf);
#endif /* __nvdialog_sandbox_h__ */