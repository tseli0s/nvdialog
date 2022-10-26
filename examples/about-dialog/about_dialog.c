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
        NvdAboutDialog* dialog = nvd_about_dialog_new("NvDialog Example",
                                                      "A relatively small description "
                                                      "about your application, where it may mention "
                                                      "social links or other information.",
                                                      NULL);
        if (!dialog) {
                puts("Error: Could not construct the dialog.");
                return -ENOMEM;
        } else
                nvd_about_dialog_set_version(dialog, "v0.3.0");

        /* Then, showing the dialog to the user. */
        nvd_show_about_dialog(dialog);

        /* Then finally, freeing the dialog. */
        nvd_free_object(dialog);

        return 0;
}