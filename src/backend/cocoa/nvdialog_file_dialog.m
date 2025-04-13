/*
 *  The MIT License (MIT)
 *
 *  Copyright (c) 2025 the NvDialog contributors
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
	(void) default_filename;

	NvdFileDialog *dialog = calloc(1, sizeof(struct _NvdFileDialog));
	NVD_RETURN_IF_NULL(dialog);
	
	NSSavePanel* raw = [NSSavePanel savePanel];
	raw.title = @(title);

	dialog->raw = raw;
	return dialog;
}


void nvd_get_file_location_cocoa(NvdFileDialog *dlg, const char **out)
{
	if (dlg->is_dir_dialog) {
        NSOpenPanel *raw = dlg->raw;
        [raw makeKeyAndOrderFront:nil];

        NSModalResponse resp = [raw runModal];

        dlg->location_was_chosen = (resp == NSModalResponseOK || resp == NSModalResponseContinue);
        
        if (dlg->location_was_chosen) {
            NSURL *url = [raw URL];
            *out = strdup(url.absoluteString.UTF8String);
        }

        [raw release];
    } else {
        NSSavePanel* raw = dlg->raw;
        [raw makeKeyAndOrderFront:nil];
        NSModalResponse resp = [raw runModal];

        dlg->location_was_chosen = resp == NSModalResponseContinue || resp == NSModalResponseOK;
        if (dlg->location_was_chosen)
            *out = strdup(raw.URL.absoluteString.UTF8String);

        [raw release];
    }
}

void *nvd_open_file_dialog_get_raw_cocoa(NvdFileDialog *dlg)
{
	return dlg->raw;
}

NvdFileDialog *nvd_open_folder_dialog_cocoa(const char *title, const char *default_filename) {
	NvdFileDialog *dialog = calloc(1, sizeof(struct _NvdFileDialog));
    NVD_RETURN_IF_NULL(dialog);

    NSOpenPanel* dialog_raw = [NSOpenPanel openPanel];
    dialog_raw.title = @(title);
    dialog_raw.canChooseFiles = false;
    dialog_raw.canChooseDirectories = true;
    dialog_raw.allowsMultipleSelection = false;

    if (default_filename != NULL) {
        dialog_raw.directoryURL = [NSURL fileURLWithPath: @(default_filename)];
    }

    dialog->raw = dialog_raw;
    return dialog;
}