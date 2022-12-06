#include "nvdialog.h"
#include "nvdialog_cocoa.h"

#include <AppKit/AppKit.h>

#include "../../nvdialog_assert.h"

struct _NvdDialogBox {
	NSAlert         *window_handle;
	const char      *msg;
	const char      *content;
	NvdDialogType   type;
};

NvdDialogBox *nvd_dialog_box_cocoa(const char *title, const char *message, NvdDialogType type)
{
	NvdDialogBox *dialog = malloc(sizeof(struct _NvdDialogBox));
	NVD_RETURN_IF_NULL(dialog);

	dialog->content = message;
	dialog->msg = title;
	dialog->type = type;
	NSAlert *nativedlg = dialog->window_handle = [[NSAlert alloc] init];

	nativedlg.messageText = [NSString stringWithCString: dialog->msg];
	nativedlg.informativeText = [NSString stringWithCString: dialog->content];

	switch (type) {
	case NVD_DIALOG_SIMPLE:
		nativedlg.alertStyle = NSAlertStyleInformational;
		break;
	case NVD_DIALOG_WARNING:
		nativedlg.alertStyle = NSAlertStyleWarning;
		break;
	case NVD_DIALOG_ERROR:
		nativedlg.alertStyle = NSAlertStyleCritical;
		break;
	}

	return dialog;
}

void nvd_show_dialog_box_cocoa(NvdDialogBox *dialog)
{
	[dialog->window_handle runModal];
	[dialog->window_handle release];
}
