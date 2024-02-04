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
#include "nvdialog_gtk.h"
#include <stdio.h>
#include <string.h>

static inline void nvd_set_margins_gtk3(GtkWidget *widget) {
        gtk_widget_set_margin_start(widget, 16);
        gtk_widget_set_margin_end(widget, 16);
        gtk_widget_set_margin_top(widget, 16);
        gtk_widget_set_margin_bottom(widget, 16);
}

NvdAboutDialog *nvd_about_dialog_gtk(const char *appname,
                                     const char *brief,
                                     const char *icon_name) {
        GdkPixbuf *img         = NULL;
        NvdAboutDialog *dialog = malloc(sizeof(struct _NvdAboutDialog));
        NVD_RETURN_IF_NULL(dialog);
        
        dialog->title          = (char *)appname;
        dialog->contents       = (char *)brief;

        
        
        dialog->raw = gtk_about_dialog_new();
        gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(dialog->raw),
                                          appname);
        gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog->raw), brief);
        if (icon_name) {
                size_t len = 0;
                const char *icons_path = "/usr/share/icons/hicolor/256x256/apps/";
                GError *err = NULL;
                len += strlen(icons_path);
                len += strlen(icon_name);
                len += 1; // NULL byte
                char *buffer = malloc(len * sizeof(char));
                if (!buffer) {
                        NVD_ASSERT(buffer != NULL);
                        nvd_set_error(NVD_OUT_OF_MEMORY);
                        return NULL;
                }
                sprintf(buffer,
                        "%s%s",
                        icons_path,
                        icon_name);
                buffer[len] = '\0';
                img = gdk_pixbuf_new_from_file(buffer, &err);
                if (!img) {
                        NVD_ASSERT(img != NULL);
                        nvd_set_error(NVD_INTERNAL_ERROR);
                        nvd_error_message("Failed to load '%s': %s.", buffer, err->message);
                        return NULL;
                }

                gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(dialog->raw), img);
        }
        
        return dialog;
}

void nvd_about_dialog_set_version_gtk(NvdAboutDialog *dialog,
                                      const char     *version) {
        gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog->raw), version);
        return;
}

void nvd_about_dialog_set_license_link_gtk(NvdAboutDialog *dialog,
                                           const char     *license_link, 
                                           const char     *txt) {
        gtk_about_dialog_set_license(GTK_ABOUT_DIALOG(dialog->raw),
                                     license_link);
        return;
}

void nvd_show_about_dialog_gtk(NvdAboutDialog *dialog) {
        gtk_dialog_run(GTK_DIALOG(dialog->raw));
        return;
}

void *nvd_about_dialog_get_raw_gtk(NvdAboutDialog *dialog) {
        NVD_ASSERT(dialog != NULL);
        return dialog->raw;
}