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

#ifndef __nvdialog_types_h__
#define __nvdialog_types_h__ 1

/**
 * @brief Defines what use it the dialog about.
 * Each member of this enum defines what the dialog should
 * represent:
 * - NVD_DIALOG_SIMPLE  -> A simple message box, to say something.
 * - NVD_DIALOG_WARNING -> A warning message to be used for warnings.
 * - NVD_DIALOG_ERROR   -> An error message box.
 * @since v0.1.0
 * @ingroup Dialog
 * @sa nvd_dialog_box_new
 */
typedef enum {
        NVD_DIALOG_SIMPLE = 0xff, /**< A simple dialog box, no decorations. */
        NVD_DIALOG_WARNING, /**< A warning message to be used for warnings, with
                               warning color styling. */
        NVD_DIALOG_ERROR,   /**< An error message box, with error styling. */
} NvdDialogType;

/**
 * @brief Enumerator containing the possible arguments for
 * nvd_dialog_question_new().
 * @details Each field describes the possible answers that will be included in a new @ref NvdQuestionDialog.
 * More specifically:
 * - NVD_YES_NO will have the dialog include only two buttons, yes and no (May differ per locale and system, but always affirmative and negative).
 * - NVD_YES_NO_CANCEL is the same but also includes a cancel button. Sometimes this is ignored depending on the system.
 * - NVD_YES_CANCEL is useful when you want to change the affirmative button's text but want to use cancel for the negative.
 * @since v0.1.0
 * @sa nvd_dialog_question_new
 */
typedef enum {
        NVD_YES_NO = 0x04,
        NVD_YES_NO_CANCEL,
        NVD_YES_CANCEL,
} NvdQuestionButton;

/**
 * @brief An enumerator containing a possible returned value by @ref nvd_get_reply, when used with an @ref NvdQuestionBox
 * @sa nvd_get_reply
 * @since v0.1.1
 */
typedef enum {
        NVD_REPLY_OK = 0x04, /**< User accepted the question. */
        NVD_REPLY_CANCEL,    /**< User cancelled the question. Also used as a
                                fallback. */
        NVD_REPLY_NO         /**< User rejected the question. */
} NvdReply;

/**
 * @brief A struct that identifies the version of NvDialog.
 * @details This struct contains a series of fields that hold information about
 * NvDialog's version (usually at runtime). It's usually filled by @ref nvd_get_version
 * @sa nvd_get_version
 * @ingroup Version
 */
typedef struct {
        short major;  /**< Major version of NvDialog. */
        short minor;  /**< Minor version of NvDialog. */
        short patch;  /**< Patch version of NvDialog. */
        char *string; /**< String representation of the version for eg. printf()
                         calls. */
} NvdVersion;

#endif /* __nvdialog_types_h__ */