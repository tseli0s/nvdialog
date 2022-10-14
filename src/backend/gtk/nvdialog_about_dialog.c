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

#include "../../nvdialog_assert.h"
#include "nvdialog_gtk.h"
#include <stdio.h>

struct _NvdAboutDialog {
        void *raw;
        char *title, *contents;
        char *version;
        char *hyperlinks[6];
        short amount_of_hyperlinks;
        char *image_name;
        bool image_from_icon;
        void *buttons[4];
        short amount_of_buttons;
        void *layout;
};

static inline void nvd_set_margins_gtk3(GtkWidget *widget) {
        gtk_widget_set_margin_start(widget, 16);
        gtk_widget_set_margin_end(widget, 16);
        gtk_widget_set_margin_top(widget, 16);
        gtk_widget_set_margin_bottom(widget, 16);
}

NvdAboutDialog *nvd_about_dialog_gtk(const char *appname, const char *brief,
                                     const char *icon_name) {
        NvdAboutDialog *dialog = malloc(sizeof(struct _NvdAboutDialog));
        NVD_RETURN_IF_NULL(dialog);
        dialog->title = (char *)appname;
        dialog->contents = (char *)brief;

        char buffer[NVDIALOG_MAXBUF];
        sprintf(buffer, "%s%s", "/usr/share/icons/hicolor/",
                icon_name); // TODO: Fix this to use the icon theme.
        GdkPixbuf *img = gdk_pixbuf_new_from_file(buffer, NULL);
        if (!img) {
                img = gdk_pixbuf_new_from_file(
                    "/usr/share/icons/hicolor/48x48/status/computer.png", NULL);
                NVD_RETURN_IF_NULL(img);
        }

        dialog->raw = gtk_about_dialog_new();
        gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(dialog->raw),
                                          appname);
        gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog->raw), brief);
        gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(dialog->raw), img);
        return dialog;
}

void nvd_about_dialog_set_version_gtk(NvdAboutDialog *dialog,
                                      const char *version) {
        gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog->raw), version);
        return;
}

void nvd_show_about_dialog_gtk(NvdAboutDialog *dialog) {
        gtk_dialog_run(GTK_DIALOG(dialog->raw));
        return;
}