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

#ifdef __nvdialog_types_h__
#error[ NVDIALOG ] Header file included twice, only include <nvdialog/nvdialog.h>
#endif /* __nvdialog_types_h__ */

#ifndef __nvdialog_types_h__
#define __nvdialog_types_h__ 1

/**
 * @brief Defines what use it the dialog about.
 * Each member of this enum defines what the dialog should
 * represent:
 * - NVD_DIALOG_SIMPLE -> A simple message box, to say something.
 * - NVD_DIALOG_WARNING -> A warning message to be used for warnings.
 * - NVD_DIALOG_ERROR -> An error message box.
 */
typedef enum {
        NVD_DIALOG_SIMPLE = 0xff,
        NVD_DIALOG_WARNING,
        NVD_DIALOG_ERROR,
} NvdDialogType;

/** @brief The enumerator containing most
   errors the library can handle. */
typedef enum {
        NVD_NO_ERROR = 0,
        NVD_NO_DISPLAY = 0xff,
        NVD_INVALID_PARAM,
        NVD_NOT_INITIALIZED,
        NVD_STRING_EMPTY,
        NVD_OUT_OF_MEMORY,
        NVD_INTERNAL_ERROR,
} NvdError;

/**
 * @brief Enumerator containing the possible arguments for
 * nvd_dialog_question_new().
 */
typedef enum {
        NVD_YES_NO = 0x04,
        NVD_YES_NO_CANCEL,
        NVD_YES_CANCEL,
} NvdQuestionButton;

/**
 * @brief This enum is returned as the reply of a question widget.
 * Usually you should use this instead of raw integers.
 */
typedef enum { NVD_REPLY_OK = 0x04, NVD_REPLY_CANCEL, NVD_REPLY_NO } NvdReply;

/**
 * @brief A struct that identifies a version of nvdialog.
 * This struct is returned by nvd_get_version().
 */
typedef struct {
        short major;
        short minor;
        short patch;
        char *string;
} NvdVersion;

/**
 * @brief Opaque type to hold information about the current process using
 * nvdialog.
 * @details This is an opaque structure intended to hold some information about
 * the current process that nvdialog is linked to
 */
__attribute__((deprecated("Contexts are no longer used within NvDialog. Please remove them from your code.")))
typedef struct _NvdContext NvdContext;

#endif /* __nvdialog_types_h__ */