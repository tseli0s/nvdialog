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

#include "gtk/gtkcssprovider.h"
#include "nvdialog.h"
#include "nvdialog_gtk.h"
#include "../../nvdialog_assert.h"
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

NvdCSSManager *nvd_css_manager_gtk() {
        return NULL;
}

int nvd_css_manager_attach_string_stylesheet_gtk(NvdCSSManager *mgr,
                                                 const char    *str) {
        return -1;
}

int nvd_css_manager_attach_stylesheet_gtk(NvdCSSManager *mgr, const char *filename) {
        return -1;
}

NVD_FORCE_INLINE int nvd_css_manager_use_style_gtk(NvdCSSManager *mgr, void *raw_handle) {
        return -1;
}