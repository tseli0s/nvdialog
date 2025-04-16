#include <nvdialog.h>
#include <stdio.h>

int main() {
        if (nvd_init() != 0) {
                fprintf(stderr, "Couldn't initialize NvDialog.\n");
                return -1;
        }

        NvdNotification *notification =
                nvd_notification_new("Notification", "A simple notification",
                                     NVD_NOTIFICATION_SIMPLE);
        if (!notification) {
                fprintf(stderr, "Couldn't create notification: %s\n",
                        nvd_stringify_error(nvd_get_error()));
                return -1;
        }

        nvd_send_notification(notification);
        nvd_delete_notification(notification);
        printf("nvdialog: NvdNotification tested succesfully.\n");

        return 0;
}