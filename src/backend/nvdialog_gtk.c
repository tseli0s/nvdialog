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

#include "nvdialog_gtk.h"
#include "nvdialog.h"
#include <stdbool.h>
#include <stdio.h>

/*
 * FIXME: This function segfaults apparently. I can't find why.
 * Perhaps it's a bug in Gtk3?
 */
const char *nvd_open_file_dialog_gtk(const char *title,
                                     const char *file_extensions) {
        GtkFileChooserNative *native;
        GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
        gint res;

        native = gtk_file_chooser_native_new("Open File", NULL, action, "_Open",
                                             "_Cancel");

        res = gtk_native_dialog_run(GTK_NATIVE_DIALOG(native));
        if (res == GTK_RESPONSE_ACCEPT) {
                char *filename;
                GtkFileChooser *chooser = GTK_FILE_CHOOSER(native);
                filename = gtk_file_chooser_get_filename(chooser);
                printf("filename");
                // g_free (filename);
        }

        g_object_unref(native);
        native = NULL;
}

void *nvd_create_gtk_dialog(const char *title, const char *message,
                            NvdDialogType type) {
        GtkWidget *dialog, *label, *content_area, *ok_button, *image;
        GtkDialogFlags flags = GTK_DIALOG_USE_HEADER_BAR;

        char *icon = NULL;
        switch (type) {
        case NVD_DIALOG_ERROR:
                icon = "dialog-error";
                break;
        case NVD_DIALOG_SIMPLE:
                icon = "dialog-information";
                break;
        case NVD_DIALOG_WARNING:
                icon = "dialog-warning";
                break;
        default:
                return NULL;
        }

        image = gtk_image_new_from_icon_name(icon, GTK_ICON_SIZE_DIALOG);
        dialog = gtk_dialog_new_with_buttons(title, NULL, flags, NULL,
                                             GTK_RESPONSE_NONE, NULL);
        content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
        label = gtk_label_new(message);
        ok_button = gtk_button_new_with_label("Ok");

        gtk_widget_set_margin_bottom(ok_button, 6);
        gtk_widget_set_margin_start(ok_button, 6);
        gtk_widget_set_margin_end(ok_button, 6);
        gtk_widget_set_margin_top(ok_button, 6);

        gtk_widget_set_margin_bottom(image, 12);
        gtk_widget_set_margin_start(image, 12);
        gtk_widget_set_margin_end(image, 12);
        gtk_widget_set_margin_top(image, 12);

        g_signal_connect_swapped(dialog, "response",
                                 G_CALLBACK(gtk_widget_destroy), dialog);
        g_signal_connect_swapped(ok_button, "clicked",
                                 G_CALLBACK(gtk_main_quit), NULL);
        GtkWidget *grid = gtk_grid_new();
        gtk_grid_set_row_spacing(GTK_GRID(grid), 12);
        gtk_container_add(GTK_CONTAINER(content_area), grid);

        gtk_grid_attach(GTK_GRID(grid), image, 0, 0, 1, 1);
        gtk_grid_attach(GTK_GRID(grid), label, 1, 0, 1, 1);
        gtk_grid_attach(GTK_GRID(grid), ok_button, 2, 1, 1, 1);

        gtk_widget_show_all(dialog);
        gtk_main();

        return dialog;
}