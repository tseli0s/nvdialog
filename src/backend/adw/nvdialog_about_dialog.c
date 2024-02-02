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

#include "nvdialog_adw.h"
#include "../../nvdialog_assert.h"
#include <stdio.h>

NvdAboutDialog *
nvd_about_dialog_adw(const char *appname,
                     const char *brief,
                     const char *logo) {
        NvdAboutDialog *dialog = malloc(sizeof(struct _NvdAboutDialog));
        NVD_RETURN_IF_NULL(dialog);
        /* In order to have a better title. */
        dialog->title    = (char *) appname;
        dialog->contents = (char *) brief;
        dialog->layout   = NULL;
        dialog->raw      = adw_about_window_new();

        if (logo)
                adw_about_window_set_application_icon(dialog->raw, logo);
        
        /* This is a horrible workaround to make text appear on the main window. We'll take it though. */
        adw_about_window_set_developer_name(dialog->raw, brief);
        adw_about_window_set_application_name(dialog->raw, dialog->title);
        return dialog;
}

void nvd_about_dialog_set_version_adw(NvdAboutDialog *dialog,
                                      const char     *version) {
        adw_about_window_set_version(dialog->raw, version);
}

void nvd_about_dialog_set_license_link_adw(NvdAboutDialog *dialog,
                                           const char *license_link,
                                           const char *txt) {
        adw_about_window_add_link(dialog->raw, txt, license_link);
}

void nvd_show_about_dialog_adw(NvdAboutDialog *dialog) {
        gtk_window_present(GTK_WINDOW(dialog->raw));
        g_main_context_iteration(NULL, true);
}

void *nvd_about_dialog_get_raw_adw(NvdAboutDialog *dialog) {
        NVD_ASSERT(dialog != NULL);
        return dialog->raw;
}