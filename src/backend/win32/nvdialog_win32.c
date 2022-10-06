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

#include "nvdialog_win32.h"
#include <wchar.h>
#include <windows.h>
#include <winuser.h>

/* The largest filename allowed by the library. Perhaps we should extend this?
 */
#ifndef NVD_MAX_FILENAME_LEN
#define NVD_MAX_FILENAME_LEN 4096
#endif /* NVD_MAX_FILENAME_LEN */

const char *nvd_open_file_dialog_win32(const char *title, const char *message) {
        OPENFILENAME ofn;
        char file[NVD_MAX_FILENAME_LEN + 1];
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

        file[NVD_MAX_FILENAME_LEN] = '\0';
        GetOpenFileName(&ofn);

        char *ptr = ofn.lpstrFile;
        return ptr;
}

uint32_t nvd_create_win32_dialog(const char *title, const char *message,
                                 NvdDialogType type) {
        uint32_t flag;
        switch (type) {
        case NVD_DIALOG_SIMPLE:
                flag = MB_ICONINFORMATION;
                break;
        case NVD_DIALOG_WARNING:
                flag = MB_ICONWARNING;
                break;
        case NVD_DIALOG_ERROR:
                flag = MB_ICONHAND;
                break;
        default:
                abort();
        }
        return MessageBox(nvd_get_parent(), message, title, MB_OK | flag);
}

/*
 * TODO: This function is not as good as its Gtk (Linux) implementation.
 * In order to provide a consistent interface, we should rewrite it to look
 * better and be more customizable.
 */
void *nvd_about_dialog_win32(const char *name, const char *description,
                             const char *license_text, const char *logo_path) {
        char fmt[NVDIALOG_MAXBUF];
        char description_fmt[NVDIALOG_MAXBUF * 2];
        sprintf(description_fmt, "%s\n\n%s", description, license_text);
        sprintf(fmt, "About %s", name);
        MessageBoxEx(nvd_get_parent(), description_fmt, fmt,
                     MB_ICONINFORMATION | MB_OK | MB_RIGHT | MB_SYSTEMMODAL, 0);
        return (void *)1; /* TODO: Create an NvdDialogBox and return it */
}

NvdReply nvd_dialog_question_win32(const char *title, const char *question,
                                   NvdQuestionButton button) {
        int flag, reply;
        switch (button) {
        case NVD_YES_NO:
        case NVD_YES_CANCEL:
                flag = MB_YESNO;
                break;
        case NVD_YES_NO_CANCEL:
                flag = MB_YESNOCANCEL;
                break;
        default:
                nvd_set_error(NVD_INVALID_PARAM);
                return -1;
        }

        reply = MessageBox(nvd_get_parent(), question, title, (unsigned int) flag | MB_ICONQUESTION);
        switch (reply) {
        case IDYES:
                return NVD_REPLY_OK;
        case IDNO:
                return NVD_REPLY_NO;
        case IDCANCEL:
                return NVD_REPLY_CANCEL;
        }
        return -1; /* Just so GCC doesn't complain */
}