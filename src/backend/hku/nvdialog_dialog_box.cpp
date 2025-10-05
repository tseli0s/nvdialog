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

#include "nvdialog_hku.h"
#include "../nvdialog_assert.h"
#include <Alert.h> /* libbe.so. Provides us with BAlert. */

NVD_C_LINKAGE {

NvdDialogBox *nvd_dialog_box_hku(const char *title, const char *message,
                                   NvdDialogType type) {
	/* Call me old fashioned but I'll do it the C way */
        NvdDialogBox *dialog = (NvdDialogBox*)malloc(sizeof(NvdDialogBox));
	NVD_ASSERT(dialog != NULL);

	alert_type tp;
	switch (type) {
		case NVD_DIALOG_SIMPLE:
			tp = B_INFO_ALERT;
			break;
		case NVD_DIALOG_WARNING:
			tp = B_WARNING_ALERT;
			break;
		case NVD_DIALOG_ERROR:
			tp = B_STOP_ALERT;
			break;
		default:
			free(dialog);
			return NULL;
	}

	dialog->msg = (char*)message;
	dialog->accept_label  = "Okay";
	dialog->reject_label  = nullptr;
	dialog->accept_button = nullptr;
	dialog->type = type;
	dialog->window_handle = new BAlert(title, message, dialog->accept_label, nullptr, nullptr, B_WIDTH_AS_USUAL, B_OFFSET_SPACING, tp);

	BAlert *alert = static_cast<BAlert*>(dialog->window_handle);
	alert->AddButton(dialog->accept_label);

	return dialog;
}

void nvd_show_dialog_hku(NvdDialogBox *dialog) {
        BAlert *alert = static_cast<BAlert*>(dialog->window_handle);
	alert->Go();
}

void nvd_dialog_box_set_accept_text_hku(NvdDialogBox *dialog, const char *accept_text) {
        BAlert *alert = static_cast<BAlert*>(dialog->window_handle);
	dialog->accept_label = (char*)accept_text;
	/* TODO: Actually switch the text (Currently I'm a little lost in the docs,
	 * I will finish it later */
}

}
