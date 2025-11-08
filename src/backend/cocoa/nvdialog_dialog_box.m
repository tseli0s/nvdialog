#include "nvdialog.h"
#include "nvdialog_cocoa.h"
#include "../../nvdialog_util.h"

#include <AppKit/AppKit.h>

#include "../../nvdialog_assert.h"

NvdDialogBox *nvd_dialog_box_cocoa(const char *title, const char *message, NvdDialogType type)
{
	NvdDialogBox *dialog = nvd_malloc(sizeof(struct _NvdDialogBox));
	NVD_RETURN_IF_NULL(dialog);

	dialog->content = message;
	dialog->msg = title;
	dialog->type = type;
	NSAlert *nativedlg = dialog->window_handle = [[NSAlert alloc] init];

	nativedlg.messageText = [NSString stringWithUTF8String:dialog->msg];;
	nativedlg.informativeText = [NSString stringWithUTF8String:dialog->content];

	/* GNUstep uses slightly different naming. It should be easy to patch it but I just want it to run for now. */
	#ifndef _NVD_USE_GNUSTEP
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
	#endif

	return dialog;
}

void nvd_show_dialog_cocoa(NvdDialogBox *dialog)
{
	[dialog->window_handle runModal];
	#ifndef _NVD_USE_GNUSTEP
	[dialog->window_handle orderOut];
	#endif
}

void *nvd_dialog_box_get_raw_cocoa(NvdDialogBox *dlg)
{
	return dlg->window_handle;
}
