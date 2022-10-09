#include "dialogs/nvdialog_about_dialog.h"
#include "dialogs/nvdialog_dialog_box.h"
#include <nvdialog/nvdialog.h>
#include <nvdialog/nvdialog_dialog.h>
#define APP_NAME "NvDialog Example"
#define NULL ((void*)0)

int main(int argc, char **argv)
{
        const char *description = "This is an example brief description about"
                                  "your application. NvDialog Example"
                                  "is a simple example of capabilities NvDialog has."
                                  "See https://github.com/AndroGR/nvdialog"
                                  "for more information.";
        nvd_init(argv[0]);
        NvdAboutDialog* dialog = nvd_about_dialog_new(APP_NAME,
                             description, "This program is licensed under the MIT license,"
                             "see https://mitlicense.example for more.", NULL);
        if (!dialog) return -1;
        else {
                nvd_show_about_dialog(dialog);
                return 0;
        }
        return argc;
}