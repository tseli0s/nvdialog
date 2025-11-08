/*
 *  The MIT License (MIT)
 *
 *  Copyright (c) 2025 the NvDialog contributors
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
 
#include "nvdialog_cocoa.h"
#include <AppKit/AppKit.h>
#include <Foundation/Foundation.h>

NvdNotification *nvd_notification_cocoa(const char *title,
                                        const char *msg,
                                        NvdNotifyType type)
{
    NvdNotification *notif = nvd_malloc(sizeof(struct _NvdNotification));
    notif->type = type;
    notif->title = title;
    notif->body = msg;
    notif->destructor = NULL;
	return notif;
}

void nvd_send_notification_cocoa(NvdNotification *notification)
{
    #ifndef _NVD_USE_GNUSTEP
    int pid = [NSProcessInfo processInfo].processIdentifier;
    NSPipe *pipe = [NSPipe pipe];
    NSFileHandle *file = pipe.fileHandleForReading;

    NSTask *task = [[NSTask alloc] init];
    task.launchPath = @"/usr/bin/osascript";
    task.arguments = @[@"-e", [NSString stringWithFormat:   @"tell application \"System Events\" to display notification \"%s\" with title \"%s\" sound name \"default\"", 
                                                            notification->body, notification->title]];
    task.standardOutput = pipe;

    [task launch];
    #endif
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