#include <errno.h>
#include <nvdialog/nvdialog.h>
#include <stdio.h>
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
        const char* filters = ".img;.png;.jpeg;.ico;.svg";

        /* Constructing the dialog. This is the most important part. */
        NvdFileDialog* dialog = nvd_open_file_dialog_new("Open File", filters);
        /* We will also display a dialog for selecting a folder instead of a
         * dialog. */
        NvdFileDialog* dir_dialog =
                nvd_open_folder_dialog_new("Open folder...", NULL);

        if (!dialog || !dir_dialog) {
                puts("Error: Could not construct the dialog.");
                return -ENOMEM;
        }

        /*
         * This function either returns the filename or NULL
         * parameter points. As you can see below, NULL means no file was
         * selected (Although it could be an error to, in which case NvDialog
         * handled it)
         */
        NvdDynamicString *filename = nvd_get_file_location(dialog);
        NvdDynamicString *directory = nvd_get_file_location(dir_dialog);

        if (filename != NULL)
                /* We have to convert the NvdDynamicString into a normal C string to print it. */
                printf("Chosen file: %s\n", NVD_CSTR(filename));
        else
                printf("No file selected.\n");

        if (directory != NULL)
                printf("Chosen directory: %s\n", NVD_CSTR(directory));
        else
                printf("No directory selected.\n");

        /* Then finally, freeing the dialog. */
        nvd_free_object(dialog);
        nvd_free_object(dir_dialog);

        return 0;
}