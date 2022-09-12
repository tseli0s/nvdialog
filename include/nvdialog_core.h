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

#ifndef __nvdialog_core_h__
#define __nvdialog_core_h__ 1

#include "nvdialog_types.h"

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

#endif /* __nvdialog_core_h__ */