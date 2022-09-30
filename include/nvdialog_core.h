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

#ifdef __nvdialog_core_h__
#error[ NVDIALOG ] Header file included twice, only include <nvdialog/nvdialog.h>
#endif /* __nvdialog_core_h__ */

#ifndef __nvdialog_core_h__
#define __nvdialog_core_h__ 1

#ifndef __nvdialog_h__
#error[ NVDIALOG ] Please only include <nvdialog.h> and no other headers.
#endif /* __nvdialog_h__ */

#include "nvdialog_types.h"

/** @brief An opaque representation of a window object. */
typedef void* NvdParentWindow;

/**
 * @brief Initializes the library.
 * This function is only required for compatibility with every platform. You
 * can safely ignore this function if you only target a specific platform.
 * @param program The argv[0] of your program.
 * @return 0 on success, else a negative error code indicating failure.
 */
int nvd_init(char *program);

/**
 * @brief Sets a custom domain name for your application.
 * @details This function sets a custom domain name for your application, to be
 * used with the 'libadwaita' backend
 * @param domain The domain name to set.
 * @note Thread-unsafe function.
 */
void nvd_set_domain_name(char *domain);

/**
 * @brief Creates a new context, that wraps around your application to
 * initialize a backend.
 * @details This function will create a new context and wrap around the
 * application calling this function. This is needed for the libadwaita backend,
 * since libadwaita requires an application to work properly.
 * @note This function has no effect if there is no libadwaita backend
 * available.
 * @sa nvd_set_domain_name
 * @return const NvdContext*
 */
NvdContext *nvd_bind_context(void);

/**
 * @brief Returns the current domain name of the NvDialog context.
 * @details This function returns the current domain name of the NvDialog
 * context. By default, it is set to 'io.androgr.nvdialog', and it can be
 * changed using @ref nvd_set_domain_name.
 * @return The domain name of NvDialog currently set (Defaults to
 * io.androgr.nvdialog)
 */
const char *nvd_get_domain_name(void);

/**
 * @brief Returns the argv[0] given to nvdialog.
 * @details This function returns the parameter passed to nvdialog during
 * nvd_init. It is mainly intended to be used internally.
 * @return The argv[0] given to nvdialog on success, otherwise NULL.
 */
const char *nvd_get_argv(void);

/**
 * @brief Sets a window as the parent of all dialogs created from NvDialog.
 * @details Using the parameter given, a window will be set as the parent of all dialogs
 * that are created from within the library.
 * @note This is a very dangerous function, and may not work as expected.
 * @param parent The window to set as the parent.
 * @return 0 on success, otherwise -1, call nvd_get_error() for more.
 */
int nvd_set_parent(NvdParentWindow parent);

/**
 * @brief Returns the window attached as the parent of all dialogs of NvDialog.
 * @return The currently set parent window, or NULL if no parent window is currently set.
 */
NvdParentWindow nvd_get_parent(void);

/**
 * @brief Unmarks the window set from @ref nvd_set_parent as the parent window.
 * @details This will reset the changes made by @ref nvd_set_parent, by unmarking the window
 * that is given as the parent from NvDialog.
 */
void nvd_delete_parent(void);

#endif /* __nvdialog_core_h__ */