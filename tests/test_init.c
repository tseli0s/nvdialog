#include <nvdialog.h>
#include <stdio.h>

int main(int argc, char **argv) {
        int retval = nvd_init();
        if (retval != 0) {
                puts("nvdialog: Failed to initialize backends.");
                return -1;
        }
        puts("nvdialog: Initialized NvDialog.");
        return 0;
}