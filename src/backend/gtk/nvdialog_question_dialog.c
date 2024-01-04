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

#include "../../nvdialog_assert.h"
#include "../../nvdialog_macros.h"
#include "nvdialog_gtk.h"

struct NvdQuestionData {
        NvdReply reply;
};

inline static void nvd_reply_write_ok(NvdReply *reply) {
        *reply = NVD_REPLY_OK;
        gtk_main_quit();
}

inline static void nvd_reply_write_cancel(NvdReply *reply) {
        *reply = NVD_REPLY_CANCEL;
        gtk_main_quit();
}
inline static void nvd_reply_write_no(NvdReply *reply) {
        *reply = NVD_REPLY_NO;
        gtk_main_quit();
}

static inline void nvd_set_margins_gtk3(GtkWidget *widget) {
        gtk_widget_set_margin_start(widget, 16);
        gtk_widget_set_margin_end(widget, 16);
        gtk_widget_set_margin_top(widget, 16);
        gtk_widget_set_margin_bottom(widget, 16);
}

NvdQuestionBox *nvd_question_gtk(const char       *title,
                                 const char       *question,
                                 NvdQuestionButton buttons) {
        NvdQuestionBox *dialog = malloc(sizeof(struct _NvdQuestionBox));
        NVD_RETURN_IF_NULL(dialog);

        dialog->title = (char *)title;
        dialog->contents = (char *)question;
        dialog->reply
            = NVD_REPLY_CANCEL; /* Default reply if no other was given */

        const char *icon_name = "dialog-question";
        GtkWidget  *grid, *button_yes, *button_no, *button_cancel, *text, *icon;

        dialog->window_handle = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_resizable(GTK_WINDOW(dialog->window_handle), false);
        gtk_window_set_title(GTK_WINDOW(dialog->window_handle), title);
        gtk_window_set_default_size(GTK_WINDOW(dialog->window_handle), 200, 150);
        text = gtk_label_new(question);
        gtk_label_set_line_wrap(GTK_LABEL(text), true);
        grid = gtk_grid_new();
        gtk_container_add(GTK_CONTAINER(dialog->window_handle), grid);
        icon = gtk_image_new_from_icon_name(icon_name, GTK_ICON_SIZE_DIALOG);
        button_yes = gtk_button_new_with_label("Yes");
        g_signal_connect_swapped(button_yes,
                                 "clicked",
                                 G_CALLBACK(nvd_reply_write_ok),
                                 &dialog->reply);

        button_no = NULL;
        button_cancel = NULL;

        switch (buttons) {
        case NVD_YES_NO:
                button_no = gtk_button_new_with_label("No");
                nvd_set_margins_gtk3(button_no);
                /* Yes already created, skipping. */
                break;

        case NVD_YES_NO_CANCEL:
                button_cancel = gtk_button_new_with_label("Cancel");
                button_no = gtk_button_new_with_label("No");
                nvd_set_margins_gtk3(button_no);
                nvd_set_margins_gtk3(button_cancel);
                break;

        case NVD_YES_CANCEL:
                button_cancel = gtk_button_new_with_label("Cancel");
                nvd_set_margins_gtk3(button_cancel);
        }

        gtk_grid_attach(GTK_GRID(grid), icon, 0, 0, 1, 1);
        gtk_grid_attach(GTK_GRID(grid), text, 1, 0, 1, 1);
        gtk_grid_attach(GTK_GRID(grid), button_yes, 0, 1, 1, 1);

        nvd_set_margins_gtk3(button_yes);
        nvd_set_margins_gtk3(icon);
        nvd_set_margins_gtk3(text);

        if (button_no) {
                gtk_grid_attach(GTK_GRID(grid), button_no, 1, 1, 1, 1);
                g_signal_connect_swapped(button_no,
                                         "clicked",
                                         G_CALLBACK(nvd_reply_write_no),
                                         &dialog->reply);
        }
        if (button_cancel) {
                gtk_grid_attach(GTK_GRID(grid), button_cancel, 2, 1, 1, 1);
                g_signal_connect_swapped(button_cancel,
                                         "clicked",
                                         G_CALLBACK(nvd_reply_write_cancel),
                                         &dialog->reply);
        }

        gtk_grid_set_row_spacing(GTK_GRID(grid), 12);
        return dialog;
}

void *nvd_dialog_question_get_raw_gtk(NvdQuestionBox *dlg) {
        NVD_ASSERT(dlg != NULL);
        return dlg->window_handle;
}

NvdReply nvd_get_reply_gtk(NvdQuestionBox *box) {
        g_signal_connect_swapped(
            box->window_handle, "destroy", G_CALLBACK(gtk_main_quit), NULL);

        gtk_widget_show_all(GTK_WIDGET(box->window_handle));
        gtk_main();
        return box->reply;
}