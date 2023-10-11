#include "nvdialog.h"
#include "nvdialog_cocoa.h"
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
    /*
    NvdAboutDialog *dlg = malloc(sizeof(struct _NvdAboutDialog));

    dlg->options = [NSMutableDictionary dictionary];
    dlg->options[NSAboutPanelOptionApplicationName] = @(name);
    dlg->options[NSAboutPanelOptionVersion] = @(desc);

    if (imgpath != nil)
        dlg->options[NSAboutPanelOptionApplicationIcon] = [[NSImage alloc] initWithContentsOfFile: @(imgpath)];

    return dlg;
    */
    return NULL; /* To avoid memory corruption while >> */
}

void nvd_about_dialog_set_licence_link_cocoa(NvdAboutDialog *dialog, const char *license_link, const char *txt)
{
    /*
    (void)txt;

    dialog->options[NSAboutPanelOptionCredits] = @(license_link);
    */
}

void *nvd_about_dialog_get_raw_cocoa(NvdAboutDialog *dlg)
{
    return dlg->raw;
}

void nvd_show_about_dialog_cocoa(NvdAboutDialog *dialog)
{
    /*
    [NSApp orderFrontStandardAboutPanelWithOptions: dialog->options];
    [dialog->options release];
    */
}
