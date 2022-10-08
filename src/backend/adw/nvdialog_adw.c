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
#include "nvdialog_types.h"
#include "dialogs/nvdialog_dialog_box.h"

inline static void nvd_reply_write_ok(NvdReply *reply) {
        *reply = NVD_REPLY_OK;
}

inline static void nvd_reply_write_cancel(NvdReply *reply) {
        *reply = NVD_REPLY_CANCEL;
}
inline static void nvd_reply_write_no(NvdReply *reply) {
        *reply = NVD_REPLY_NO;
}

NvdDialogBox *nvd_dialog_box_adw(const char *title, const char *message,
                                 NvdDialogType type) {
        GtkWidget *dialog = adw_message_dialog_new(nvd_get_parent(), title, message);

        adw_message_dialog_add_response(ADW_MESSAGE_DIALOG(dialog), "accept",
                                        "Okay");
        adw_message_dialog_set_default_response(ADW_MESSAGE_DIALOG(dialog),
                                                "accept");

        switch (type) {
        case NVD_DIALOG_WARNING:
        case NVD_DIALOG_ERROR:
                adw_message_dialog_set_response_appearance(
                    ADW_MESSAGE_DIALOG(dialog), "accept",
                    ADW_RESPONSE_DESTRUCTIVE);
                break;

        default:
        case NVD_DIALOG_SIMPLE:
                break;
        }

        gtk_window_present(GTK_WINDOW(dialog));
        while (g_list_model_get_n_items(gtk_window_get_toplevels()) > 0) {
                g_main_context_iteration(NULL, true);
        }

        return NULL;
}

NvdReply nvd_question_adw(const char *title, const char *question,
                          NvdQuestionButton buttons) {
        GtkWidget *dialog = adw_message_dialog_new(nvd_get_parent(), title, question);

        adw_message_dialog_add_response(ADW_MESSAGE_DIALOG(dialog), "accept",
                                        "Yes");
        adw_message_dialog_set_default_response(ADW_MESSAGE_DIALOG(dialog),
                                                "accept");

        if (buttons == NVD_YES_CANCEL) {
                adw_message_dialog_add_response(ADW_MESSAGE_DIALOG(dialog),
                                                "cancel", "Cancel");
        } else if (buttons == NVD_YES_NO_CANCEL) {
                adw_message_dialog_add_response(ADW_MESSAGE_DIALOG(dialog),
                                                "cancel", "Cancel");
                adw_message_dialog_add_response(ADW_MESSAGE_DIALOG(dialog),
                                                "reject", "No");
        } else {
                adw_message_dialog_add_response(ADW_MESSAGE_DIALOG(dialog),
                                                "reject", "No");
        }

        NvdReply reply = NVD_REPLY_CANCEL;
        g_signal_connect_swapped(dialog, "response::accept",
                                 G_CALLBACK(nvd_reply_write_ok), &reply);
        g_signal_connect_swapped(dialog, "response::reject",
                                 G_CALLBACK(nvd_reply_write_no), &reply);
        g_signal_connect_swapped(dialog, "response::cancel",
                                 G_CALLBACK(nvd_reply_write_cancel), &reply);

        gtk_window_present(GTK_WINDOW(dialog));
        while (g_list_model_get_n_items(gtk_window_get_toplevels()) > 0) {
                g_main_context_iteration(NULL, true);
        }
        return reply;
}