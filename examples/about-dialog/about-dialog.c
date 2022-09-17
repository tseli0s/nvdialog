#include <nvdialog/nvdialog.h>
#include <nvdialog/nvdialog_dialog.h>
#define APP_NAME "NvDialog Example"
#define NULL ((void*)0)

int main(int argc, char **argv)
{
        const char *description = "This is an example brief description about your application. NvDialog Example\n"
                                  "is a simple example of capabilities NvDialog has. See https://github.com/AndroGR/nvdialog\n"
                                  "for more information.\n";
        nvd_init(argv[0]);
        nvd_about_dialog_new(APP_NAME,
                             description, "This program is licensed under the MIT license,"
                             "see https://mitlicense.example for more.", NULL);
        return argc;
}