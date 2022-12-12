#include <nvdialog.h>
#include <stdio.h>
#if defined(__linux__) || defined(__gnu_linux__)
#include <pthread.h>
#endif /* __linux__ */

struct Args {
        int    argc;
        char **argv;
};

int return_code = -1;
static void create_dialog(struct Args arg) {
        nvd_init(arg.argv[0]);

        NvdDialogBox* dlg = nvd_dialog_box_new("Hello World!",
                                               "Hello World!",
                                                NVD_DIALOG_SIMPLE);
        if (!dlg) {
                printf("Failed to create dialog: %s\n", nvd_stringify_error(nvd_get_error()));
                return_code = -1;
        }
        
        nvd_free_object(dlg);
        return_code = 0;
}

int main(int argc, char **argv) {
        #if defined(__linux__) || defined(__gnu_linux__)
        pthread_t thread;
        struct Args arg = {
                .argc = argc,
                .argv = argv
        };
        int result = pthread_create(
                &thread,
                NULL,
                create_dialog,
                &arg
        );
        
        if (result != 0) {
                puts("nvdialog: Failed to create new thread.");
                return -1;
        }

        pthread_join(thread, NULL);
        if (return_code != 0) {
                puts("nvdialog: Child thread failed, stopping here.");
                return return_code;
        }

        puts("nvdialog: Multithreading succesfully tested.");
        
        #else
        puts("nvdialog: Multithreading support not available for this platform.");
        #endif /* __linux__ */

        return 0;
}