#include <nvdialog.h>
#include <stdio.h>

int main(int argc, char **argv) {
        if (nvd_init(argv[0]) != 0) {
                puts("nvdialog: Failed to initialize backends.");
                return -1;
        }

        NvdDialogBox* dlg = nvd_dialog_box_new("Testing",
                                               "Testing Dialog",
                                               NVD_DIALOG_WARNING);
        if (!dlg) {
                puts("nvdialog: NvdDialogBox failed (Couldn't create dialog).");
                return -1;
        }

        #if defined (NVD_EXTRA_TESTING)
        nvd_show_dialog(dlg);
        #endif /* NVD_EXTRA_TESTING */
        nvd_free_object(dlg);

        puts("nvdialog: NvdDialogBox succesfully tested.");
        return 0;
}