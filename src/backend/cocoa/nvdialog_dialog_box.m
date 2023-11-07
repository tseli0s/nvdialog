#include "nvdialog.h"
#include "nvdialog_cocoa.h"

#include <AppKit/AppKit.h>

#include "../../nvdialog_assert.h"

NvdDialogBox *nvd_dialog_box_cocoa(const char *title, const char *message, NvdDialogType type)
{
	NvdDialogBox *dialog = malloc(sizeof(struct _NvdDialogBox));
	NVD_RETURN_IF_NULL(dialog);

	dialog->content = message;
	dialog->msg = title;
	dialog->type = type;
	NSAlert *nativedlg = dialog->window_handle = [[NSAlert alloc] init];

	nativedlg.messageText = @(dialog->msg);
	nativedlg.informativeText = @(dialog->content);

	switch (type) {
    default:
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

void nvd_show_dialog_cocoa(NvdDialogBox *dialog)
{
	[dialog->window_handle runModal];
	[dialog->window_handle orderOut];
}

void *nvd_dialog_box_get_raw_cocoa(NvdDialogBox *dlg)
{
	return dlg->window_handle;
}
