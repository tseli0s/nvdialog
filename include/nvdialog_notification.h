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

#pragma once

#include "nvdialog.h"
#ifndef __nvdialog_notification_h__
#define __nvdialog_notification_h__ 1

#ifndef __nvdialog_h__
#error[ NVDIALOG ] Please only include <nvdialog.h> and no other headers.
#endif /* __nvdialog_h__ */

/**
 * @brief Possible types of NvDialog notifications. Each field will create a slightly
 * different dialog matching the requested type.
 * @ingroup Notification
 * @since v0.5.0
 * @sa NvdNotification
 */
typedef enum {
       NVD_NOTIFICATION_SIMPLE, /**< A simple notification eg. to notify of something new in the app. */
       NVD_NOTIFICATION_WARNING, /**< A warning notification. */
       NVD_NOTIFICATION_ERROR /**< An error notification, preferably used before crashing. */
} NvdNotifyType;

/**
 * @brief The base notification type used by NvDialog.
 *
 * NvDialog offers since v0.5.0 support for basic notifications that
 * will be useful for many applications. The notification API is cross-platform
 * and should reduce the required setup to send a simple notification.
 * 
 * @ingroup Notification
 * @sa nvd_notification_new
 * @since v0.5.0
 */
typedef struct _NvdNotification NvdNotification;

/**
 * @brief  Creates a new notification object and returns it.
 * @param  title The title of the notification, can be NULL if no title is desired.
 * @param  msg The message to show (Required, can't be NULL).
 * @param  type The type of the notification, see @ref NvdNotifyType.
 * <b>Example:</b>
 * @code
   #include <nvdialog/nvdialog.h>
   int main(int argc, char** argv) {
       nvd_init(argv[0]);
       NvdNotification *notif = nvd_notification_new("Notification",
                                                     "A notification for your app.",
                                                     NVD_NOTIFICATION_SIMPLE);
       if (!notif) return -1;
       nvd_send_notification(notif);
       nvd_delete_notification(notif);
       return 0;
   }
 * @endcode
 * @ingroup Notification
 * @return An empty notification object.
 */
NVD_API NvdNotification* nvd_notification_new(const char   *title,
                                              const char   *msg,
                                              NvdNotifyType type);

/**
 * @brief Sends the notification to the system.
 * It's safe to assume that the same notification can be sent multiple times.
 * Just make sure the notification is still valid (Not freed yet).
 * 
 * @param notification The notification object to use.
 * @ingroup Notification
 * @since v0.5.0
 */
NVD_API void nvd_send_notification(NvdNotification* notification);

/**
 * @brief Deletes a notification object from NvDialog.
 * @note  You should only use this to free notifications. <b>Do not use @ref nvd_free_object please.</b>
 * @param notification The notification object to delete.
 * @ingroup Notification
 */
NVD_API void nvd_delete_notification(NvdNotification* notification);

/**
 * @brief Adds another button with a specified action to do when it is clicked.
 * @note Please make sure you don't register the same action twice on the same notification.
 * @param notification The notification to add the said action to.
 * @param action A string defining the action as well as the label of the button for the action.
 * @param value_to_set The value to set when the action is triggered.
 * @param value_to_return A pointer to an integer to save the value passed to @ref value_to_set .
 * @ingroup Notification
 */
NVD_API void nvd_add_notification_action(NvdNotification* notification,
                                         const char* action,
                                         int  value_to_set,
                                         int* value_to_return);
#endif /* __nvdialog_notification_h__ */