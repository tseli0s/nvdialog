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

NvdDialogBox *
nvd_dialog_box_adw(const char *title, const char *message, NvdDialogType type) {
        NvdDialogBox *dialog = malloc(sizeof(struct _NvdDialogBox));
        NVD_RETURN_IF_NULL(dialog);

        dialog->content = message;
        dialog->msg = title;
        dialog->type = type;
        dialog->window_handle
            = adw_message_dialog_new(nvd_get_parent(), title, message);
        adw_message_dialog_add_response(
            ADW_MESSAGE_DIALOG(dialog->window_handle), "accept", "Okay");
        adw_message_dialog_set_default_response(
            ADW_MESSAGE_DIALOG(dialog->window_handle), "accept");

        switch (type) {
        case NVD_DIALOG_WARNING:
        case NVD_DIALOG_ERROR:
                adw_message_dialog_set_response_appearance(
                    ADW_MESSAGE_DIALOG(dialog->window_handle),
                    "accept",
                    ADW_RESPONSE_DESTRUCTIVE);
                break;

        default:
        case NVD_DIALOG_SIMPLE:
                break;
        }
        return dialog;
}

inline void *nvd_dialog_box_get_raw_adw(NvdDialogBox *dlg) {
        NVD_ASSERT(dlg != NULL);
        return dlg->window_handle;
}

void nvd_show_dialog_adw(NvdDialogBox *dialog) {
        gtk_window_present(GTK_WINDOW(dialog->window_handle));
        g_main_context_iteration(NULL, true);
        /* TODO: Forcefully terminate the Gtk / libadwaita loop. */
}