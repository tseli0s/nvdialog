#include "nvdialog_cocoa.h"

#include <AppKit/AppKit.h>
#include <UserNotifications/UserNotifications.h>

struct _NvdNotification {
    NvdNotifyType type;
    bool responded, permitted;

    UNMutableNotificationContent *raw;
};

NvdNotification *nvd_notification_cocoa(const char *title,
                                        const char *msg,
                                        NvdNotifyType type)
{
    NvdNotification *notif = malloc(sizeof(struct _NvdNotification));
    notif->type = type;
    notif->permitted = notif->responded = false;

    [UNUserNotificationCenter.currentNotificationCenter requestAuthorizationWithOptions: UNNotificationPresentationOptionBadge | UNNotificationPresentationOptionList | UNNotificationPresentationOptionBanner | UNNotificationPresentationOptionSound
                                                                      completionHandler: ^(BOOL b, NSError *_Nullable err) {
                                                                          notif->permitted = b && err;
                                                                          notif->responded = true;
                                                                      }];

    notif->raw = [[UNMutableNotificationContent alloc] init];
    notif->raw.title = @(title);
    notif->raw.body = @(msg);

	return notif;
}

void nvd_send_notification_cocoa(NvdNotification *notification)
{
    while (!notification->responded);
    if (!notification->permitted) return;
    [UNUserNotificationCenter.currentNotificationCenter addNotificationRequest: [UNNotificationRequest requestWithIdentifier: NSBundle.mainBundle.bundleIdentifier
                                                                                                                     content: notification->raw 
                                                                                                                     trigger: nil] 
                                                         withCompletionHandler: ^(NSError * _Nullable _){(void)_;}];
    [notification->raw release];
}
