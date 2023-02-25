#include "nvdialog.h"
#include "nvdialog_cocoa.h"

#include <AppKit/AppKit.h>
#include <Foundation/Foundation.h>

NvdAboutDialog *nvd_about_dialog_cocoa(const char *name,
                                       const char *desc,
                                       const char *imgpath)
{
    NvdAboutDialog *dlg = malloc(sizeof(struct _NvdAboutDialog));

    dlg->options = [NSMutableDictionary dictionary];
    dlg->options[NSAboutPanelOptionApplicationName] = @(name);
    dlg->options[NSAboutPanelOptionVersion] = @(desc);

    if (imgpath != nil)
        dlg->options[NSAboutPanelOptionApplicationIcon] = [[NSImage alloc] initWithContentsOfFile: @(imgpath)];

    return dlg;
}

void nvd_about_dialog_set_licence_link_cocoa(NvdAboutDialog *dialog, const char *license_link, const char *txt)
{
    (void)txt;

    dialog->options[NSAboutPanelOptionCredits] = @(license_link);
}

void *nvd_about_dialog_get_raw_cocoa(NvdAboutDialog *dlg)
{
    return dlg;
}

void nvd_show_about_dialog_cocoa(NvdAboutDialog *dialog)
{
    [NSApp orderFrontStandardAboutPanelWithOptions: dialog->options];
    [dialog->options release];
}
