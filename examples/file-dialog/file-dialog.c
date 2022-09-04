#include <stddef.h>
#include <nvdialog.h>
#include <string.h>
#include <stdio.h>

#define MAX_BYTES  4096

int main(int argc, char **argv)
{
        nvd_init(argv[0]);
        const char* filename = nvd_open_file_dialog_new(
                "Open File Example",
                NULL
        );

        if (filename != NULL)
        {
                printf("%s", NULL);
                printf("%s", filename);
                nvd_dialog_box_new(
                        "File Selected",
                        filename,
                        NVD_DIALOG_SIMPLE
                );
        } else {
                nvd_dialog_box_new(
                        "Cancelled",
                        "No file selected.",
                        NVD_DIALOG_WARNING
                );
        }
}
