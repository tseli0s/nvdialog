/*
 *  The MIT License (MIT)
 *
 *  Copyright (c) 2024 Aggelos Tselios
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

#define NVD_APP_ID (32512)

#include "../../nvdialog_assert.h"
#include "nvdialog_win32.h"
#include <stdint.h>
#include <windows.h>

NvdNotification *nvd_notification_win32(const char   *title,
                                        const char   *msg,
                                        NvdNotifyType type) {
        NvdNotification *notification = malloc(sizeof(struct _NvdNotification));
        NVD_RETURN_IF_NULL(notification);

        notification->title      = (char*) title;
        notification->body       = (char*) msg;
        notification->destructor = NULL;
        notification->type       = type;
        notification->shown      = false;
        
        /* Heap allocating to save it inside notification->raw */
        NOTIFYICONDATA *nid = malloc(sizeof(NOTIFYICONDATA));;
        if (!nid) nvd_set_error(NVD_OUT_OF_MEMORY);
        NVD_CHECK_INTERNAL(nid, notification, NULL);

        uint32_t icon = 0x0;
        switch (notification->type) {
        case NVD_NOTIFICATION_SIMPLE:
                icon = NIIF_INFO;
                break;
        case NVD_NOTIFICATION_WARNING:
                icon = NIIF_WARNING;
                break;
        case NVD_NOTIFICATION_ERROR:
                icon = NIIF_ERROR;
                break;
        default:
                nvd_error_message("Invalid type (%d) for notification passed.", type);
                icon = NIIF_INFO; /* Fallback. */
                break;
        }

        nid->cbSize       = sizeof(NOTIFYICONDATA);
        nid->hWnd         = nvd_get_parent();
        nid->uID          = NVD_APP_ID;
        nid->uFlags       = NIF_INFO | NIF_ICON;
        nid->dwInfoFlags  = icon;
        nid->uTimeout     = 5000;

        snprintf(nid->szInfo, 256, "%s", msg);
        strcpy(nid->szInfoTitle, title);

        notification->raw = nid;
        return notification;
}

void nvd_send_notification_win32(NvdNotification *notification) {
    NVD_ASSERT(Shell_NotifyIcon(NIM_ADD, notification->raw) == TRUE);
}

/* 
 * This will require us to work with IToastNotification.
 * Leave it for someone who knows I guess.
 */
void nvd_add_notification_action_win32(NvdNotification* unused,
                                       const char* _unused,
                                       int __unused,
                                       int* ___unused) {
        (void) unused;
        (void) _unused;
        (void) __unused;
        (void) ___unused;
}
