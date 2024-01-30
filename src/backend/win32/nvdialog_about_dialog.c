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

#include "nvdialog_win32.h"
#include "../../nvdialog_assert.h"

static HICON nvd_load_hicon_win32(const char* path) {
    const HICON icon = (HICON) LoadImage(
        NULL,
        path,
        IMAGE_ICON,
        0,
        0,
        LR_LOADFROMFILE
    );

    NVD_RETURN_IF_NULL(icon);
    return icon;
}

NvdAboutDialog *nvd_about_dialog_win32(const char *appname,
                                       const char *brief,
                                       const char *logo) {
        (void) logo;
        NvdAboutDialog *dialog = (NvdAboutDialog *)malloc(sizeof(struct _NvdAboutDialog));
        NVD_RETURN_IF_NULL(dialog);

        dialog->title    = (char *)appname;
        dialog->contents = (char *)brief;
        dialog->raw      = NULL;

        return dialog;
}

void nvd_about_dialog_set_version_win32(NvdAboutDialog *dialog,
                                        const char     *version) {
        dialog->version = (char *)version;
}

void nvd_about_dialog_set_license_link_win32(NvdAboutDialog *dialog,
                                            const char      *license_link, 
                                            const char      *txt) {
        (void) dialog;
        (void) license_link;
        (void) txt;

        return; /* Unfortunately can't be implemented with the WinAPI. */
}

void nvd_show_about_dialog_win32(NvdAboutDialog *dialog) {
        HICON app_icon = NULL;
        if (dialog->image_name != NULL) {
                app_icon = nvd_load_hicon_win32(dialog->image_name);
                NVD_ASSERT(app_icon != NULL);
        }

        int result = ShellAbout(nvd_get_parent(),
                                dialog->title,
                                dialog->contents,
                                app_icon
                        );

        (app_icon != NULL) ? DestroyIcon(app_icon): (void) app_icon;
        if (!result) nvd_set_error(NVD_INTERNAL_ERROR);
}