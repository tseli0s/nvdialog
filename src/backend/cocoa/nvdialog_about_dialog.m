#include "nvdialog.h"
#include "nvdialog_cocoa.h"

#include <AppKit/AppKit.h>

struct _NvdAboutDialog {
    const char *name, *description, *copyright_url;
    NSImage *image;
};

NvdAboutDialog *nvd_about_dialog_cocoa(const char *name,
                                       const char *desc,
                                       const char *imgpath)
{
    NvdAboutDialog *dlg = malloc(sizeof(struct _NvdAboutDialog));
    dlg->name = name;
    dlg->description = desc;
    dlg->copyright_url = NULL;
    dlg->image = [NSImage imageNamed: @(imgpath)];
    return dlg;
}

void nvd_about_dialog_set_licence_link_cocoa(NvdAboutDialog *dialog, const char *license_link, const char *txt)
{
    
}
