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

#pragma once

#ifndef __nvdialog_init_h__
#define __nvdialog_init_h__ 1

#define NVD_TRY_CALL(f) \
    if ((f) != NULL) {   \
        (f)();           \
    } else {             \
        fprintf(stderr, "Error: Function pointer " #f " is NULL\n"); \
        return;           \
    }
#include "nvdialog.h"
#include "nvdialog_macros.h"


typedef struct _NvdBackendMask {
    NvdDialogBox *(*dialog_box)(const char *, const char *, NvdDialogType);
    void (*show_dialog)(NvdDialogBox *);

    NvdQuestionBox *(*question)(const char *, const char *, NvdQuestionButton);
    NvdReply (*get_reply)(NvdQuestionBox *);
    
    NvdAboutDialog *(*about_dialog)(const char *, const char *, const char *);
    void (*show_about_dialog)(NvdAboutDialog *);
    void (*about_dialog_set_version)(NvdAboutDialog *, const char *);
    void (*about_dialog_set_license)(NvdAboutDialog *, const char *, const char *);
    
    NvdFileDialog *(*open_file_dialog)(const char *, const char *);
    NvdFileDialog *(*save_file_dialog)(const char *, const char *);
    NvdFileDialog *(*open_folder_dialog)(const char *, const char *);
    void (*get_file_location)(NvdFileDialog *, char **);

    NvdNotification *(*notification)(const char *, const char *, NvdNotifyType);
    void (*send_notification)(NvdNotification *);
    void (*add_notification_action)(NvdNotification*, const char*, int, int*);
} NvdBackendMask;

NVD_INTERNAL_FUNCTION int nvd_init_gtk3(NvdBackendMask *mask);
NVD_INTERNAL_FUNCTION int nvd_init_win32(NvdBackendMask *mask);
NVD_INTERNAL_FUNCTION int nvd_init_gtk4(NvdBackendMask *mask);
NVD_INTERNAL_FUNCTION int nvd_init_cocoa(NvdBackendMask *mask);
NVD_INTERNAL_FUNCTION int nvd_init_backends(NvdBackendMask *mask);

#endif