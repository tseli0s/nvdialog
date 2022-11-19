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
#include "nvdialog_adw.h"
#include "../../nvdialog_assert.h"
#include <stdio.h>
#include <unistd.h>

struct _NvdCSSManager {
        void *raw;
        bool used;
        char *filename;
        void *extra_data;
};

static char *__nvd_string_gen(char *str, size_t size) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJ";
    if (size) {
        --size;
        for (size_t n = 0; n < size; n++) {
            int key = rand() % (int)(sizeof charset - 1);
            str[n] = charset[key];
        }
        str[size] = '\0';
    }
    return str;
}

NvdCSSManager *nvd_css_manager_adw() {
        /* Only using calloc() here because I don't want to assign NULL everywhere :P */
        NvdCSSManager *mgr = calloc(1, sizeof(struct _NvdCSSManager));
        NVD_RETURN_IF_NULL(mgr);

        mgr->raw  = gtk_css_provider_new();
        mgr->used = false;

        return mgr;
}

int nvd_css_manager_attach_string_stylesheet_adw(NvdCSSManager *mgr,
                                                 const char    *str) {
        chdir("/tmp"); /* So we don't harm anything we shouldn't. */

        char *new_filename = calloc(1, sizeof(char) * 13);
        __nvd_string_gen(new_filename, 12);

        FILE *stream = fopen(new_filename, "w");
        fputs (str, stream);
        fclose(stream);

        char filename[NVDIALOG_MAXBUF];
        sprintf(filename, "%s%s", "/tmp/", new_filename);

        gtk_css_provider_load_from_path ((GtkCssProvider*) mgr->raw,
                                                      filename);
        /*
         * Well, we could store it in 'mgr' but then why even create a random
         * string for its filename?
         */
        free(new_filename);
        return 0;
}

int nvd_css_manager_attach_stylesheet_adw(NvdCSSManager *mgr, const char *filename) {
        gtk_css_provider_load_from_path(mgr->raw,
                                        filename);
        return 0;
}

int nvd_css_manager_use_style_adw(NvdCSSManager *mgr, void *raw_handle) {
        gtk_style_context_add_provider(
                gtk_widget_get_style_context(GTK_WIDGET(raw_handle)),
                mgr->raw,
                GTK_STYLE_PROVIDER_PRIORITY_USER
        );
        return 0;
}