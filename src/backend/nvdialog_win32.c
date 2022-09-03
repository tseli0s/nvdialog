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

#include "nvdialog_win32.h"
#include "nvdialog.h"

void nvd_open_file_dialog_win32(const char *title, const char *message) {}

uint32_t nvd_create_win32_dialog(const char *title, const char *message,
                             NvdDialogType type) {
        uint32_t flag;
        switch (type) {
                case NVD_DIALOG_SIMPLE:
                        flag = MB_ICONINFORMATION;
                        break;
                case NVD_DIALOG_WARNING:
                        flag = MB_ICONWARNING;
                        break;
                case NVD_DIALOG_ERROR:
                        flag = MB_ICONHAND;
                        break;
                default: abort();
        }
        return MessageBox(NULL, message, title, MB_OK | flag);
}