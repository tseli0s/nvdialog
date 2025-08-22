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

#include "../nvdialog_platform.h"
#include "../nvdialog_string.h"

/**
 * @brief A simple input box that accepts text input from the user.
 * @details An `NvdInputBox` provides the user with a small prompt (commonly a dialog window similar)
 * to @ref NvdDialogBox that requests some text input from the user. When the input is submitted, the
 * library returns the submitted text. For convenience and compatibility reasons, the input is guaranteed
 * to be limited to a single line. 
 * @note Just like @ref NvdDialogBox and some other APIs, reusing an `NvdInputBox` is undefined behaviour, depending on the platform.
 * @sa @ref NvdDialogBox
 * @ingroup InputDialog
 * @since v0.10.0
 */

typedef struct _NvdInputBox NvdInputBox;

/**
 * @brief Constructs a new @ref NvdInputBox and returns it.
 * @param title The title of the input box, cannot be NULL
 * @param msg The message of the input box. If NULL, then a preconfigured string will be displayed.
 * @since v0.10.0
 * @warning By default on Windows the dialog will use a fallback theme, since NvDialog does not want to force a manifest to load
 * the proper theme as required by WinAPI. This may make controls look a bit outdated. To fix it, you must either supply your own .rc file
 * and change the theming manually, or embed, at your own risk of breaking other libraries, the .rc file directly into NvDialog. If you do the former,
 * do it before initializing the library. This does not apply on macOS and Linux.
 * @ingroup InputDialog
 * @returns A new @ref NvdInputBox on success, NULL otherwise.
*/
NVD_API NvdInputBox *nvd_input_box_new(const char *title, const char *msg);

/**
 * @brief Displays the @ref NvdInputBox given to the user.
 * @param box The input box to display. May not be NULL.
 * @note To retrieve the input of the user, use @ref nvd_input_box_get_string.
 * @since v0.10.0
 * @ingroup InputDialog
*/
NVD_API void nvd_show_input_box(NvdInputBox *box);

/**
 * @brief Retrieves the text entered by the user in an @ref NvdInputBox.
 * @param box The input box to get the string from. May not be NULL.
 * @returns A constant pointer to an @ref NvdDynamicString containing the user's input.
 * @note Invalid data may be given by the user. Make sure you check the string for validity.
 * @since v0.10.0
 * @ingroup InputDialog
 */
NVD_API NvdDynamicString *nvd_input_box_get_string(NvdInputBox *box);