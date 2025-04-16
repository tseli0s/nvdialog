#include <nvdialog.h>
#include <stdio.h>

int main() {
/* NvdAboutDialog currently broken on macOS. I will fix it before hitting v1.0,
 * hopefully. */
#if !defined(__APPLE__)
        if (nvd_init() != 0) {
                puts("nvdialog: Failed to initialize backends.");
                return -1;
        }

        NvdAboutDialog* dlg = nvd_about_dialog_new("Some App", "Testing", NULL);
        if (!dlg) {
                puts("nvdialog: Failed to create dialog.");
                return -1;
        }

        nvd_free_object(dlg);
        puts("nvdialog: NvdAboutDialog succesfully tested.");
#endif /* __APPLE__ */

        return 0;
}