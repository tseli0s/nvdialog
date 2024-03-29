#include "nvdialog.h"
#include "nvdialog_cocoa.h"

#include <AppKit/AppKit.h>
#include <stdbool.h>

#include "../../nvdialog_assert.h"

/* Contributor's note: NSOpenPanel inherits from NSSavePanel. Unrelated in this context but you may find it useful */

NvdFileDialog *nvd_open_file_dialog_cocoa(const char *title, const char *file_extensions)
{
	NvdFileDialog *dialog = malloc(sizeof(struct _NvdFileDialog));
	NVD_RETURN_IF_NULL(dialog);

	dialog->file_extensions = (char *) file_extensions;
	NSOpenPanel *dialog_raw = [NSOpenPanel openPanel];
	dialog_raw.title = @(title);
	dialog_raw.canChooseFiles = true;
	dialog_raw.canChooseDirectories = false;
	dialog_raw.allowsMultipleSelection = false;

	//ex: .c;.m;.cpp;
    if (file_extensions != NULL)
		dialog_raw.allowedFileTypes = [@(file_extensions) componentsSeparatedByString: @";"];

	dialog->raw = dialog_raw;

	return dialog;
}

NvdFileDialog *nvd_save_file_dialog_cocoa(const char *title, const char *default_filename)
{
	(void) default_filename;//TODO: This must be an option right?

	NvdFileDialog *dialog = calloc(1, sizeof(struct _NvdFileDialog));
	NVD_RETURN_IF_NULL(dialog);
	
	NSSavePanel* raw = [NSSavePanel savePanel];
	raw.title = @(title);

	dialog->raw = raw;
	return dialog;
}


void nvd_get_file_location_cocoa(NvdFileDialog *dlg, const char **out)
{
	NSSavePanel* raw = dlg->raw;
	[raw makeKeyAndOrderFront:nil];
	NSModalResponse resp = [raw runModal];

	dlg->location_was_chosen = resp == NSModalResponseContinue || resp == NSModalResponseOK;
	if (dlg->location_was_chosen)
		*out = strdup(raw.URL.absoluteString.UTF8String);

	[raw release];
}

void *nvd_open_file_dialog_get_raw_cocoa(NvdFileDialog *dlg)
{
	return dlg->raw;
}
