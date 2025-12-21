#include <nvdialog.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
        int retval = nvd_init();
        if (retval != 0) {
                fprintf(stderr, "nvdialog: Failed to initialize backends.\n");
                abort();
        }
        puts("nvdialog: Initialized NvDialog.");
        return 0;
}
