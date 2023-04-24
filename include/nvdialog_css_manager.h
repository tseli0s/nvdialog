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

#pragma once

#include "nvdialog.h"
#ifndef __nvdialog_css_manager_h__
#define __nvdialog_css_manager_h__ 1

#ifndef __nvdialog_h__
#error[ NVDIALOG ] Please only include <nvdialog.h> and no other headers.
#endif /* __nvdialog_h__ */

/**
 * @deprecated Styling support has been dropped from 0.7.0 onwards.
 * This is because it created large cross-platform problems for developers.
 */
typedef enum {
        NVD_GTK3_CSS_BACKEND = 0xdd, /* Gtk3 CSS Backend. */
        NVD_GTK4_CSS_BACKEND,        /* Gtk4 / libadwaita CSS Backend. */
        NVD_NO_CSS_BACKEND           /* No CSS backend available. */
} NvdCSSBackend;

/**
 * @deprecated First deprecated in v0.7.0, the CSS styling support
 * was dropped. If your application uses it, try limiting it before
 * v0.8.0 is released (Which is when all deprecated code will be removed).
 */
typedef struct _NvdCSSManager NvdCSSManager;

/**
 * @deprecated Styling support has been dropped, hence this function is invalid.
 */
NVD_API NvdCSSBackend nvd_get_css_backend(void);

/**
 * @deprecated CSS support has been deprecated. Avoid using deprecated code.
 */
NVD_API NvdCSSManager* nvd_css_manager_new(void);

/**
 * @deprecated Styling support has been deprecated from v0.7.0 onwards.
 */
NVD_API int nvd_css_manager_attach_string_stylesheet(NvdCSSManager *mgr, const char *str);

/**
 * @deprecated Styling support has been deprecated from v0.7.0 onwards.
 */
NVD_API int nvd_css_manager_attach_stylesheet(NvdCSSManager *mgr, const char *filename);

/**
 * @deprecated Styling support has been deprecated from v0.7.0 onwards.
 */
NVD_API int nvd_css_manager_use_style(NvdCSSManager *mgr, void *raw_handle);
#endif /* __nvdialog_css_manager_h__ */