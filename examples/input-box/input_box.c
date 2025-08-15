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

        /* Creating the actual dialog. */
        NvdInputBox *input = nvd_input_box_new("Input here!", "Write a message, then a dialog will pop up with this message.");

        /* Showing it to the user... */
        nvd_show_input_box(input);
        /* And getting back what they entered in the prompt! */
        NvdDynamicString *msg = nvd_input_box_get_string(input);

        /* Now displaying the message to the user using an NvdDialogBox. The details won't be explained here, see examples/hello-world for more. */
        if (msg != NULL) {
                NvdDialogBox *dlg = nvd_dialog_box_new("Your message is...", NVD_CSTR(msg), NVD_DIALOG_SIMPLE);
                nvd_show_dialog(dlg);
                nvd_free_object(dlg);
        } else {
                NvdDialogBox *dlg = nvd_dialog_box_new("Error!", "Either you didn't enter a message or it wasn't received. If the latter, please report this bug upstream.", NVD_DIALOG_ERROR);
                nvd_show_dialog(dlg);
                nvd_free_object(dlg);
        }

        nvd_delete_string(msg); /* An NvdDynamicString is heap allocated, so you must free it after you're done with it. */
        nvd_free_object(input); /* Same goes for the NvdInputBox. */
        return 0;
}
