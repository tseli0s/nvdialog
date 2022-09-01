/* Testing unit for libnvdialog. */

#include <assert.h>
#include <nvdialog.h>
#include <stddef.h>

int main(int argc, char **argv) {
        nvd_init(argv[0]);
        NvdDialogBox *dialog = nvd_dialog_box_new(
                "Testing",
                "Test message",
                NVD_DIALOG_SIMPLE
        );
        assert(dialog != NULL);
}
