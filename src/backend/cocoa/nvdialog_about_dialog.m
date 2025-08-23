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
#include "../nvdialog_assert.h"
#include <stdlib.h>
#include <AppKit/AppKit.h>
#include <Foundation/Foundation.h>
/*
 * This file is supposed to be the older implementation on the Cocoa backend.
 * However since it's mostly unmaintained this code won't compile, and I do
 * not know Objective-C so I don't know how to fix this. If you do, please
 * make a pull request, thank you.
 */

/*
struct _NvdAboutDialog {
    NSMutableDictionary<NSAboutPanelOptionKey, id> *options;
};
*/

NvdAboutDialog *nvd_about_dialog_cocoa(const char *name,
                                       const char *desc,
                                       const char *imgpath)
{
    /* GNUstep doesn't like this implementation, so let's ignore it. */
    #ifndef _NVD_USE_GNUSTEP
    NvdAboutDialog* dlg = malloc(sizeof(struct _NvdAboutDialog));
    NSMutableDictionary<NSAboutPanelOptionKey, id>* options;
    NVD_ASSERT(dlg != nil);

    options = [NSMutableDictionary dictionary];
    options[NSAboutPanelOptionApplicationName] = @(name);
    options[NSAboutPanelOptionVersion]         = @(desc);

    if (imgpath != nil)
        options[NSAboutPanelOptionApplicationIcon] = [[NSImage alloc] initWithContentsOfFile: @(imgpath)];
    
    dlg->raw = options;
    return dlg;
    #endif
}

void nvd_about_dialog_set_licence_link_cocoa(NvdAboutDialog *dialog, const char *license_link, const char *txt)
{
    #ifndef _NVD_USE_GNUSTEP
    (void)txt;
    NSMutableDictionary<NSAboutPanelOptionKey, id> *raw = dialog->raw;
    raw[NSAboutPanelOptionCredits] = @(license_link);
    dialog->raw = raw;
    #endif
}

void *nvd_about_dialog_get_raw_cocoa(NvdAboutDialog *dlg)
{
    return dlg->raw;
}

void nvd_show_about_dialog_cocoa(NvdAboutDialog *dialog)
{
    [NSApp orderFrontStandardAboutPanelWithOptions: dialog->raw];
    [dialog->raw release];
}
