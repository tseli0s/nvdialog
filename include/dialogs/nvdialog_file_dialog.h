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
 * @brief An opaque file dialog type, representing either a file
 * dialog that can be used to open a file or save a file.
 * @since v0.1.0
 * @ingroup FileDialog
 */
typedef struct _NvdFileDialog NvdFileDialog;

/**
 * @brief Creates a new, empty @ref NvdFileDialog to be used for
 * retrieving a file and returns it.
 *
 * This creates a new file dialog and returns it. In order to use it, you must call
 * @ref nvd_get_file_location and pass a pointer to write the file location to.
 * @note This function creates problems with the Adwaita backend. Those problems should be
 * fixed by the time v0.6.0 is officially released.
 *
 * @param title A string to put as the dialog title.
 * @param file_extensions Unused legacy parameter, just pass NULL in here.
 * @returns An empty @ref NvdFileDialog object if successful, otherwise NULL and an error retrievable
 * through @ref nvd_get_error is set.
 * @ingroup FileDialog
 */
NVD_API NvdFileDialog *nvd_open_file_dialog_new(const char *title,
                                                const char *file_extensions);

/**
 * @brief Creates a new, empty @ref NvdFileDialog object that will be used to save a
 * file in the selected (from the user) location.
 * @param title The title of the dialog, default is "Save file"
 * @param default_filename The default filename to use for saving.
 * @return An @ref NvdFileDialog on success, otherwise NULL and @ref nvd_get_error should
 * be called to get the failure reason.
 * @ingroup FileDialog
 */
NVD_API NvdFileDialog *nvd_save_file_dialog_new(const char *title,
                                                const char *default_filename);
/**
 * @brief Returns the filesystem path chosen through the @ref NvdFileDialog passed.
 *
 * This function will return the path on the filesystem from the dialog chosen, that you can
 * then use to either open or save the file given. It works with both save and open file dialog
 * types.
 *
 * @sa nvd_open_file_dialog_new
 * @param dialog The file dialog to take the filename from.
 * @param savebuf A pointer to a buffer where the path will be written, must not be NULL.
 * @ingroup FileDialog
 */
NVD_API void nvd_get_file_location(NvdFileDialog* dialog, const char** savebuf);

/**
 * @brief Returns the raw object behind the dialog.
 * @param dialog The dialog to retrieve the object from.
 * @return void* The raw toolkit-created object.
 * @ingroup FileDialog
 */
NVD_API void *nvd_open_file_dialog_get_raw(NvdFileDialog *dialog);