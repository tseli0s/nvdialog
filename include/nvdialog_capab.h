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
#ifdef __nvdialog_capab_h__
#error[ NVDIALOG ] Header file included twice, only include <nvdialog/nvdialog.h>
#endif /* __nvdialog_capab_h__ */

#pragma once
#ifndef __nvdialog_capab_h__
#define __nvdialog_capab_h__ 1

#include <stdbool.h>

#ifndef __nvdialog_h__
#error[ NVDIALOG ] Please only include <nvdialog.h> and no other headers.
#endif /* __nvdialog_h__ */

enum {
        /* Adwaita backend support */
        NVD_ADW_BACKEND = 0x20,
        /* Built as a static library */
        NVD_STATIC_LIB,
        /* Older version compatibility */
        NVD_COMPAT_MODE
};

/**
 * @brief Returns the NvDialog's build time detected capabilities.
 * @details This function returns the NvDialog's build time capabilities, such
 * as backends enabled, linkage method and others. It is a work in progress
 * since most of the library isn't modular.
 * @param query Which capabilities to query.
 * @return true if the requested @ref query is supported, else false.
 */
NVD_API bool nvd_get_capabilities(int query);

#endif /* __nvdialog_capab_h__ */