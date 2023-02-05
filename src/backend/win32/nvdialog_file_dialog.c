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

#include "../../nvdialog_assert.h"
#include "nvdialog_win32.h"
#include <stdbool.h>
#include <wchar.h>
#include <windows.h>
#include <winuser.h>

struct _NvdFileDialog {
        char *filename, file_extensions;
        bool  location_was_chosen;
        bool  is_save_dialog;
};

NvdFileDialog *nvd_open_file_dialog_win32(const char *title,
                                          const char *file_extensions) {
        NvdFileDialog *dialog
            = (NvdFileDialog *)malloc(sizeof(struct _NvdFileDialog));
        NVD_RETURN_IF_NULL(dialog);

        dialog->is_save_dialog = false;
        return dialog;
}

NvdFileDialog *nvd_save_file_dialog_win32(const char *title,
                                          const char *default_filename) {
        NvdFileDialog *dialog = calloc(1, sizeof(struct _NvdFileDialog));
        NVD_RETURN_IF_NULL(dialog);

        dialog->is_save_dialog = true;
        return dialog;
}

void nvd_get_file_location_win32(NvdFileDialog *dialog,
                                 const char   **savebuf) {
        OPENFILENAME ofn;
        char         file[NVDIALOG_MAXBUF];
        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = nvd_get_parent();

        ofn.lpstrFile = file;
        ofn.lpstrFile[0] = '\0';
        ofn.nMaxFile = sizeof(file) - 1; /* NULL byte manually set */

        ofn.lpstrFilter = "";
        ofn.nFilterIndex = 1;
        ofn.lpstrFileTitle = NULL;

        ofn.nMaxFileTitle = 0;
        ofn.lpstrInitialDir = NULL;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

        file[NVDIALOG_MAXBUF - 1] = '\0';
        if (dialog->is_save_dialog) GetSaveFileName(&ofn);
        else GetOpenFileName(&ofn);

        dialog->filename = ofn.lpstrFile;
        dialog->location_was_chosen = true;
        *savebuf = dialog->filename;
}