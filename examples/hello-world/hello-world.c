#include <nvdialog/nvdialog.h>

int main(int argc, char **argv)
{
        /* Initializing the library. */
        nvd_init(argv[0]);

        /* Creating the dialog. */
        NvdDialogBox* dialog = nvd_dialog_box_new(
                "Hello World!",
                "This is a dialog box using \nlibnvdialog. See https://github.com/AndroGR/nvdialog/"
                "\nfor more details."
                ,
                NVD_DIALOG_SIMPLE
        );
        /* If the dialog couldn't be created, exit. */
        if (!dialog) return -12;

        /* 
         * Otherwise show the created dialog. 
         * Recommendation: You can try running the dialog
         * to a seperate thread / process to avoid halting the process.
        */
        nvd_show_dialog(dialog);
        return argc - 1;
}
