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

#include "../../nvdialog_assert.h"
#include "nvdialog_gtk.h"

NvdQuestionBox *nvd_question_gtk(const char *title, const char *question,
                                 NvdQuestionButton buttons) {
        NvdQuestionBox *dialog = malloc(sizeof(NvdQuestionBox));
        NVD_RETURN_IF_NULL(dialog);

        GtkButtonsType btn_type;
        switch (buttons) {
                case NVD_YES_NO:
                        btn_type = GTK_BUTTONS_YES_NO;
                        break;
                /* We'll set these two manually. */
                case NVD_YES_CANCEL:
                        btn_type = GTK_BUTTONS_NONE;
                        break;
                case NVD_YES_NO_CANCEL:
                        btn_type = GTK_BUTTONS_NONE;
                        break;
                default:
                        btn_type = GTK_BUTTONS_YES_NO;
                        break;
        }

        GtkWidget *msgdlg = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL,
                                                   GTK_MESSAGE_QUESTION,
                                                   btn_type, "%s", question);

        gtk_window_set_title(GTK_WINDOW(msgdlg), title);

        if (buttons == NVD_YES_NO_CANCEL) {
                gtk_dialog_add_buttons(GTK_DIALOG(msgdlg), "Yes",
                                       GTK_RESPONSE_YES, "No", GTK_RESPONSE_NO,
                                       "Cancel", GTK_RESPONSE_CANCEL, NULL);
        } else if (buttons == NVD_YES_CANCEL) {
                gtk_dialog_add_buttons(GTK_DIALOG(msgdlg), "Yes",
                                       GTK_RESPONSE_YES, "Cancel",
                                       GTK_RESPONSE_CANCEL, NULL);
        }

        dialog->window_handle = msgdlg;
        dialog->reply = NVD_REPLY_CANCEL;
        return dialog;
}

void *nvd_dialog_question_get_raw_gtk(NvdQuestionBox *dlg) {
        NVD_ASSERT(dlg != NULL);
        return dlg->window_handle;
}

NvdReply nvd_get_reply_gtk(NvdQuestionBox *box) {
        gint resp = gtk_dialog_run(GTK_DIALOG(box->window_handle));
        switch (resp) {
                case GTK_RESPONSE_YES:
                        box->reply = NVD_REPLY_OK;
                        break;
                case GTK_RESPONSE_NO:
                        box->reply = NVD_REPLY_NO;
                        break;
                case GTK_RESPONSE_CANCEL:
                case GTK_RESPONSE_DELETE_EVENT:
                default:
                        box->reply = NVD_REPLY_CANCEL;
                        break;
        }
        gtk_widget_destroy(box->window_handle);
        while (g_main_context_iteration(NULL, FALSE));
        return box->reply;
}