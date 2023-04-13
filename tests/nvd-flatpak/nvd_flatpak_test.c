#include <nvdialog/nvdialog.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {
    (void) argc;

    nvd_init((char*)argv[0]);

    NvdFileDialog* dialog = nvd_open_file_dialog_new("Open File", "png;ico;jpeg");
    const char* buffer = NULL;

    nvd_get_file_location(dialog, &buffer);
    puts(buffer);
    
    return 0;
}
