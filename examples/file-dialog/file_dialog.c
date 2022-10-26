#include <stdio.h>
#include <errno.h>
#include <nvdialog/nvdialog.h>
#include <stdlib.h>

int main(int argc, char** argv) {
        /*
         * First, we initialize NvDialog. This is required especially
         * on Linux to avoid undefined behaviour.
         * Call this function before any other.
         */
        int result = nvd_init(argv[0]);
        if (result != 0) {
                /* Initialization failed, exit now. */
                puts("Error: Couldn't initialize NvDialog.");
                exit(EXIT_FAILURE);
        }

        /* Constructing the dialog. This is the most important part. */
        NvdFileDialog* dialog = nvd_open_file_dialog_new("Open File",
                                                         NULL);
        if (!dialog) {
                puts("Error: Could not construct the dialog.");
                return -ENOMEM;
        }

        /* Showing the dialog to the user, then saving the filename to the second parameter. */
        char* filename;
        nvd_get_file_location(dialog, &filename);
        
        /* Then, take the file path and print it to stdout. */
        puts(filename);

        /* Then finally, freeing the dialog. */
        nvd_free_object(dialog);

        return 0;
}