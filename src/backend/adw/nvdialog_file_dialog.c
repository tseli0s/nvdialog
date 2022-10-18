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

#include "dialogs/nvdialog_file_dialog.h"
#include "../../nvdialog_assert.h"
#include "nvdialog_adw.h"
#include <stdlib.h>

struct _NvdFileDialog {
        char *filename, *file_extensions;
        bool  location_was_chosen;
        void *raw;
};

NvdFileDialog *nvd_open_file_dialog_adw(const char *title,
                                        const char *file_extensions) {
        NvdFileDialog *dialog = malloc(sizeof(struct _NvdFileDialog));
        NVD_RETURN_IF_NULL(dialog);
        dialog->file_extensions = (char *)file_extensions;

        GtkWidget *dialog_raw
            = gtk_file_chooser_dialog_new(title,
                                          NULL,
                                          GTK_FILE_CHOOSER_ACTION_OPEN,
                                          "Cancel",
                                          GTK_RESPONSE_CANCEL,
                                          "Open",
                                          GTK_RESPONSE_OK,
                                          NULL);

        dialog->raw = dialog_raw;

        return dialog;
}

void nvd_get_file_location_adw(NvdFileDialog *dialog, char **savebuf) {
        if (gtk_dialog_run(GTK_DIALOG(dialog->raw)) == GTK_RESPONSE_OK) {
                *savebuf = gtk_file_chooser_get_filename(
                    GTK_FILE_CHOOSER(dialog->raw));
                dialog->filename = (char *)*savebuf;
                dialog->location_was_chosen = true;
                return;
        } else {
                dialog->location_was_chosen = false;
                return;
        }
}