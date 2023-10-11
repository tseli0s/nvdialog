#include "nvdialog_cocoa.h"
#include <AppKit/AppKit.h>
#include <Foundation/Foundation.h>

NvdNotification *nvd_notification_cocoa(const char *title,
                                        const char *msg,
                                        NvdNotifyType type)
{
    NvdNotification *notif = malloc(sizeof(struct _NvdNotification));
    notif->type = type;
    notif->title = title;
    notif->body = msg;
    notif->destructor = NULL;
	return notif;
}

void nvd_send_notification_cocoa(NvdNotification *notification)
{
    int pid = [NSProcessInfo processInfo].processIdentifier;
    NSPipe *pipe = [NSPipe pipe];
    NSFileHandle *file = pipe.fileHandleForReading;

    NSTask *task = [[NSTask alloc] init];
    task.launchPath = @"/usr/bin/osascript";
    task.arguments = @[@"-e", [NSString stringWithFormat:   @"tell application \"System Events\" to display notification \"%s\" with title \"%s\" sound name \"default\"", 
                                                            notification->body, notification->title]];
    task.standardOutput = pipe;

    [task launch];
}

void nvd_add_notification_action_cocoa(NvdNotification* notification,
                                     const char* action,
                                     int  value_to_set,
                                     int* value_to_return) {
    (void) notification;
    (void) action;
    (void) value_to_set;
    (void) value_to_return;
}