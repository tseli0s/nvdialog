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

#include <stdio.h>

#include "../../nvdialog_assert.h"
#include "nvdialog_adw.h"
#include "../gtk/nvdialog_gtk.h"

/*
 * There's no more libadwaita code here, it's all replaced by calling on the gtk backend to do the job.
 * The code here exists purely for compatibility and will be removed in the future.
 * Enjoy the remnants here as if you're watching a long dead city inside a mountain. Or something like that.
 */

NvdAboutDialog *nvd_about_dialog_adw(const char *appname, const char *brief,
                                     const char *logo) {
        return nvd_about_dialog_gtk(appname, brief, logo);
}

void nvd_about_dialog_set_version_adw(NvdAboutDialog *dialog,
                                      const char *version) {
        nvd_about_dialog_set_version_gtk(dialog, version);
}

void nvd_about_dialog_set_license_link_adw(NvdAboutDialog *dialog,
                                           const char *license_link,
                                           const char *txt) {
        nvd_about_dialog_set_license_link_gtk(dialog, license_link, txt);
}

void nvd_show_about_dialog_adw(NvdAboutDialog *dialog) {
        nvd_show_about_dialog_gtk(dialog);
}

void *nvd_about_dialog_get_raw_adw(NvdAboutDialog *dialog) {
        NVD_ASSERT(dialog != NULL);
        return dialog->raw;
}