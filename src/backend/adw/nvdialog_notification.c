/*
 *  The MIT License (MIT)
 *
 *  Copyright (c) 2025 Aggelos Tselios
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

#include "nvdialog_notification.h"

#include "../../nvdialog_assert.h"
#include "nvdialog_adw.h"
#include "../gtk/nvdialog_gtk.h"
/* So we reduce compile-time dependencies. */
#if defined(NVD_PREINCLUDE_HEADERS)
#include <libnotify/notification.h>
#endif /* NVD_PREINCLUDE_HEADERS */
#include <dlfcn.h>
#include <stdlib.h>

#if !defined(NVD_PREINCLUDE_HEADERS)
typedef void *nvd_notification_t;
#else
typedef NotifyNotification nvd_notification_t;
#endif /* NVD_PREINCLUDE_HEADERS */

NvdNotification *nvd_notification_adw(const char *title, const char *msg,
                                      NvdNotifyType type) {
        return nvd_notification_gtk(title, msg, type);
}

void nvd_send_notification_adw(NvdNotification *notification) {
        nvd_send_notification_gtk(notification);
}

void nvd_add_notification_action_adw(NvdNotification *notification,
                                     const char *action, int value_to_set,
                                     int *value_to_return) {
        nvd_add_notification_action_gtk(notification, action, value_to_set, value_to_return);
}