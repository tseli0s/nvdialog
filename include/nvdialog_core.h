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
#ifdef __nvdialog_core_h__
#error[ NVDIALOG ] Header file included twice, only #include <nvdialog/nvdialog.h>
#endif /* __nvdialog_core_h__ */

#ifndef __nvdialog_core_h__
#define __nvdialog_core_h__ 1

#ifndef __nvdialog_h__
#error[ NVDIALOG ] Please only include <nvdialog.h> and no other headers.
#endif /* __nvdialog_h__ */

#include "nvdialog_types.h"

/** @brief An opaque representation of a window object. */
typedef void *NvdParentWindow;

/**
 * @brief Initializes NvDialog.
 * 
 * This function initializes NvDialog. It's the first function that should be called
 * when you create your program as without it, you cannot create any dialogs or use the
 * library at all.
 *
 * @note You should call this function to the same thread you're creating your dialogs from.
 * If you also happen to use a library used by NvDialog as the backend, make sure that the two libraries
 * stay in the same thread to avoid race conditions.
 * @since v0.1.0
 * @ingroup Core
 * @return 0 on success, else a negative error code indicating failure.
 */
NVD_API int nvd_init();

/**
 * @brief Sets the application name to use inside NvDialog.
 * @details This function sets the application name that NvDialog will use if an application name
 * is needed. By default, the application name is set to "NvDialog Application". The application name
 * is used in notifications, so it is important to set the actual application name.
 * @ingroup Core
 * @param application_name The application name to use.
 */
NVD_API void nvd_set_application_name(const char* application_name);

/**
 * @brief Returns the application name set inside NvDialog.
 * @return The application name.
 * @ingroup Core
 * @since v0.5.0
 */
NVD_API const char *nvd_get_application_name();

/**
 * @brief Returns the argv[0] given to nvdialog.
 * @details This function returns the parameter passed to nvdialog during
 * nvd_init. It is mainly intended to be used internally.
 * @deprecated This function is deprecated as of v0.8.1 and will only return NULL
 * @ingroup Core
 * @return The argv[0] given to nvdialog on success, otherwise NULL.
 */
NVD_API const char *nvd_get_argv(void);

/**
 * @brief Sets a window as the parent of all dialogs created from NvDialog.
 * @details Using the parameter given, a window will be set as the parent of all
 * dialogs that are created from within the library. The window has to match the
 * window type used by the backend.
 * @note This is a very dangerous function, and may not work as expected.
 * @ingroup Core
 * @param parent The window to set as the parent.
 * @return 0 on success, otherwise -1, call nvd_get_error() for more.
 */
NVD_API int nvd_set_parent(NvdParentWindow parent);

/**
 * @brief Returns the window attached as the parent of all dialogs of NvDialog.
 * @ingroup Core
 * @return The currently set parent window, or NULL if no parent window is
 * currently set.
 */
NVD_API NvdParentWindow nvd_get_parent(void);

/**
 * @brief Unmarks the window set from @ref nvd_set_parent as the parent window.
 * @ingroup Core
 *
 * This will reset the changes made by @ref nvd_set_parent, by
 * unmarking the window that is given as the parent from NvDialog.
 *
 */
NVD_API void nvd_delete_parent(void);

/**
 * @brief Deletes an object creates by NvDialog.
 * @details Call this function when you are no longer interested in using the
 * parameter passed anymore, to free up any resources occupied by the object.
 * Note that calling this in the middle of an operation will cause use after free.
 * @ingroup Core
 * @param object The object to be deleted.
 */
NVD_API void nvd_free_object(void *object);

#endif /* __nvdialog_core_h__ */