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
#ifndef __nvdialog_capab_h__
#define __nvdialog_capab_h__ 1

#include <stdbool.h>
#include "nvdialog_platform.h"

/**
 * @brief Enumerator defining nvdialog optional capabilities. To be used with @ref nvd_get_capabilities
 * @since v0.2.0
 * @note In v0.10.1 the type name was added (using typedef).
 * @ingroup Capabilities
*/
typedef enum {
        /**
         * @brief Has nvdialog been configured to use the Adwaita backend by default?
         * @deprecated The Adwaita backend has been deprecated as of v0.10.0, any value returned by this is invalid.
         */
        NVD_ADW_BACKEND = 0x20,
        /** @brief Is nvdialog linked to the program statically or dynamically? */
        NVD_STATIC_LIB,
        /**
         * @brief Is nvdialog configured to be in compatibility mode?:
         * @warning This will always return false with @ref nvd_get_capabilities. Compatibility mode wasn't implemented properly and went unused.
        */
        NVD_COMPAT_MODE
} NvdCapability;

/**
 * @brief Returns the NvDialog's build time detected (optional) features.
 * @details This function returns the NvDialog's build time capabilities, such
 * as backends enabled, linkage method and others. It is a work in progress
 * since most of the library isn't modular.
 * @param query Which capabilities to query.
 * @return true if the requested query is supported, else false.
 * @since v0.2.0
 * @ingroup Capabilities
 */
NVD_API bool nvd_get_capabilities(int query);

#endif /* __nvdialog_capab_h__ */