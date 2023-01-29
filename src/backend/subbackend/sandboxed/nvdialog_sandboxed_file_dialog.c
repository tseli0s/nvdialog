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

#include "nvdialog_sandbox.h"
#include "../../../nvdialog_assert.h"
#include <stdlib.h>

#define TIMEOUT_MAX_SECONDS (25)

struct _NvdFileDialog {
        void *raw;
        char *filename;
        bool is_save_dialog;
};

static char* _nvd_native_filename = NULL;

static void file_callback(GtkNativeDialog *native,
                          int              response) {
        if (response == GTK_RESPONSE_ACCEPT) {
                GtkFileChooser *chooser = GTK_FILE_CHOOSER (native);
                GFile *file = gtk_file_chooser_get_file (chooser);

                /* 
                 * Gtk won't let us use some user data; We have
                 * to workaround it like this:
                */
                _nvd_native_filename = g_file_get_path(file);
                g_object_unref (file);
        }

        g_object_unref (native);
}

/*
 * Being completely honest, I've never worked with DBus myself before, nevermind about
 * using a portal API. Since Gtk already has done this job, we will just use the
 * native file dialog provided by Gtk and this will do all the heavy lifting for us
 * without any extra dependencies.
*/
NvdFileDialog *nvd_open_file_dialog_sndbx(const char *title,
                                          const char *file_extensions) {
        (void) file_extensions;

        NvdFileDialog *dialog = malloc(sizeof(struct _NvdFileDialog));
        NVD_RETURN_IF_NULL(dialog);

        dialog->is_save_dialog = false;
        dialog->filename       = NULL;
        dialog->raw            = gtk_file_chooser_native_new(title,
                                                             NULL,
                                                             GTK_FILE_CHOOSER_ACTION_OPEN,
                                                             "Open",
                                                             "Cancel");
        g_signal_connect(dialog->raw, "response", G_CALLBACK(file_callback), NULL);
        return dialog;
}

void nvd_get_file_location_sndbx(NvdFileDialog *dialog, const char **savebuf) {
        NVD_ASSERT_FATAL(savebuf != NULL);
        *savebuf = _nvd_native_filename;
}