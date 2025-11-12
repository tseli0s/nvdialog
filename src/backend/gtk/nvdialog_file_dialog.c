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
#include <string.h>

#include "../../nvdialog_assert.h"
#include "gtk/gtk.h"
#include "nvdialog_gtk.h"
#include "nvdialog_string.h"

/* TODO: Perhaps in the future we will use DBus directly to request files just like Firefox. For now, GtkNativeDialog works.*/

NvdFileDialog *nvd_open_file_dialog_gtk(const char *title,
                                        const char *file_extensions) {
        NvdFileDialog *dialog = nvd_malloc(sizeof(struct _NvdFileDialog));
        NVD_RETURN_IF_NULL(dialog);
        dialog->file_extensions = (char *)file_extensions;

        dialog->raw = gtk_file_chooser_native_new(title, nvd_get_parent(),
                                                  GTK_FILE_CHOOSER_ACTION_OPEN,
                                                  "_Open", "_Cancel");
        if (!dialog->raw) {
                free(dialog);
                return NULL;
        }

        
        if (file_extensions) {
                /* Note: This array is null-terminated, so we keep parsing until we hit NULL. */
                char **filters = nvd_seperate_args(file_extensions);
                for (int i = 0; filters[i] != NULL; i++) {
                        GtkFileFilter *current_filter = gtk_file_filter_new();
                        size_t filter_size = strlen(filters[i]);

                        /* We have to add the wildcard manually here, otherwise gtk will think we're looking for the exact filename. */
                        char *filter = nvd_malloc(filter_size + 2); /* Plus the '*' and the null terminator*/
                        memcpy(filter + 1, filters[i], filter_size + 1); /* Including the null terminator */
                        filter[0] = '*';
                        filter[filter_size + 1] = '\0';

                        gtk_file_filter_add_pattern(current_filter, filter);
                        gtk_file_filter_set_name(current_filter, filter); /* Couldn't come up with something better lol */
                        gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog->raw), current_filter);        
                }

                GtkFileFilter *default_filter = gtk_file_filter_new();
                gtk_file_filter_set_name(default_filter, "All files");
                gtk_file_filter_add_pattern(default_filter, "*");
                gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog->raw), default_filter);
        }
        

        return dialog;
}

NvdFileDialog *nvd_save_file_dialog_gtk(const char *title,
                                        const char *default_filename) {
        NvdFileDialog *dialog = nvd_malloc(sizeof(struct _NvdFileDialog));
        NVD_RETURN_IF_NULL(dialog);
        dialog->raw = gtk_file_chooser_native_new(title, nvd_get_parent(),
                                                  GTK_FILE_CHOOSER_ACTION_SAVE,
                                                  "_Save", "_Cancel");
        if (!dialog->raw) {
                free(dialog);
                return NULL;
        }

        if (default_filename)
                gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(dialog->raw), default_filename);

        return dialog;
}

NvdFileDialog *nvd_open_folder_dialog_gtk(const char *title,
                                          const char *default_filename) {
        NvdFileDialog *dialog = nvd_malloc(sizeof(struct _NvdFileDialog));
        NVD_RETURN_IF_NULL(dialog);
        dialog->raw = gtk_file_chooser_native_new(title, nvd_get_parent(),
                                                  GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER,
                                                  "_Open Folder", "_Cancel");
        if (!dialog->raw) {
                free(dialog);
                return NULL;
        }

        /*
         * We can't set a default filename when we use GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER.
         * To make the compiler shut up, just do this instead. */
        (void) default_filename;

        return dialog;
}

void *nvd_open_file_dialog_get_raw_gtk(NvdFileDialog *dlg) {
        NVD_ASSERT(dlg != NULL);
        return dlg->raw;
}
NvdDynamicString *nvd_get_file_location_gtk(NvdFileDialog *dialog) {
        NVD_ASSERT_FATAL(dialog->raw != NULL);

        GtkResponseType response = gtk_native_dialog_run(GTK_NATIVE_DIALOG(dialog->raw));
        char *filename = NULL;

        if (response == GTK_RESPONSE_OK || response == GTK_RESPONSE_ACCEPT) {
                filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog->raw));
                dialog->location_was_chosen = true;
                if (filename) {
                        dialog->filename = nvd_string_new(filename);
                        g_free(filename);
                }
        } else {
                dialog->location_was_chosen = false;
                nvd_delete_string(dialog->filename);
                dialog->filename = NULL;
        }

        gtk_native_dialog_destroy(GTK_NATIVE_DIALOG(dialog->raw));
        dialog->raw = NULL;

        while (gtk_events_pending()) gtk_main_iteration();
        return dialog->filename;
}

