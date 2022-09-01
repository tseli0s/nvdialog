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

#ifndef __nvdialog_h__
#define __nvdialog_h__

#define NVDIALOG_VERSION_MAJOR 0
#define NVDIALOG_VERSION_MINOR 1
#define NVDIALOG_VERSION_PATCH 0

#include <stdint.h>

/**
 * @brief The core type for managing and identifying dialog boxes.
 * This struct should be returned from the library and not be shared across
 * multiple threads / uses.
 */
typedef struct _NvdDialogBox NvdDialogBox;

/**
 * @brief Defines what use it the dialog about.
 * Each member of this enum defines what the dialog should
 * represent:
 * - NVD_DIALOG_SIMPLE -> A simple message box, to say something.
 * - NVD_DIALOG_WARNING -> A warning message to be used for warnings.
 * - NVD_DIALOG_ERROR -> An error message box.
 * - NVD_DIALOG_QUESTION -> Currently unsupported.
 */
typedef enum {
        NVD_DIALOG_SIMPLE = 0xff,
        NVD_DIALOG_WARNING,
        NVD_DIALOG_ERROR,
        NVD_DIALOG_QUESTION,
} NvdDialogType;

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
 * @brief Returns the version of nvdialog currently linked with.
 * For a compile time alternative implementation see the
 * NVDIALOG_VERSION_MAJOR, NVDIALOG_VERSION_MINOR and NVDIALOG_VERSION_PATCH
 * constants.
 */
NvdVersion nvd_get_version();

/**
 * @brief Initializes the library.
 * This function is only required for compatibility with every platform. You
 * can safely ignore this function if you only target a specific platform.
 * @param program The argv[0] of your program.
 * @return 0 on success, else a negative error code indicating failure.
 */
uint32_t nvd_init(char *program);

/**
 * @brief Creates a new dialog object and returns it.
 * This function creates a simple dialog with the specified arguments,
 * and returns an opaque handle to it for use with @ref nvd_show_dialog().
 * @return The dialog handle on success, else NULL.
 */
NvdDialogBox *nvd_dialog_box_new(const char *title, const char *message,
                                 NvdDialogType type);
/**
 * @brief Shows a dialog to the system shell.
 * @param dialog The dialog to show.
 */
void nvd_show_dialog(NvdDialogBox *dialog);

#endif /* __nvdialog_h__ */