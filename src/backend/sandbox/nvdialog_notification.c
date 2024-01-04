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

#include "../../nvdialog_assert.h"
#include "nvdialog_sbx.h"
#include "nvdialog_notification.h"
/* So we reduce compile-time dependencies. */
#if defined (NVD_PREINCLUDE_HEADERS)
#include <libnotify/notification.h>
#endif /* NVD_PREINCLUDE_HEADERS */
#include <dlfcn.h>
#include <stdlib.h>

#if !defined (NVD_PREINCLUDE_HEADERS)
typedef void*              nvd_notification_t;
#else
typedef NotifyNotification nvd_notification_t;
#endif /* NVD_PREINCLUDE_HEADERS */

typedef nvd_notification_t (*nvd_notify_new_t)(const char*,
                                                const char*,
                                                const char*);

struct NvdActionsArgs {
        int* ptr;
        int value;
};

static void nvd_set_action_ptr(void* notif, char* action, struct NvdActionsArgs *args) {
        (void) notif;
        (void) action;

        *(int*) args->ptr = (int) args->value;
}

static bool __nvd_check_libnotify(NvdNotification *notification) {
        bool (*nvd_notify_init)(char*) = dlsym(notification->lib, "notify_init");
        if (nvd_notify_init == NULL) {
                nvd_error_message("Can't load libnotify properly (Perhaps incompatible version?): %s", dlerror());
                dlclose(notification->lib);
                return false;
        }

        if (!nvd_notify_init((char*) nvd_get_application_name())) {
                nvd_error_message("Couldn't initialize libnotify, stopping here.");
                dlclose(notification->lib);
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

NvdNotification *nvd_notification_sbx(const char   *title,
                                      const char   *msg,
                                      NvdNotifyType type) {
        NvdNotification *notification = malloc(sizeof(struct _NvdNotification));
        NVD_RETURN_IF_NULL(notification);

        notification->lib = dlopen("/usr/lib/libnotify.so", RTLD_LAZY);
        if (!__nvd_check_libnotify(notification)) {
                nvd_set_error(NVD_BACKEND_INVALID);
                return NULL;
        }

        nvd_notify_new_t notify_new  = dlsym(notification->lib, "notify_notification_new");
        
        if (!notify_new) {
                nvd_error_message("libnotify is missing required symbols.");
                dlclose(notification->lib);
                free   (notification);

                return NULL;
        }

        const char *icon_name  = __nvd_match_notif_type(type);

        notification->title    = (char*) title;
        notification->body     = (char*) msg;
        notification->raw      = (void*) notify_new(notification->title,
                                                    notification->body,
                                                    icon_name);
        notification->type     = type;
        notification->shown    = false;
        
        if (notification->type == NVD_NOTIFICATION_ERROR) {
                const char *fn_name = "notify_notification_set_urgency";
                void (*nvd_notify_set_urgency)(nvd_notification_t, gint) = dlsym(notification->lib,
                                                                                   fn_name);
                nvd_notify_set_urgency(notification->raw, 2);
        }
        return notification;
}

void nvd_send_notification_sbx(NvdNotification *notification) {
        NVD_ASSERT(notification        != NULL );
        NVD_ASSERT(notification->shown == false); /* Just to avoid halting the thread. */

        bool (*show_fn)(nvd_notification_t, GError**) = dlsym(notification->lib,
                                                              "notify_notification_show");
        if (!show_fn) {
                nvd_error_message("libnotify is missing required symbols, see assertion message below.");
                NVD_ASSERT(show_fn != NULL);
        }
        
        show_fn(notification->raw, NULL);
}

void nvd_delete_notification_sbx(NvdNotification *notification) {
        NVD_ASSERT_FATAL(notification != NULL); /* Fatal to avoid some pretty scary bugs. */
        if (dlclose(notification->lib) < 0) {
                nvd_set_error(NVD_INTERNAL_ERROR);
                abort();
        }
        free(notification);
}

void nvd_add_notification_action_sbx(NvdNotification* notification,
                                     const char* action,
                                     int  value_to_set,
                                     int* value_to_return) {
        NVD_ASSERT_FATAL(notification != NULL);
        void (*fn) (void *notification,
                    const char *action,
                    const char *label,
                    void (*fn_callback)(void*, char*, gpointer),
                    gpointer user_data,
                    GFreeFunc free_func) = dlsym(notification->lib,
                                                 "notify_notification_add_action");
                
        struct NvdActionsArgs data = {
                value_to_return,
                value_to_set
        };
        
        fn(notification->raw, action, action, (void*) &nvd_set_action_ptr, (gpointer) &data, NULL);
}