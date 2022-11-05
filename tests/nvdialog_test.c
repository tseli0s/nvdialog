/*
 *  The MIT License (MIT)
 *
 *  Copyright (c) 2022 Aggelos Tselios. This file is part of NvDialog.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <nvdialog.h>

int main(int argc, char** argv) {
        if (nvd_init(argv[0]) != 0) {
                printf("nvd_init: Couldn't initialize: %s\n", nvd_stringify_error(nvd_get_error()));
                exit(EXIT_FAILURE);
        }

        char *dialog_title = "Dialog Title";
        char *dialog_msg   = "Testing Dialog.";
        char *question_dlg = "Are you sure you want to discard changes?";
        char *filename     = NULL;

        NvdDialogBox *dialog         = nvd_dialog_box_new(dialog_title,
                                                  dialog_msg,
                                                  NVD_DIALOG_SIMPLE);

        NvdDialogBox *warning_dialog = nvd_dialog_box_new(dialog_title,
                                                          dialog_msg,
                                                          NVD_DIALOG_WARNING);
        
        NvdDialogBox *error_dialog   = nvd_dialog_box_new(dialog_title,
                                                        dialog_msg,
                                                        NVD_DIALOG_ERROR);
        if (!dialog || !warning_dialog || !error_dialog) {
                puts("Error: Couldn't create dialog box");
                exit(EXIT_FAILURE);
        }

        nvd_free_object(dialog);
        nvd_free_object(warning_dialog);
        nvd_free_object(error_dialog);

        nvd_free_object(NULL); /* This is just to ensure NvDialog catches errors correctly. */

        NvdFileDialog *file_dialog = nvd_open_file_dialog_new("Open File", NULL);
        nvd_free_object(file_dialog);

        NvdAboutDialog *about = nvd_about_dialog_new("NvDialog Test",
                                                     "Simply a testing unit for NvDialog.",
                                                     NULL);

        nvd_free_object(about);

        exit(EXIT_SUCCESS);
}