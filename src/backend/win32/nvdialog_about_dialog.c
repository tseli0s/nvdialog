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
#include "nvdialog_win32.h"

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

NvdAboutDialog *nvd_about_dialog_win32(const char *appname,
                                       const char *brief,
                                       const char *logo) {
        NvdAboutDialog *dialog
            = (NvdAboutDialog *)malloc(sizeof(struct _NvdAboutDialog));
        NVD_RETURN_IF_NULL(dialog);

        dialog->title = (char *)appname;
        dialog->contents = (char *)brief;
        dialog->raw = NULL;

        return dialog;
}

void nvd_about_dialog_set_version_win32(NvdAboutDialog *dialog,
                                        const char     *version) {
        dialog->version = (char *)version;
}

void nvd_about_dialog_set_license_link_win32(NvdAboutDialog *dialog,
                                            const char      *license_link, 
                                            const char      *txt) {
        return; /* Unfortunately can't be implemented with the WinAPI. */
}

void nvd_show_about_dialog_win32(NvdAboutDialog *dialog) {
        bool result = ShellAboutA(
            nvd_get_parent(),
            dialog->title,
            dialog->contents,
            NULL /* Another TODO: Make it so icons can be added to Windows
                    dialogs. */
        );

        if (!result)
                nvd_set_error(NVD_INTERNAL_ERROR);
}