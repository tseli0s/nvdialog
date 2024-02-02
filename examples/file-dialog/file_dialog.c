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
        int result = nvd_init();
        if (result != 0) {
                /* Initialization failed, exit now. */
                puts("Error: Couldn't initialize NvDialog.");
                exit(EXIT_FAILURE);
        }

        /* The file extensions we can use with the dialog. */
        const char* filters = "img;png;jpeg;ico;svg";
        
        /* Constructing the dialog. This is the most important part. */
        NvdFileDialog* dialog = nvd_open_file_dialog_new("Open File",
                                                         filters);
        if (!dialog) {
                puts("Error: Could not construct the dialog.");
                return -ENOMEM;
        }

        /* Showing the dialog to the user, then saving the filename to the second parameter. */
        const char* filename;
        /* 
         * This function either returns the filename or NULL to where the second parameter points.
         * As you can see below, NULL means no file was selected (Although it could be an error to,
         * in which case NvDialog handled it)
         */
        nvd_get_file_location(dialog, &filename);

        if (filename != NULL) printf("Chosen file: %s\n", filename);
        else printf("No file selected.\n");

        /* Then finally, freeing the dialog. */
        nvd_free_object(dialog);

        return 0;
}