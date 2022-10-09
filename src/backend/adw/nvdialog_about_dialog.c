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
#include <stdio.h>

struct _NvdAboutDialog {
        void *raw;
        char *title, contents;
        uint8_t image_buffer;
};

NvdAboutDialog *nvd_about_dialog_adw(const char *appname, const char *brief,
                                     const char *logo) {
        NvdAboutDialog *dialog = malloc(sizeof(struct _NvdAboutDialog));
        NVD_RETURN_IF_NULL(dialog);
        /* In order to have a better title. */
        size_t title_len = strlen("About ") + strlen(appname);
        dialog->title = calloc(1, title_len);
        dialog->contents = brief;

        snprintf(dialog->title, title_len, "About %s", appname);
        dialog->raw = adw_about_window_new();
        if (logo)
                adw_about_window_set_application_icon(dialog->raw, logo);

        adw_about_window_set_application_name(dialog->raw, appname);
        adw_about_window_set_comments(dialog->raw, dialog->contents);

        return dialog;
}