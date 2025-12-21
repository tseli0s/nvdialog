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

#include <shlobj.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <windows.h>
#include <winuser.h>

#include "../../nvdialog_assert.h"
#include "../../nvdialog_util.h"
#include "nvdialog_string.h"
#include "nvdialog_typeimpl.h"
#include "nvdialog_win32.h"
#include "winnt.h"
static NvdDynamicString *nvd_file_only_dialog_win32(NvdFileDialog *dialog) {
        OPENFILENAME ofn;
        char file[NVDIALOG_MAXBUF];
        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = nvd_get_parent();
        ofn.lpstrFile = file;
        ofn.lpstrFile[0] = '\0';
        ofn.nMaxFile = sizeof(file) - 1;
        ofn.nFilterIndex = 1;
        ofn.lpstrFileTitle = (char *)dialog->title;
        ofn.nMaxFileTitle = 0;
        ofn.lpstrInitialDir = NULL;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

        if (dialog->file_extensions) {
                char **words = nvd_seperate_args(dialog->file_extensions);
                size_t i = 0;
                char buffer[NVDIALOG_MAXBUF] = {0};

                while (words[i] != NULL) {
                        char tmp_buffer[128];
                        snprintf(tmp_buffer, sizeof(tmp_buffer), ".%s files (*.%s)", words[i], words[i]);
                        strncat(buffer, tmp_buffer, sizeof(buffer) - strlen(buffer) - 1);
                        strncat(buffer, "\0", sizeof(buffer) - strlen(buffer) - 1);
                        i++;
                }
                ofn.lpstrFilter = buffer;
        } else  ofn.lpstrFilter = NULL;

        file[NVDIALOG_MAXBUF - 1] = '\0';
        if (dialog->is_save_dialog) GetSaveFileName(&ofn);
        else GetOpenFileName(&ofn);

        dialog->filename = nvd_string_new(ofn.lpstrFile);
        dialog->location_was_chosen = true;
        return dialog->filename;
}

static NvdDynamicString *nvd_dir_dialog_win32(NvdFileDialog *dialog) {
        BROWSEINFO bi = {0};
        char path[MAX_PATH];

        bi.lpszTitle = dialog->title;
        bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
        bi.lParam = (LPARAM)dialog->filename;

        LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
        if (pidl != NULL) {
                if (SHGetPathFromIDList(pidl, path))
                        dialog->filename = nvd_string_new(path);
                CoTaskMemFree(pidl);
        }
        return dialog->filename;
}

NvdFileDialog *nvd_open_file_dialog_win32(const char *title,
                                          const char *file_extensions) {
        NvdFileDialog *dialog = nvd_malloc(sizeof(struct _NvdFileDialog));
        NVD_RETURN_IF_NULL(dialog);

        dialog->is_dir_dialog = false;
        dialog->is_save_dialog = false;
        dialog->raw = NULL;
        dialog->file_extensions = file_extensions;
        dialog->title = title;
        dialog->location_was_chosen = false;

        return dialog;
}

/* TODO: Add default filename support. */
NvdFileDialog *nvd_save_file_dialog_win32(const char *title,
                                          const char *default_filename) {
        NvdFileDialog *dialog = nvd_calloc(1, sizeof(struct _NvdFileDialog));
        NVD_RETURN_IF_NULL(dialog);

        dialog->is_save_dialog = true;
        dialog->is_dir_dialog = false;
        dialog->file_extensions =
                NULL; /* Technically, we could add filters here, but how? */
        dialog->title = title;
        dialog->location_was_chosen = false;
	dialog->raw = default_filename; /* To be used when constructing the dialog, since this field is otherwise useless */

        return dialog;
}

NvdFileDialog *nvd_open_folder_dialog_win32(const char *title,
                                            const char *default_path) {
        NvdFileDialog *dlg = nvd_calloc(1, sizeof(struct _NvdFileDialog));
        NVD_RETURN_IF_NULL(dlg);

        dlg->is_save_dialog = false;
        dlg->is_dir_dialog = true;
        dlg->filename = nvd_string_new(default_path);
        dlg->title = title;
        dlg->file_extensions = NULL;
        dlg->location_was_chosen = false;

        return dlg;
}

NvdDynamicString *nvd_get_file_location_win32(NvdFileDialog *dialog) {
        if (dialog->is_dir_dialog) return nvd_dir_dialog_win32(dialog);
        else return nvd_file_only_dialog_win32(dialog);
}
