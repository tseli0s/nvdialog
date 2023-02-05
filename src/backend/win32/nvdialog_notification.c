/*
 *  The MIT License (MIT)
 *
 *  Copyright (c) 2023 Aggelos Tselios
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
#include "nvdialog_win32.h"

struct _NvdNotification {
        char *title;
        char *contents;
        NvdNotifyType type;
        bool shown;
        void *raw;
        void *lib;
};

NvdNotification *nvd_notification_win32(const char   *title,
                                        const char   *msg,
                                        NvdNotifyType type) {
        NvdNotification *notification = malloc(sizeof(struct _NvdNotification));
        NVD_RETURN_IF_NULL(notification);

        notification->title    = (char*) title;
        notification->contents = (char*) msg;
        notification->type     = type;
        notification->shown    = false;

        return notification;
}

void nvd_send_notification_win32(NvdNotification *notification) {
        /* 
         * TODO: Implement function. Unfortunately I couldn't find any C-only
         * way to do this, because Microsoft likes to make my life harder.
         * I imagine we could have a small C++ implementation that we will
         * statically link with NvDialog?
         */
}

void nvd_add_notification_action_win32(NvdNotification* unused,
                                       const char* _unused,
                                       int __unused,
                                       int* ___unused) {
        (void) unused;
        (void) _unused;
        (void) __unused;
        (void) ___unused;
}
