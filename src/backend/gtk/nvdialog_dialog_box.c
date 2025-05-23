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

#include "dialogs/nvdialog_dialog_box.h"

#include "../../nvdialog_assert.h"
#include "nvdialog_gtk.h"

static inline void nvd_set_margins_gtk3(GtkWidget *widget) {
        gtk_widget_set_margin_start(widget, 16);
        gtk_widget_set_margin_end(widget, 16);
        gtk_widget_set_margin_top(widget, 16);
        gtk_widget_set_margin_bottom(widget, 16);
}

static inline void nvd_destroy_and_quit(GtkWidget *widget) {
        gtk_widget_destroy(GTK_WIDGET(widget));
        gtk_main_quit();
}

NvdDialogBox *nvd_dialog_box_gtk(const char *title, const char *message,
                                 NvdDialogType type) {
        NvdDialogBox *dialog = malloc(sizeof(struct _NvdDialogBox));
        NVD_RETURN_IF_NULL(dialog);

        dialog->accept_label = "Okay";
        dialog->content = (char *)message;
        dialog->msg = (char *)title;
        dialog->type = type;
        dialog->window_handle = gtk_window_new(GTK_WINDOW_TOPLEVEL);

        gtk_widget_set_hexpand(dialog->window_handle, true);
        gtk_widget_set_vexpand(dialog->window_handle, true);
        gtk_window_set_title(GTK_WINDOW(dialog->window_handle), title);
        gtk_window_set_resizable(GTK_WINDOW(dialog->window_handle), false);
        gtk_window_set_decorated(GTK_WINDOW(dialog->window_handle), true);
        gtk_window_set_modal(GTK_WINDOW(dialog->window_handle), true);

        GtkWidget *img;
        switch (type) {
                case NVD_DIALOG_WARNING:
                        img = gtk_image_new_from_icon_name(
                                "dialog-warning", GTK_ICON_SIZE_DIALOG);
                        break;
                case NVD_DIALOG_ERROR:
                        img = gtk_image_new_from_icon_name(
                                "dialog-error", GTK_ICON_SIZE_DIALOG);
                        break;

                default:
                case NVD_DIALOG_SIMPLE:
                        img = gtk_image_new_from_icon_name(
                                "dialog-information", GTK_ICON_SIZE_DIALOG);
                        break;
        }

        GtkGrid *grid = GTK_GRID(gtk_grid_new());
        gtk_grid_set_column_spacing(grid, 16);

        GtkWidget *text = gtk_label_new(dialog->content);
        GtkWidget *button = gtk_button_new_with_label(dialog->accept_label);

        nvd_set_margins_gtk3(text);
        nvd_set_margins_gtk3(button);
        nvd_set_margins_gtk3(img);

        gtk_grid_attach(grid, img, 0, 0, 1, 1);
        gtk_grid_attach(grid, text, 1, 0, 1, 1);
        gtk_grid_attach(grid, button, 0, 1, 1, 1);

        gtk_widget_set_hexpand(GTK_WIDGET(grid), true);
        gtk_widget_set_vexpand(GTK_WIDGET(grid), true);

        gtk_container_add(GTK_CONTAINER(dialog->window_handle),
                          GTK_WIDGET(grid));

        g_signal_connect_swapped(dialog->window_handle, "destroy",
                                 G_CALLBACK(nvd_destroy_and_quit),
                                 dialog->window_handle);
        g_signal_connect_swapped(button, "clicked",
                                 G_CALLBACK(nvd_destroy_and_quit),
                                 dialog->window_handle);

        dialog->accept_button = button;
        return dialog;
}

inline void *nvd_dialog_box_get_raw_gtk(NvdDialogBox *dlg) {
        NVD_ASSERT(dlg != NULL);
        return dlg->window_handle;
}

void nvd_show_dialog_gtk(NvdDialogBox *dialog) {
        gtk_widget_show_all(dialog->window_handle);
        gtk_main();
}

void nvd_gtk_update_accept_label(NvdDialogBox *dialog) {
        NVD_ASSERT(dialog != NULL);
        gtk_button_set_label(dialog->accept_button, dialog->accept_label);
}
