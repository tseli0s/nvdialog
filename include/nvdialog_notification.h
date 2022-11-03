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

#pragma once

#ifndef __nvdialog_notification_h__
#define __nvdialog_notification_h__ 1

#ifndef __nvdialog_h__
#error[ NVDIALOG ] Please only include <nvdialog.h> and no other headers.
#endif /* __nvdialog_h__ */

#include <libnotify/notify.h>

/**
 * @brief An enumerator to define the type of notification
 * that NvDialog will use.
 */
typedef enum {
       NVD_NOTIFICATION_SIMPLE,
       NVD_NOTIFICATION_WARNING,
       NVD_NOTIFICATION_ERROR
} NvdNotifyType;

/**
 * @brief A notification type that can be used to
 * send notifications to the system using NvDialog.
 * @since v0.5.0
 */
typedef struct _NvdNotification NvdNotification;

/**
 * @brief  Creates a new NvDialog-compatible notification.
 * @param  title The title of the notification, can be NULL if no title is desired.
 * @param  msg The message to show (Required, can't be NULL).
 * @param  type The type of the notification, see @ref NvdNotifyType.
 * @return An empty notification object.
 */
NvdNotification* nvd_notification_new(const char   *title,
                                      const char   *msg,
                                      NvdNotifyType type);

/**
 * @brief Sends the notification to the system.
 * @param notification The notification object to use.
 */
void nvd_send_notification(NvdNotification* notification);
#endif /**/