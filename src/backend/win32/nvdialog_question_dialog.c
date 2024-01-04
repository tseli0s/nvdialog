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

NvdQuestionBox *nvd_question_win32(const char       *title,
                                   const char       *question,
                                   NvdQuestionButton buttons) {
        NvdQuestionBox *box = malloc(sizeof(struct _NvdQuestionBox));
        NVD_RETURN_IF_NULL(box);

        box->title    = (char *)title;
        box->contents = (char *)question;
        box->buttons  = buttons;

        return box;
}

NvdReply nvd_get_reply_win32(NvdQuestionBox *box) {
        uint32_t flag = 0;
        switch (box->buttons) {
        case NVD_YES_NO:
        case NVD_YES_CANCEL:
                flag = MB_YESNO;
                break;
        case NVD_YES_NO_CANCEL:
                flag = MB_YESNOCANCEL;
                break;
        default:
                nvd_set_error(NVD_INVALID_PARAM);
                return -1;
        }
        int32_t reply = MessageBox(nvd_get_parent(),
                                   box->contents,
                                   box->title,
                                   (unsigned int) flag | MB_ICONQUESTION);
        switch (reply) {
        case IDYES:
                box->reply = NVD_REPLY_OK;
                break;
        case IDNO:
                box->reply = NVD_REPLY_NO;
                break;
        case IDCANCEL:
                box->reply = NVD_REPLY_CANCEL;
                break;
        }
        return box->reply;
}