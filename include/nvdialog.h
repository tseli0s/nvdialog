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

#ifndef __nvdialog_h__
#define __nvdialog_h__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @mainpage
 * <b>Documentation</b>
 *
 * This manual documents the NvDialog library, a dialog box library written in C
 * that uses the system API to display its dialogs, making it minimal, dependency-free, portable and easy to use.
 * Instructions on how to build the library can be found in @ref building "this page". There are also multiple examples
 * to get you started - You can probably copy them in your source and continue with your project.
 *
 * NvDialog is verified to work on Windows (XP through 11), macOS (Catalina), Debian (10-13), Arch Linux and FreeBSD. Most other
 * Unix-like OSes also work, as long as Gtk3 is installed on the system.
 *
 * To get started, you should read about @ref NvdDialogBox, which is a simple
 * dialog box with no special functionality in it apart from the very basics. NvDialog also provides the following (among many many others)
 * features as part of its API:
 * - @ref NvdAboutDialog
 * - @ref NvdQuestionBox
 * - @ref NvdFileDialog
 *
 * # Examples
 * If you want to check out some code before using this library in your
 * project, this is a simple example: (Taken directly from the [GitHub
 * README](https://github.com/tseli0s/nvdialog)).
 * @code
 * #include <nvdialog/nvdialog.h>
 * int main(int argc, char** argv) {
 *      nvd_init();
 *      NvdDialogBox *dialog = nvd_dialog_box_new("Dialog Title", "Dialog
 * Message", NVD_DIALOG_SIMPLE); if (!dialog) return -1;
 *
 *      nvd_show_dialog(dialog);
 *      nvd_free_object(dialog);
 *
 *      return 0;
 * }
 * @endcode
 * # Other Resources
 * - [GitHub URL](https://github.com/tseli0s/nvdialog.git)
 * - [Homepage](https://tseli0s.github.io/nv.dialog)
 * - [Bug Tracker](https://github.com/tseli0s/nvdialog/issues)
 * - [Releases](https://github.com/tseli0s/nvdialog/releases)
 */

/** Major version of NvDialog at compile time. */
#define NVDIALOG_VERSION_MAJOR 0
/** Minor version of NvDialog at compile time. */
#define NVDIALOG_VERSION_MINOR 10
/** Patch version of NvDialog at compile time. */
#define NVDIALOG_VERSION_PATCH 0

/** @brief A macro to set the version at compile time. */
#define NVD_VERSION(x)                                         \
        {                                                      \
                (NvdVersion) x.major = NVDIALOG_VERSION_MAJOR; \
                (NvdVersion) x.minor = NVDIALOG_VERSION_MINOR; \
                (NvdVersion) x.patch = NVDIALOG_VERSION_PATCH; \
        }

#if !defined(_WIN32) || !defined(WIN32)
/**
 * @brief A macro to create thread-local static variables, primarily intended
 * for usage within NvDialog.
 * @note This requires C11 and newer to work, due to the `_Thread_local` macro.
 * @since v0.7.0
 */
#define NVD_THREAD_LOCAL(var) static _Thread_local var
#else
#define NVD_THREAD_LOCAL(var) var
#endif /* _WIN32 */

#include "nvdialog_platform.h"
#include "nvdialog_capab.h"
#include "nvdialog_core.h"
#include "nvdialog_dialog.h"
#include "nvdialog_error.h"
#include "nvdialog_image.h"
#include "nvdialog_notification.h"
#include "nvdialog_types.h"

/**
 * @brief Returns the version of nvdialog currently linked with.
 * @details For a compile time alternative implementation see the
 * NVDIALOG_VERSION_MAJOR, NVDIALOG_VERSION_MINOR and NVDIALOG_VERSION_PATCH
 * constants.
 * @returns The version of NvDialog linked with at runtime, as a struct.
 * @since v0.2.0
 * @ingroup Version
 */
NvdVersion nvd_get_version();

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __nvdialog_h__ */