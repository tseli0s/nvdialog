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

#include "../../nvdialog_assert.h"
#include "../../nvdialog_util.h"
#include "nvdialog_win32.h"
#include <stdbool.h>
#include <string.h>
#include <wchar.h>
#include <windows.h>
#include <winuser.h>

static const char* nvd_append_bytes(char* dest, const char* src) {
    size_t dest_len = strlen(dest);
    size_t src_len  = strlen(src);
    
    char* new_str = (char*)malloc(dest_len + src_len + 1);
    if (!new_str) {
        return NULL;
    }
    memcpy(new_str, dest, dest_len);
    memcpy(new_str + dest_len, src, src_len + 1);

    return new_str;
}

NvdFileDialog *nvd_open_file_dialog_win32(const char *title,
                                          const char *file_extensions) {
        NvdFileDialog *dialog = malloc(sizeof(struct _NvdFileDialog));
        NVD_RETURN_IF_NULL(dialog);

        dialog->is_save_dialog  = false;
        dialog->file_extensions = file_extensions;
        dialog->title           = title;

        return dialog;
}

/* TODO: Add default filename support. */
NvdFileDialog *nvd_save_file_dialog_win32(const char *title,
                                          const char *default_filename) {
        NvdFileDialog *dialog = calloc(1, sizeof(struct _NvdFileDialog));
        NVD_RETURN_IF_NULL(dialog);

        dialog->is_save_dialog  = true;
        dialog->file_extensions = NULL; /* Technically, we could add filters here, but how? */
        dialog->title           = title;
        return dialog;
}

void nvd_get_file_location_win32(NvdFileDialog *dialog,
                                 const char   **savebuf) {
        OPENFILENAME ofn;
        char         file[NVDIALOG_MAXBUF];
        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize    = sizeof(ofn);
        ofn.hwndOwner      = nvd_get_parent();
        ofn.lpstrFile      = file;
        ofn.lpstrFile[0]   = '\0';
        ofn.nMaxFile       = sizeof(file) - 1; /* NULL byte manually set */
        ofn.nFilterIndex   = 1;
        ofn.lpstrFileTitle = NULL;
        ofn.nMaxFileTitle  = 0;
        ofn.lpstrInitialDir = NULL;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

        if (dialog->file_extensions) {
                char** words = nvd_seperate_args(dialog->file_extensions);
                size_t i     = 0;
                const char buffer[NVDIALOG_MAXBUF];

                while (words[i] != NULL) {
                        const char tmp_buffer[128];
                        snprintf(buffer, sizeof(buffer), ".%s files (*.%s)", words[i], words[i]);
                        nvd_append_bytes(buffer, tmp_buffer);
                        i++;
                }

                ofn.lpstrFilter = buffer;
        } else ofn.lpstrFilter = NULL;

        file[NVDIALOG_MAXBUF - 1] = '\0';
        if (dialog->is_save_dialog) GetSaveFileName(&ofn);
        else                        GetOpenFileName(&ofn);

        dialog->filename = ofn.lpstrFile;
        dialog->location_was_chosen = true;
        *savebuf = dialog->filename;
}