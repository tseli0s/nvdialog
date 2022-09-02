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
#include <stdbool.h>

void *nvd_create_gtk_dialog(const char *title, const char *message,
                            NvdDialogType type) {
        GtkWidget *dialog, *label, *content_area, *ok_button;
        GtkDialogFlags flags = GTK_DIALOG_USE_HEADER_BAR;

        dialog = gtk_dialog_new_with_buttons(title, NULL, flags, NULL,
                                             GTK_RESPONSE_NONE, NULL);
        content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
        label = gtk_label_new(message);
        ok_button = gtk_button_new_with_label("Ok");

        gtk_widget_set_margin_bottom(label, 12);
        gtk_widget_set_margin_start(label, 12);
        gtk_widget_set_margin_end(label, 12);
        gtk_widget_set_margin_top(label, 12);

        gtk_widget_set_margin_bottom(ok_button, 12);
        gtk_widget_set_margin_start(ok_button, 12);
        gtk_widget_set_margin_end(ok_button, 12);
        gtk_widget_set_margin_top(ok_button, 12);

        g_signal_connect_swapped(dialog, "response",
                                 G_CALLBACK(gtk_widget_destroy), dialog);
        g_signal_connect_swapped(ok_button, "clicked", G_CALLBACK(gtk_main_quit), NULL);

        gtk_container_add(GTK_CONTAINER(content_area), label);
        gtk_container_add(GTK_CONTAINER (content_area), ok_button);
        
        gtk_widget_show_all(dialog);
        gtk_main();
        
        return dialog;
}