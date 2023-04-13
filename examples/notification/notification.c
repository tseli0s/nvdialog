#include <nvdialog/nvdialog.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {
    if (nvd_init(argv[0]) != 0) {
        printf("NvDialog couldn't initialize: %s", nvd_stringify_error(nvd_get_error()));
        exit(EXIT_FAILURE);
    }

    NvdNotification* notif = nvd_notification_new(
        "Notification title!",
        "Set your notification text here.",
        NVD_NOTIFICATION_SIMPLE
    );

    int pressed_button = 0;
    nvd_add_notification_action(notif, "I like NvDialog :)", 1, &pressed_button);
    nvd_send_notification(notif);
    
    return 0;
}