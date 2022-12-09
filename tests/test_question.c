#include <nvdialog/nvdialog.h>
#include <stdio.h>

int main(int argc, char **argv) {
        if (nvd_init(argv[0]) != 0) {
                puts("nvdialog: Failed to initialize backends.");
                return -1;
        }

        NvdQuestionBox* dlg = nvd_dialog_question_new("Testing",
                                                      "Cheese",
                                                      NVD_YES_NO_CANCEL);
        if (!dlg) {
                puts("nvdialog: NvdQuestionBox failed (Couldn't create dialog).");
                return -1;
        }

        #if defined (NVD_EXTRA_TESTING)
        nvd_show_dialog(dlg);
        #endif /* NVD_EXTRA_TESTING */
        nvd_free_object(dlg);

        puts("nvdialog: NvdQuestionBox succesfully tested.");
        return 0;
}