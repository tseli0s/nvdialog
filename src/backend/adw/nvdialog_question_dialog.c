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
#include "../../nvdialog_assert.h"
#include "../../nvdialog_macros.h"

struct _NvdQuestionBox {
        void* window_handle;
        char* title, *contents;
        NvdReply reply;
};

NvdQuestionBox *nvd_question_adw(const char *title,
                                 const char *question,
                                 NvdQuestionButton buttons) {
        NvdQuestionBox *box = malloc(sizeof(struct _NvdQuestionBox));
        NVD_RETURN_IF_NULL(box);

        box->title    = (char*) title;
        box->contents = (char*) question;
        box->window_handle = adw_message_dialog_new(nvd_get_parent(), title, question);

        adw_message_dialog_add_response(ADW_MESSAGE_DIALOG(box->window_handle), "accept",
                                        "Yes");
        adw_message_dialog_set_default_response(ADW_MESSAGE_DIALOG(box->window_handle),
                                                "accept");

        if (buttons == NVD_YES_CANCEL) {
                adw_message_dialog_add_response(ADW_MESSAGE_DIALOG(box->window_handle),
                                                "cancel", "Cancel");
        } else if (buttons == NVD_YES_NO_CANCEL) {
                adw_message_dialog_add_response(ADW_MESSAGE_DIALOG(box->window_handle),
                                                "cancel", "Cancel");
                adw_message_dialog_add_response(ADW_MESSAGE_DIALOG(box->window_handle),
                                                "reject", "No");
        } else {
                adw_message_dialog_add_response(ADW_MESSAGE_DIALOG(box->window_handle),
                                                "reject", "No");
        }
        box->reply = NVD_REPLY_CANCEL;
        gtk_window_present(GTK_WINDOW(box->window_handle));
        return box;
}

void nvd_get_reply_adw(NvdQuestionBox* box) {
        nvd_show_dialog((void*) box);
        return;
}