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

#ifdef __nvdialog_types_h__
#error[ NVDIALOG ] Header file included twice, only include <nvdialog/nvdialog.h>
#endif /* __nvdialog_types_h__ */

#ifndef __nvdialog_types_h__
#define __nvdialog_types_h__ 1

/**
 * @brief Defines what use it the dialog about.
 * Each member of this enum defines what the dialog should
 * represent:
 * - NVD_DIALOG_SIMPLE  -> A simple message box, to say something.
 * - NVD_DIALOG_WARNING -> A warning message to be used for warnings.
 * - NVD_DIALOG_ERROR   -> An error message box.
 */
typedef enum {
        NVD_DIALOG_SIMPLE = 0xff, /**< A simple dialog box, no decorations. */
        NVD_DIALOG_WARNING,       /**< A warning message to be used for warnings, with warning color styling. */
        NVD_DIALOG_ERROR,         /**< An error message box, with error styling. */
} NvdDialogType;

/** 
 * @brief The enumerator containing most
 * errors the library can handle.
 * @sa @ref nvd_stringify_error
 */
typedef enum {
        NVD_NO_ERROR   = 0,
        NVD_NO_DISPLAY = 0xff,
        NVD_BACKEND_FAILURE,
        NVD_INVALID_PARAM,
        NVD_NOT_INITIALIZED,
        NVD_BACKEND_INVALID,
        NVD_FILE_INACCESSIBLE,
        NVD_STRING_EMPTY,
        NVD_OUT_OF_MEMORY,
        NVD_INTERNAL_ERROR,
        NVD_ALREADY_INITIALIZED,
} NvdError;

/**
 * @brief Enumerator containing the possible arguments for
 * nvd_dialog_question_new().
 * @since v0.1.0
 * @sa nvd_dialog_question_new
 */
typedef enum {
        NVD_YES_NO = 0x04,
        NVD_YES_NO_CANCEL,
        NVD_YES_CANCEL,
} NvdQuestionButton;

/**
 * @brief Returned value by @ref nvd_get_reply .
 * @sa nvd_get_reply
 * @since v0.1.1
 */
typedef enum {
        NVD_REPLY_OK = 0x04, /**< User accepted the question. */
        NVD_REPLY_CANCEL,    /**< User cancelled the question. Also used as a fallback. */
        NVD_REPLY_NO         /**< User rejected the question. */
} NvdReply;

/**
 * @brief A struct that identifies the version of NvDialog.
 * @details This struct contains a series of fields that hold information about
 * NvDialog's version. The struct can be used at both compile-time and runtime
 * using respectively @ref NVD_VERSION and @ref nvd_get_version .
 * @sa nvd_get_version
 */
typedef struct {
        short major;  /**< Major version of NvDialog. */
        short minor;  /**< Minor version of NvDialog. */
        short patch;  /**< Patch version of NvDialog. */
        char *string; /**< String representation of the version for eg. printf() calls. */
} NvdVersion;

#endif /* __nvdialog_types_h__ */