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

#include "nvdialog.h"
#ifndef __nvdialog_css_manager_h__
#define __nvdialog_css_manager_h__ 1

#ifndef __nvdialog_h__
#error[ NVDIALOG ] Please only include <nvdialog.h> and no other headers.
#endif /* __nvdialog_h__ */

/**
 * @brief An enumerator to get the CSS provider for the CSS API
 * of NvDialog.
 * @details The CSS provider (Backend) is the service behind NvDialog's
 * CSS API implementation, almost always tied to the backend available.
 * In order to get the full customization capabilities, you can query
 * which CSS provider is being used by NvDialog, then write provider-specific
 * configuration to allow for customization.
 * @note The CSS backend is not available for the WinAPI.
 */
typedef enum {
        NVD_GTK3_CSS_BACKEND = 0xdd, /* Gtk3 CSS Backend. */
        NVD_GTK4_CSS_BACKEND,        /* Gtk4 / libadwaita CSS Backend. */
        NVD_NO_CSS_BACKEND           /* No CSS backend available. */
} NvdCSSBackend;

/**
 * @brief The CSS manager for NvDialog. 
 * @details The CSS manager is responsible for using a custom stylesheet
 * on dialogs, by attaching the stylesheet to the raw handle of the dialog.
 * @note The CSS manager is *NOT* thread-safe. Only use it from the main thread.
 */
typedef struct _NvdCSSManager NvdCSSManager;

/**
 * @brief Returns the @ref NvdCSSBackend.
 * @return The CSS backend used as an enumerator.
 */
NVD_API NvdCSSBackend nvd_get_css_backend(void);

/**
 * @brief Returns a new NvdCSSManager.
 * @details This function is used to instantiate a new NvdCSSManager into
 * your application, by returning a pointer to the new instance created by
 * this function.
 * @note You only need a single instance of the manager. All changes are program-wide,
 * and will be reflected in every dialog created.
 * @return An empty, initialized @ref NvdCSSManager.
 */
NVD_API NvdCSSManager* nvd_css_manager_new(void);

/**
 * @brief Attaches a CSS stylesheet from the 'str' parameter given below.
 * @param mgr The manager to attach the stylesheet to.
 * @param str A string representation of a stylesheet.
 * @note This creates a file and writes 'str' to it, then loads the file into
 * the CSS backend. As a result, it may cause your application to halt for a bit.
 * Prefer using a file instead.
 * @return 0 if succesful, otherwise -1 and sets the error code. See @ref nvd_get_error for details.
 */
NVD_API int nvd_css_manager_attach_string_stylesheet(NvdCSSManager *mgr, const char *str);

/**
 * @brief Attaches a CSS stylesheet from the specified filename.
 * @param mgr The manager to use.
 * @param filename The filename of the stylesheet file to parse and attach.
 * @return int 
 */
NVD_API int nvd_css_manager_attach_stylesheet(NvdCSSManager *mgr, const char *filename);

/**
 * @brief Uses the stylesheet attached to the manager for the dialog specified.
 * @param mgr The manager to use.
 * @param raw_handle Returned from an object-specific function as the backend object.
 * @return 0 on success, otherwise -1 and sets the error code. See @ref nvd_get_error.
 */
NVD_API int nvd_css_manager_use_style(NvdCSSManager *mgr, void *raw_handle);
#endif /* __nvdialog_css_manager_h__ */