#include "nvdialog.h"
#include "nvdialog_cocoa.h"

#include <AppKit/AppKit.h>
#include <stdbool.h>

#include "../../nvdialog_assert.h"

static NSSavePanel raw;
static NSOpenPanel raw_open;

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
	raw_open = dialog_raw; /* Bad workaround but should work for now. */

	return dialog;
}

NvdFileDialog *nvd_save_file_dialog_cocoa(const char *title, const char *default_filename)
{
	(void) default_filename;//TODO: This must be an option right?

	NvdFileDialog *dialog = calloc(1, sizeof(struct _NvdFileDialog));
	NVD_RETURN_IF_NULL(dialog);
	dialog->raw = [NSSavePanel savePanel];
	raw = dialog->raw;
	raw.title = @(title);
	return dialog;
}


void nvd_get_file_location_cocoa(NvdFileDialog *dlg, const char **out)
{
	[dlg->raw makeKeyAndOrderFront:nil];
	NSModalResponse resp = [dlg->raw runModal];

	dlg->location_was_chosen = resp == NSModalResponseContinue || resp == NSModalResponseOK;
	if (dlg->location_was_chosen)
		*out = strdup(raw_open.URL.absoluteString.UTF8String);

	[dlg->raw release];
}

void *nvd_open_file_dialog_get_raw_cocoa(NvdFileDialog *dlg)
{
	return dlg->raw;
}
