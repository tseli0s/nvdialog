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

#include <stdlib.h>
#include <string.h>

#include "dialogs/nvdialog_input_box.h"
#include "glib.h"
#include "gtk/gtk.h"
#include "nvdialog_gtk.h"
#include "nvdialog_string.h"

static void nvd_fetch_user_input(GtkWidget *button, gpointer data) {
        NvdInputBox *box = data;
        GtkWidget *entry = g_object_get_data(G_OBJECT(button), "entry");
        const char *text = gtk_entry_get_text(GTK_ENTRY(entry));

        if (!strlen(text))
                box->user_input = nvd_string_new(NULL);
        else
                box->user_input = nvd_string_new(text);

        gtk_widget_destroy(GTK_WIDGET(box->window_handle));
        gtk_main_quit();
}

NvdInputBox *nvd_input_box_gtk(const char *title, const char *message) {
        const char *default_msg = "Enter your text below...";
        NvdInputBox *obj = nvd_malloc(sizeof(NvdInputBox));
        obj->title = nvd_string_new(title);

        obj->user_input = NULL;
        obj->window_handle = (void *)gtk_window_new(GTK_WINDOW_TOPLEVEL);

        gtk_window_set_title(GTK_WINDOW(obj->window_handle), title);
        gtk_window_set_resizable(GTK_WINDOW(obj->window_handle), false);
        gtk_window_set_decorated(GTK_WINDOW(obj->window_handle), true);
        gtk_window_set_modal(GTK_WINDOW(obj->window_handle), true);

        GtkWidget *container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
        GtkWidget *entry = gtk_entry_new();

        gtk_entry_set_activates_default(GTK_ENTRY(entry), true);
        gtk_widget_set_margin_start(container, 6);
        gtk_widget_set_margin_end(container, 6);
        gtk_widget_set_margin_top(container, 6);
        gtk_widget_set_margin_bottom(container, 6);

        if (message) {
                GtkWidget *label = gtk_label_new(message);
                gtk_container_add(GTK_CONTAINER(container), label);
                obj->content = nvd_string_new(message);
        } else {
                GtkWidget *label = gtk_label_new(default_msg);
                gtk_container_add(GTK_CONTAINER(container), label);
                obj->content = nvd_string_new(default_msg);
        }

        GtkWidget *button = gtk_button_new_with_label("Ok");
        g_object_set_data(G_OBJECT(button), "entry", entry);
        g_signal_connect(button, "clicked", G_CALLBACK(nvd_fetch_user_input),
                         obj);
        gtk_container_add(GTK_CONTAINER(container), entry);
        gtk_container_add(GTK_CONTAINER(container), button);
        gtk_container_add(GTK_CONTAINER(obj->window_handle), container);

        return obj;
}

void nvd_show_input_box_gtk(NvdInputBox *box) {
        gtk_widget_show_all(GTK_WIDGET(box->window_handle));
        gtk_main();
}

NvdDynamicString *nvd_input_box_get_string_gtk(NvdInputBox *box) {
        return box->user_input;
}