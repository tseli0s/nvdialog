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
#include "dbus/dbus-protocol.h"
#include "dbus/dbus-shared.h"
#include "nvdialog_core.h"
#include "nvdialog_error.h"
#include "nvdialog_gtk.h"
#include <dlfcn.h>
#include <dbus/dbus.h>
#include <stdlib.h>
#include <sys/types.h>

typedef struct _NvdDBusNotifyData {
        DBusConnection *conn;
        DBusMessage *msg, *reply;
} NvdDBusNotifyData;

static char *nvd_match_notif_type(NvdNotifyType type) {
        static char *icon_name;

        switch (type) {
                case NVD_NOTIFICATION_SIMPLE:
                        icon_name = (char*) "dialog-information";
                        break;
                case NVD_NOTIFICATION_WARNING:
                        icon_name = (char*) "dialog-warning";
                        break;
                case NVD_NOTIFICATION_ERROR:
                        icon_name = (char*) "dialog-error";
                        break;
                default:
                        nvd_set_error(NVD_INVALID_PARAM);
                        return NULL;
        }

        return icon_name;
}

static void nvd_delete_notification_gtk(NvdNotification *notification) {
        NvdDBusNotifyData *data = notification->raw;
        if (data->reply) dbus_message_unref(data->reply);
        dbus_message_unref(data->msg);
        free(data);
}

NvdNotification *nvd_notification_gtk(const char *title, const char *msg,
                                      NvdNotifyType type) {
        const uint32_t timeout  = 5000; /* Timeout for the notification. */
        const uint32_t notif_id = 0;    /* Don't touch this */

        NvdNotification *notification = malloc(sizeof(struct _NvdNotification));
        NVD_RETURN_IF_NULL(notification);

        notification->lib = NULL;
        notification->shown = false;
        notification->title = (char*) title;
        notification->body = (char*) msg;
        notification->type = type;

        notification->destructor = nvd_delete_notification_gtk;
        notification->raw = malloc(sizeof(NvdDBusNotifyData));
        if (!notification->raw) {
                free(notification);
                return NULL;
        }

        NvdDBusNotifyData *priv = notification->raw;

        priv->conn = dbus_bus_get_private(DBUS_BUS_SESSION, NULL);
        priv->msg = dbus_message_new_method_call(
                "org.freedesktop.Notifications",
                "/org/freedesktop/Notifications",
                "org.freedesktop.Notifications",
                "Notify"
        );
        if (!priv->msg) {
                free(priv);
                free(notification);
                return NULL;
        }

        const char *appname  = (nvd_get_application_name() != NULL) ? nvd_get_application_name() : "NvDialog";
        const char *icon     = nvd_match_notif_type(type);

        DBusMessageIter params, actions_iter, hints_iter;
        dbus_message_iter_init_append(priv->msg, &params);

        dbus_message_iter_append_basic(&params, DBUS_TYPE_STRING, &appname);
        dbus_message_iter_append_basic(&params, DBUS_TYPE_UINT32, &notif_id);
        dbus_message_iter_append_basic(&params, DBUS_TYPE_STRING, &icon);
        dbus_message_iter_append_basic(&params, DBUS_TYPE_STRING, &title);
        dbus_message_iter_append_basic(&params, DBUS_TYPE_STRING, &msg);

        dbus_message_iter_open_container(&params, DBUS_TYPE_ARRAY, "s", &actions_iter);
        dbus_message_iter_close_container(&params, &actions_iter);

        dbus_message_iter_open_container(&params, DBUS_TYPE_ARRAY, "{sv}", &hints_iter);
        dbus_message_iter_close_container(&params, &hints_iter);

        dbus_message_iter_append_basic(&params, DBUS_TYPE_INT32, &timeout);

    return notification;
}

void nvd_send_notification_gtk(NvdNotification *notification) {
        NvdDBusNotifyData *data = notification->raw;
        data->reply = dbus_connection_send_with_reply_and_block(
                data->conn,
                data->msg,
                -1,
                NULL
        );
}

void nvd_add_notification_action_gtk(NvdNotification *notification,
                                     const char *action, int value_to_set,
                                     int *value_to_return) {
        nvd_error_message("nvd_add_notification_action_gtk: Deprecated, do not use.");
}