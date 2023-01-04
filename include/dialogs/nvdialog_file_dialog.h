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

#include "nvdialog.h"

/** @brief A type to represent a file dialog (Saving / Opening). */
typedef struct _NvdFileDialog NvdFileDialog;

/**
 * @brief Creates an open file dialog.
 * This function creates a dialog to open a file in the filesystem
 * through a GUI.
 * @param title The window title to display.
 * @param file_extensions If looking for specific file extension, put it here.
 * Else pass NULL.
 * @note INCOMPLETE FUNCTION - Do not use please.
 * @returns The filename path on success, otherwise NULL.
 */
NVD_API NvdFileDialog *nvd_open_file_dialog_new(const char *title,
                                                const char *file_extensions);

/**
 * @brief Creates a file dialog that can be used to save a file
 * into the location chosen by the user.
 * @param title The title of the dialog, default is "Save file"
 * @param default_filename The default filename to use.
 * @return A handle to the dialog for future use.
 */
NVD_API NvdFileDialog *nvd_save_file_dialog_new(const char *title,
                                                const char *default_filename);
/**
 * @brief Returns a raw location on the filesystem from the dialog given.
 * @details This function will return the raw location of the dialog (eg. /home/someone/.local/share/)
 * given to the buffer passed.
 * @param dialog The file dialog to use for the operation.
 * @param savebuf A pointer to a buffer where the location will be saved.
 */
NVD_API void nvd_get_file_location(NvdFileDialog* dialog, const char** savebuf);

/**
 * @brief Returns the raw object behind the dialog.
 * @param dialog The dialog to retrieve the object from.
 * @return void* The raw toolkit-created object.
 */
NVD_API void *nvd_open_file_dialog_get_raw(NvdFileDialog *dialog);