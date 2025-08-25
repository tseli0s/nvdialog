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

#include "dialogs/nvdialog_file_dialog.h"

#include <stdlib.h>

#include "../../nvdialog_assert.h"
#include "nvdialog_adw.h"
#include "../gtk/nvdialog_gtk.h"
#include "nvdialog_string.h"

NvdFileDialog *nvd_open_file_dialog_adw(const char *title,
                                        const char *file_extensions) {
        return nvd_open_file_dialog_gtk(title, file_extensions);
}

NvdFileDialog *nvd_save_file_dialog_adw(const char *title,
                                        const char *default_filename) {
        return nvd_save_file_dialog_gtk(title, default_filename);
}

inline void *nvd_open_file_dialog_get_raw_adw(NvdFileDialog *dlg) {
        NVD_ASSERT(dlg != NULL);
        return dlg->raw;
}

NvdDynamicString *nvd_get_file_location_adw(NvdFileDialog *dialog) {
        return dialog->filename;
}