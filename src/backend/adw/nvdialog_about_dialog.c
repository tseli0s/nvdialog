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

#include "nvdialog_adw.h"
#include "../../nvdialog_assert.h"
#include <stdio.h>

struct _NvdAboutDialog {
        void *raw;
        char *title, *contents;
        char *version;
        char *hyperlinks[6];
        short amount_of_hyperlinks;
        char *image_name;
        bool  image_from_icon;
        void *buttons[4];
        short amount_of_buttons;
        void *layout;
};

static void nvd_set_margins_gtk4(GtkWidget *widget) {
        gtk_widget_set_margin_start(widget, 10);
        gtk_widget_set_margin_end(widget, 10);
        gtk_widget_set_margin_top(widget, 10);
        gtk_widget_set_margin_bottom(widget, 10);
}

NvdAboutDialog *
nvd_about_dialog_adw(const char *appname, const char *brief, const char *logo) {
        NvdAboutDialog *dialog = malloc(sizeof(struct _NvdAboutDialog));
        NVD_RETURN_IF_NULL(dialog);
        /* In order to have a better title. */
        dialog->title    = (char *) appname;
        dialog->contents = (char *) brief;
        dialog->layout   = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
        dialog->raw      = adw_window_new();
        gtk_window_set_default_size(GTK_WINDOW(dialog->raw), 480, 400);

        GtkWidget *titlebar = adw_header_bar_new();
        GtkWidget *title
            = adw_window_title_new(dialog->title, "About Application");
        GtkWidget *label = gtk_label_new("");
        GtkWidget *brief_label = gtk_label_new(dialog->contents);
        gtk_label_set_lines(GTK_LABEL(brief_label), 1);
        nvd_set_margins_gtk4(brief_label);
        nvd_set_margins_gtk4(label);
        gtk_label_set_wrap(GTK_LABEL(brief_label), true);

        char buffer[NVDIALOG_MAXBUF];
        sprintf(buffer,
                "<span font_desc=\"18.0\"><b>About %s:</b></span>",
                dialog->title);
        gtk_label_set_markup(GTK_LABEL(label), buffer);

        adw_header_bar_set_title_widget(ADW_HEADER_BAR(titlebar), title);

        gtk_box_append(GTK_BOX(dialog->layout), titlebar);
        gtk_box_append(GTK_BOX(dialog->layout), label);
        gtk_box_append(GTK_BOX(dialog->layout), brief_label);
        adw_window_set_content(dialog->raw, dialog->layout);
        return dialog;
}

void nvd_about_dialog_set_version_adw(NvdAboutDialog *dialog,
                                      const char     *version) {
        char buffer[NVDIALOG_MAXBUF];
        
        sprintf(buffer,
                "<span font_desc=\"10.0\"><b>Running version %s</b></span>",
                version);
        GtkWidget *label = gtk_label_new("");

        gtk_label_set_markup(GTK_LABEL(label), buffer);
        nvd_set_margins_gtk4(label);
        gtk_box_append(GTK_BOX(dialog->layout), label);
        
        return;
}

void nvd_about_dialog_set_license_link_adw(NvdAboutDialog *dialog,
                                           const char *license_link,
                                           const char *txt) {
        dialog->buttons[0]        = gtk_link_button_new_with_label(txt, license_link);
        dialog->amount_of_buttons = 1;
        gtk_widget_set_margin_start(dialog->buttons[0], 16);
        gtk_widget_set_margin_end(dialog->buttons[0], 16);
        gtk_box_append(GTK_BOX(dialog->layout),
                               dialog->buttons[0]);
}

void nvd_show_about_dialog_adw(NvdAboutDialog *dialog) {
        GtkGrid* grid = GTK_GRID(gtk_grid_new());
        gtk_box_append (GTK_BOX(dialog->layout),
                                GTK_WIDGET(grid));

        gtk_window_present(GTK_WINDOW(dialog->raw));
        while (g_list_model_get_n_items(gtk_window_get_toplevels()) > 0)
                g_main_context_iteration(NULL, true);
}