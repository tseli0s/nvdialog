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

#include "../nvdialog_platform.h"

/**
 * @brief An opaque handle to a dialog box created from
 * @ref nvd_about_dialog_new.
 */
typedef struct _NvdAboutDialog NvdAboutDialog;

/**
 * @brief Shows an 'About application' dialog box.
 * @details This function displays a dialog box similar to 'About' menus in
 * other applications. It will display the application name, a brief description
 * of the application, the logo (If specified)
 * @param name Your application name.
 * @param description A short description of the application, describing what it
 * does.
 * @param logo Nullable value that can specify a filename to load as the
 * application logo.
 * @note This function does not use GtkAboutDialog on Unix.
 * @ingroup AboutDialog
 * @return NULL on failure, otherwise a handle to a heap allocated object containing
 * the actual dialog.
 */
NVD_API NvdAboutDialog *nvd_about_dialog_new(const char *name,
                                     const char *description,
                                     const char *logo);

/**
 * @brief Sets a hyperlink to the application's license (Preferably a link.)
 * @param dialog The dialog to set the hyperlink to.
 * @param license_link The link that points to your license.
 * @param txt A text string to set as the link's text. Can be NULL if the link
 * can be used as the text too.
 * @ingroup AboutDialog
 */
NVD_API void nvd_about_dialog_set_license_link(NvdAboutDialog *dialog,
                                       const char *license_link,
                                       const char* txt);

/**
 * @brief Adds a version text to the dialog given.
 * @param dialog The dialog to set the version to.
 * @param version A string to represent the version of your application.
 * @ingroup AboutDialog
 */
NVD_API void nvd_about_dialog_set_version(NvdAboutDialog *dialog, const char *version);

/**
 * @brief Shows the About dialog given to the user.
 * @param dialog The dialog to show.
 * @ingroup AboutDialog
 */
NVD_API void nvd_show_about_dialog(NvdAboutDialog *dialog);

/**
 * @brief Returns the raw object behind the dialog.
 * @param dialog The dialog to retrieve the object from.
 * @return void* The raw toolkit-created object.
 * @ingroup AboutDialog
 */
NVD_API void *nvd_about_dialog_get_raw(NvdAboutDialog *dialog);