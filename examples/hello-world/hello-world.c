#include <nvdialog.h>
#include <stdio.h>

int main(int argc, char **argv)
{
        /* Initializing the library. */
        nvd_init(argv[0]);

        /* Creating the dialog. */
        nvd_dialog_box_new(
                "Hello World!",
                "This is a dialog box using \nlibnvdialog. See https://github.com/AndroGR/nvdialog/"
                "\nfor more details."
                ,
                NVD_DIALOG_SIMPLE
        );
        
        return argc - 1;
}