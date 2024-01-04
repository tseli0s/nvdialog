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

#include "nvdialog.h"
#include "nvdialog_error.h"

static const bool nvd_has_adw_gtk =
#if defined(NVD_USE_GTK4)
    true;
#else
    false;
#endif

static const bool nvd_built_static =
#if !defined(NVD_STATIC_LINKAGE)
    true;
#else
    false;
#endif

static const bool nvd_compat_mode = false;

bool nvd_get_capabilities(int query) {
        switch (query) {
        case NVD_ADW_BACKEND:
                return nvd_has_adw_gtk;
        case NVD_STATIC_LIB:
                return nvd_built_static;
        case NVD_COMPAT_MODE:
                return nvd_compat_mode;
        default: 
            nvd_set_error(NVD_INVALID_PARAM);
            return false;
        }
        return false; /* Just to silence compiler warnings */
}