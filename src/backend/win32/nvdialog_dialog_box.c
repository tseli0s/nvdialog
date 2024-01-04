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
#include "nvdialog_win32.h"
#include <stdint.h>
#include <wchar.h>
#include <windows.h>
#include <winuser.h>

NvdDialogBox *nvd_dialog_box_win32(const char   *title,
                                   const char   *message,
                                   NvdDialogType type) {
        NVD_ASSERT(title   != NULL);
        NVD_ASSERT(message != NULL);

        NvdDialogBox *dialog = (NvdDialogBox *)malloc(sizeof(struct _NvdDialogBox));
        NVD_RETURN_IF_NULL(dialog);

        dialog->accept_label = "Ok";
        dialog->reject_label = "Deny";

        dialog->msg     = title;
        dialog->content = message;
        dialog->type    = type;

        return dialog;
}

void nvd_show_dialog_win32(NvdDialogBox *dialog) {
        uint32_t flag;
        switch (dialog->type) {
        case NVD_DIALOG_SIMPLE:
                flag = MB_ICONINFORMATION;
                break;
        case NVD_DIALOG_WARNING:
                flag = MB_ICONWARNING;
                break;
        case NVD_DIALOG_ERROR:
                flag = MB_ICONHAND;
                break;
        }

        MessageBox(nvd_get_parent(), dialog->content, dialog->msg, MB_OK | flag);
}