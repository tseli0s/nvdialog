#include <nvdialog.h>
#include <stdio.h>

int main(int argc, char **argv)
{
        /* Initializing the library. */
        nvd_init(argv[0]);

        /* Creating the dialog. */
        nvd_dialog_box_new(
                "Hello, world!",
                "Hello world ! This is a dialog box created using libnvdialog!",
                NVD_DIALOG_SIMPLE
        );
        
        return argc - 1;
}