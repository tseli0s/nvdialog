#include <assert.h>
#include <nvdialog/nvdialog.h>
#include <stdint.h>
#include <stdlib.h>

int main(void) {
        assert(nvd_init() == 0);
        int width, height;
        NvdFileDialog *filedlg =
                nvd_open_file_dialog_new("Choose an image to use", NULL);
        const char *description =
                "This is an example dialog to show how to use images with "
                "NvdAboutDialog.";

        NvdDynamicString *path = nvd_get_file_location(filedlg);

        if (path) {
                const uint8_t *buffer =
                        nvd_image_from_filename(NVD_CSTR(path), &width, &height);
                NvdImage *image = nvd_create_image(buffer, width, height);
                assert(image != NULL);

                NvdAboutDialog *dialog =
                        nvd_about_dialog_new("Example", description, NULL);
                nvd_dialog_set_icon(dialog, image);
                nvd_show_about_dialog(dialog);
        } else {
                return EXIT_FAILURE;
        }
}