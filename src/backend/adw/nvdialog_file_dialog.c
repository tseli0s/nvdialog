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

#include "dialogs/nvdialog_file_dialog.h"
#include "../../nvdialog_assert.h"
#include "nvdialog_adw.h"
#include <stdlib.h>

static void nvd_file_dialog_response_adw(GtkDialog     *dialog,
                                         int32_t        response,
                                         NvdFileDialog* data) {
        if (response == GTK_RESPONSE_ACCEPT ||
            response == GTK_RESPONSE_APPLY  ||
            response == GTK_RESPONSE_YES    ) {

                GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
                g_autoptr(GFile) file   = gtk_file_chooser_get_file (chooser);
                data->filename          = g_file_get_path(file);
        }
        gtk_window_destroy (GTK_WINDOW (dialog));
}

NvdFileDialog *nvd_open_file_dialog_adw(const char *title,
                                        const char *file_extensions) {
        NvdFileDialog *dialog = malloc(sizeof(struct _NvdFileDialog));
        NVD_RETURN_IF_NULL(dialog);
        dialog->file_extensions = (char *)file_extensions;

        /* I know it's not the Gtk4 official one but this one is the only one working for me. */
        GtkFileChooserNative *dialog_raw = gtk_file_chooser_native_new(title,
                                                                nvd_get_parent(),
                                                                GTK_FILE_CHOOSER_ACTION_OPEN,
                                                          "Open",
                                                          "Cancel");

        dialog->raw = dialog_raw;
        gtk_native_dialog_show(GTK_NATIVE_DIALOG(dialog->raw));
        
        return dialog;
}

NvdFileDialog *nvd_save_file_dialog_adw(const char *title,
                                        const char *default_filename) {
        NvdFileDialog *dialog = calloc(1, sizeof(struct _NvdFileDialog));
        NVD_RETURN_IF_NULL(dialog);

        dialog->raw = gtk_file_chooser_dialog_new(title,
                                                  nvd_get_parent(),
                                                  GTK_FILE_CHOOSER_ACTION_SAVE,
                                                  "Cancel",
                                                  GTK_RESPONSE_CANCEL,
                                                  "Save",
                                                  GTK_RESPONSE_ACCEPT,
                                                  NULL);
        if (!dialog->raw) {
                nvd_set_error(NVD_BACKEND_INVALID);
                free(dialog);
        } else gtk_file_chooser_set_current_name(dialog->raw, default_filename);

        return dialog;
}

inline void *nvd_open_file_dialog_get_raw_adw(NvdFileDialog *dlg) {
        NVD_ASSERT(dlg != NULL);
        return dlg->raw;
}

void nvd_get_file_location_adw(NvdFileDialog *dialog, char **savebuf) {
        g_signal_connect (dialog->raw,
                          "response",
                          G_CALLBACK (nvd_file_dialog_response_adw),
                          dialog);
        while (g_list_model_get_n_items(gtk_window_get_toplevels()) > 0)
                g_main_context_iteration(NULL, false);

        *savebuf = (char*) dialog->filename;
}