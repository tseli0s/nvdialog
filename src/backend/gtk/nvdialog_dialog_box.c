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
#include "gtk/gtk.h"
#include "nvdialog_core.h"
#include "nvdialog_gtk.h"

NvdDialogBox *nvd_dialog_box_gtk(const char *title, const char *message,
                                 NvdDialogType type) {
        NvdDialogBox *dialog = malloc(sizeof(NvdDialogBox));
        NVD_RETURN_IF_NULL(dialog);

        dialog->accept_label = "Okay";
        dialog->content = (char *)message;
        dialog->msg = (char *)title;
        dialog->type = type;

        GtkMessageType gtk_type;
        switch (type) {
                case NVD_DIALOG_WARNING:
                        gtk_type = GTK_MESSAGE_WARNING;
                        break;
                case NVD_DIALOG_ERROR:
                        gtk_type = GTK_MESSAGE_ERROR;
                        break;
                default:
                case NVD_DIALOG_SIMPLE:
                        gtk_type = GTK_MESSAGE_INFO;
                        break;
        }

        dialog->window_handle =
                gtk_message_dialog_new(nvd_get_parent(), GTK_DIALOG_MODAL | GTK_DIALOG_USE_HEADER_BAR,
                                       gtk_type, GTK_BUTTONS_OK, "%s", message);
        gtk_window_set_title(GTK_WINDOW(dialog->window_handle), title);
        GtkWidget *ok_button = gtk_dialog_get_widget_for_response(
                GTK_DIALOG(dialog->window_handle), GTK_RESPONSE_OK);
        dialog->accept_button = ok_button;
        g_signal_connect_swapped(dialog->window_handle, "response",
                                 G_CALLBACK(gtk_widget_destroy),
                                 GTK_WIDGET(dialog->window_handle));

        return dialog;
}

inline void *nvd_dialog_box_get_raw_gtk(NvdDialogBox *dlg) {
        NVD_ASSERT(dlg != NULL);
        return dlg->window_handle;
}

void nvd_show_dialog_gtk(NvdDialogBox *dialog) {
        gtk_dialog_run(GTK_DIALOG(dialog->window_handle));
        gtk_main_quit();
}

void nvd_gtk_update_accept_label(NvdDialogBox *dialog) {
        NVD_ASSERT(dialog != NULL);
        gtk_button_set_label(dialog->accept_button, dialog->accept_label);
}

void nvd_dialog_box_set_accept_text_gtk(NvdDialogBox *box, const char *text) {
        /* FIXME: Use NvdDynamicString here instead. */
        box->accept_label = (char*) text; 
        nvd_gtk_update_accept_label(box);
}
