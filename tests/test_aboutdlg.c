#include <nvdialog.h>
#include <stdio.h>

int main(int argc, char **argv) {
        if (nvd_init(argv[0]) != 0) {
                puts("nvdialog: Failed to initialize backends.");
                return -1;
        }

        NvdAboutDialog* dlg = nvd_about_dialog_new("Some App",
                                                   "Testing",
                                                   NULL);
        if (!dlg) {
                puts("nvdialog: Failed to create dialog.");
                return -1;
        }

        nvd_free_object(dlg);
        puts("nvdialog: NvdDialogBox succesfully tested.");
        return 0;
}