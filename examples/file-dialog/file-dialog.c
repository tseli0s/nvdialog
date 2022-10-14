#include <stddef.h>
#include <nvdialog.h>
#include <string.h>
#include <stdio.h>

#define MAX_BYTES  4096

int main(int argc, char **argv)
{
        nvd_init(argv[0]);
        void* dialog = nvd_open_file_dialog_new(
                "Open File Example",
                NULL
        );

        const char* filename;
        nvd_get_file_location(dialog, &filename);
        NvdDialogBox* chosen_file = nvd_dialog_box_new("File chosen",
        filename,
                NVD_DIALOG_SIMPLE);
}
