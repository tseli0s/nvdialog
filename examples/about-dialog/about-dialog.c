#include <nvdialog/nvdialog.h>
#define APP_NAME "NvDialog Example"
#define NULL ((void*)0)

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
        const char *description = "This is an example brief description about"
                                  "your application. NvDialog Example"
                                  "is a simple example of capabilities NvDialog has."
                                  "See https://github.com/AndroGR/nvdialog"
                                  "for more information.";
        nvd_init(argv[0]);
        NvdAboutDialog* dialog = nvd_about_dialog_new(APP_NAME,
                             description, NULL);
        if (!dialog) {
                puts("Couldn't create the dialog object. Aborting.");
                abort();
        } else {
                nvd_about_dialog_set_version(dialog, "v0.1.0-testing");
                nvd_show_about_dialog(dialog);
                return 0;
        }
        return argc;
}