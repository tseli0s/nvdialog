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
#include "../../nvdialog_macros.h"
#include "nvdialog_adw.h"

struct NvdQuestionData {
        NvdReply reply;
};

inline static void nvd_reply_write_ok(NvdReply *reply) {
        *reply = NVD_REPLY_OK;
}

inline static void nvd_reply_write_cancel(NvdReply *reply) {
        *reply = NVD_REPLY_CANCEL;
}
inline static void nvd_reply_write_no(NvdReply *reply) {
        *reply = NVD_REPLY_NO;
}

NvdQuestionBox *nvd_question_adw(const char       *title,
                                 const char       *question,
                                 NvdQuestionButton buttons) {
        NvdQuestionBox *dialog = malloc(sizeof(struct _NvdQuestionBox));
        NVD_RETURN_IF_NULL(dialog);
        dialog->title = (char *)title;
        dialog->contents = (char *)question;
        dialog->reply
            = NVD_REPLY_CANCEL; /* Default reply if no other was given */

        dialog->window_handle = (AdwMessageDialog *)adw_message_dialog_new(
            nvd_get_parent(), dialog->title, dialog->contents);

        NVD_CHECK_INTERNAL(dialog->window_handle, dialog, NULL);

        switch (buttons) {
        case NVD_YES_NO:
                adw_message_dialog_add_response(
                    ADW_MESSAGE_DIALOG(dialog->window_handle),
                    "cancel",
                    "Cancel");
                break;
        case NVD_YES_NO_CANCEL:
                adw_message_dialog_add_response(
                    ADW_MESSAGE_DIALOG((GtkWidget *)dialog->window_handle),
                    "cancel",
                    "Cancel");
                adw_message_dialog_add_response(
                    ADW_MESSAGE_DIALOG((GtkWidget *)dialog->window_handle),
                    "reject",
                    "No");
                break;
        case NVD_YES_CANCEL:
                adw_message_dialog_add_response(
                    ADW_MESSAGE_DIALOG((GtkWidget *)dialog->window_handle),
                    "reject",
                    "No");
                break;
        default:
                return NULL;
        }
        adw_message_dialog_add_response(
            ADW_MESSAGE_DIALOG((GtkWidget *)dialog->window_handle),
            "accept",
            "Okay");
        /* Just for better looks. */
        adw_message_dialog_set_response_appearance(
            ADW_MESSAGE_DIALOG((GtkWidget *)dialog->window_handle),
            "accept",
            ADW_RESPONSE_SUGGESTED);
        return dialog;
}

NvdReply nvd_get_reply_adw(NvdQuestionBox *box) {
        g_signal_connect_swapped((GtkWidget *)box->window_handle,
                                 "response::accept",
                                 G_CALLBACK(nvd_reply_write_ok),
                                 &box->reply);
        g_signal_connect_swapped((GtkWidget *)box->window_handle,
                                 "response::reject",
                                 G_CALLBACK(nvd_reply_write_no),
                                 &box->reply);
        g_signal_connect_swapped((GtkWidget *)box->window_handle,
                                 "response::cancel",
                                 G_CALLBACK(nvd_reply_write_cancel),
                                 &box->reply);

        gtk_window_present(GTK_WINDOW(box->window_handle));
        g_main_context_iteration(NULL, true);
        return box->reply;
}

void *nvd_dialog_question_get_raw_adw(NvdQuestionBox *dlg) {
        NVD_ASSERT(dlg != NULL);
        return dlg->window_handle;
}