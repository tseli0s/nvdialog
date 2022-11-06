/*
 *  The MIT License (MIT)
 *
 *  Copyright (c) 2022 Aggelos Tselios
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

#include "../../nvdialog_assert.h"
#include "nvdialog_gtk.h"
#include "nvdialog_notification.h"
#include <libnotify/notification.h>
#include <dlfcn.h>
#include <stdlib.h>

struct _NvdNotification {
        char *title;
        char *contents;
        NvdNotifyType type;
        bool shown;
        void *raw;
        void *lib;
};

typedef NotifyNotification* (*nvd_notify_new_t)(const char*,
                                                const char*,
                                                const char*);

static bool __nvd_check_libnotify(NvdNotification *notification) {
        gboolean (*nvd_notify_init)(char*) = dlsym(notification->lib, "notify_init");
                if (!nvd_notify_init) {
                        dlclose(notification->lib);
                        nvd_error_message("Can't load libnotify properly (Perhaps incompatible version?): %s", dlerror());
                        return false;
                }

                if (!nvd_notify_init("NvDialog")) {
                        dlclose(notification->lib);
                        nvd_error_message("Couldn't initialize libnotify, stopping here.");
                        return false;
        }
        return true;
}

static inline char *__nvd_match_notif_type(NvdNotifyType type) {
        static char *icon_name;
        
        switch (type) {
        case NVD_NOTIFICATION_SIMPLE:
                icon_name = "dialog-information";
                break;
        case NVD_NOTIFICATION_WARNING:
                icon_name = "dialog-warning";
                break;
        case NVD_NOTIFICATION_ERROR:
                icon_name = "dialog-error";
                break;
        default: return NULL;
        }

        return icon_name;
}

NvdNotification *nvd_notification_gtk(const char   *title,
                                      const char   *msg,
                                      NvdNotifyType type) {
        NvdNotification *notification = malloc(sizeof(struct _NvdNotification));
        NVD_RETURN_IF_NULL(notification);

        notification->lib                  = dlopen("/usr/lib/libnotify.so", RTLD_LAZY);
        if (!__nvd_check_libnotify(notification)) nvd_set_error(NVD_BACKEND_INVALID);

        nvd_notify_new_t notify_new  = dlsym(notification->lib, "notify_notification_new");
        
        if (!notify_new) {
                nvd_error_message("libnotify is missing required symbols.");
                dlclose(notification->lib);
                free   (notification);

                return NULL;
        }

        const char *icon_name  = __nvd_match_notif_type(type);

        notification->title    = (char*) title;
        notification->contents = (char*) msg;
        notification->raw      = (void*) notify_new(notification->title,
                                                    notification->contents,
                                                    icon_name);
        notification->type     = type;
        notification->shown    = false;
        
        if (notification->type == NVD_NOTIFICATION_ERROR) {
                const char *fn_name = "notify_notification_set_urgency";
                void (*nvd_notify_set_urgency)(NotifyNotification *, gint) = dlsym(notification->lib,
                                                                                   fn_name);
                nvd_notify_set_urgency(notification->raw,
                                       NOTIFY_URGENCY_CRITICAL);
        }
        return notification;
}

void nvd_send_notification_gtk(NvdNotification *notification) {
        NVD_ASSERT(notification        != NULL );
        NVD_ASSERT(notification->shown == false); /* Just to avoid halting the thread. */

        bool (*show_fn)(NotifyNotification*, GError**) = dlsym(notification->lib,
                                                              "notify_notification_show");
        if (!show_fn) {
                nvd_error_message("libnotify is missing required symbols, see assertion message below.");
                NVD_ASSERT(show_fn != NULL);
        }
        
        show_fn(notification->raw, NULL);
}

void nvd_delete_notification_gtk(NvdNotification *notification) {
        NVD_ASSERT_FATAL(notification != NULL); /* Fatal to avoid some pretty scary bugs. */
        dlclose(notification->lib);
        free(notification);
}