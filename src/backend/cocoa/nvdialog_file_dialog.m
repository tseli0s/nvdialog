#include "nvdialog.h"
#include "nvdialog_cocoa.h"

#include <AppKit/AppKit.h>
#include <stdbool.h>

#include "../../nvdialog_assert.h"

struct _NvdFileDialog {
	char *filename, *file_extensions;
	bool  location_was_chosen;

	//NSOpenPanel inherits from NSSavePanel
	NSSavePanel *raw;
};

NvdFileDialog *nvd_open_file_dialog_cocoa(const char *title, const char *file_extensions)
{
	NvdFileDialog *dialog = malloc(sizeof(struct _NvdFileDialog));
	NVD_RETURN_IF_NULL(dialog);

	dialog->file_extensions = (char *)file_extensions;
	NSOpenPanel *dialog_raw = [NSOpenPanel openPanel];
	dialog_raw.title = [NSString stringWithCString: title];
	dialog_raw.canChooseFiles = true;
	dialog_raw.canChooseDirectories = false;
	dialog_raw.allowsMultipleSelection = false;

	//ex: .c;.m;.cpp;
	dialog_raw.allowedFileTypes = [[NSString stringWithCString: file_extensions] 
						 componentsSeparatedByString: [NSString stringWithCString: ";"]];

	dialog->raw = dialog_raw;

	return dialog;
}

NvdFileDialog *nvd_save_file_dialog_cocoa(const char *title, const char *default_filename)
{
	(void)default_filename; //TODO: This must be an option right?

	NvdFileDialog *dialog = calloc(1, sizeof(struct _NvdFileDialog));
	NVD_RETURN_IF_NULL(dialog);
	NSSavePanel *dialog_raw = [NSSavePanel savePanel];
	dialog_raw.title = [NSString stringWithCString: title];

	dialog->raw = dialog_raw;
	return dialog;
}


void nvd_get_file_location_cocoa(NvdFileDialog *dlg, const char **out)
{
	NSSavePanel *rawdlg = dlg->raw;
	[rawdlg makeKeyAndOrderFront: nil];
	NSModalResponse resp = [rawdlg runModal];

	switch (resp) {
		case NSModalResponseContinue:
		case NSModalResponseOK:
			*out = strdup(rawdlg.URL.absoluteString.UTF8String);
			dlg->location_was_chosen = true;
			break;

		default: 
			dlg->location_was_chosen = false;
			break;
	}


	[dlg->raw release];
	return;
}
