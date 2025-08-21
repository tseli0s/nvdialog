#include <nvdialog/nvdialog.h>
#include <stdio.h>

int main(int argc, char const* argv[]) {
        (void)argc;

        nvd_init();

        NvdFileDialog* dialog =
                nvd_open_file_dialog_new("Open File", "png;ico;jpeg");
        NvdDynamicString* buffer = nvd_get_file_location(dialog);
        puts(NVD_CSTR(buffer));

        return 0;
}
