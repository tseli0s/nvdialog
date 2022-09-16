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

#include "nvdialog_adw.h"
#include "../nvdialog_macros.h"
#include "nvdialog_core.h"
#include "nvdialog_types.h"
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#define NVD_NO_FLAGS (0)

/* Copy of the original implementation to access the members. */
struct _NvdContext {
#ifdef NVD_USE_GTK4
        AdwApplication *application;
#else
        GtkApplication *application;
#endif /* NVD_USE_GTK4 */
        bool initialized, ready;
        const char *domain;
        uint32_t flags;
};

/*
 * The struct used to pass data into the activate() function.
 * This struct should be allocated on the heap.
 */
typedef struct _NvdActivateData {
        bool show;
        char *title, contents;
        void *dialog, *return_data;
} NvdActivateData;

/* A handle to the current context bound. */
static NvdContext *nvd_bound_ctx = NULL;

/*
 * TODO: Instead of creating an entire application, we
 * should just call Adwaita functions similar to Gtk.
 */
static inline AdwApplication *nvd_create_application_adw(const char *domain) {
        g_autoptr(AdwApplication) app =
            adw_application_new(domain, NVD_NO_FLAGS);
        return app;
}

static NVD_FORCE_INLINE void nvd_delete_app(AdwApplication *app) {
        g_object_unref(app);
}

static void nvd_open_file_adw_response(NvdActivateData *data,
                                       int32_t response) {
        if (response == GTK_RESPONSE_ACCEPT) {
                GtkFileChooser *chooser = GTK_FILE_CHOOSER(data->dialog);
                GFile *file = gtk_file_chooser_get_file(chooser);
                assert(file != NULL);
                const char *filename = g_file_get_path(file);
                assert(filename != NULL);

                data->return_data = (char *)filename;
        }
        gtk_window_destroy(GTK_WINDOW(data->dialog));
}

NvdContext *nvd_bind_context_adw() {
        /* Maybe we should just use the stack instead? */
        NvdContext *ctx = calloc(1, sizeof(struct _NvdContext));
        if (!ctx)
        {
                nvd_error_message("WARNING -- Failed to create context.");
                nvd_out_of_memory();
        }

        ctx->domain = nvd_get_domain_name();
        ctx->application = nvd_create_application_adw(ctx->domain);

        ctx->initialized = true;
        ctx->flags = NVD_NO_FLAGS;
        ctx->ready = true;

        /* For some reason, this one works instead of plain assignment. */
        NvdContext **ctx_static = &nvd_bound_ctx;
        *ctx_static = ctx;
        return ctx; /* TODO: Potential memory leak here, we need to fix it. */
}

inline void nvd_delete_context_adw(NvdContext *ctx) {
        nvd_delete_app(ctx->application);
        free(ctx);
        return;
}

/* INCOMPLETE FUNCTION -- FIXING NEEDED */
const char *nvd_open_file_dialog_adw(const char *title,
                                     const char *file_extensions) {
        GtkFileChooserNative *native = gtk_file_chooser_native_new(
            title, NULL, GTK_FILE_CHOOSER_ACTION_OPEN, "Save", "Cancel");
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(native);
        NvdActivateData *data = calloc(1, sizeof(NvdActivateData));
        assert(data != NULL);
        g_signal_connect(native, "response",
                         G_CALLBACK(nvd_open_file_adw_response), data);
        gtk_native_dialog_show(GTK_NATIVE_DIALOG(native));

        assert(data->return_data != NULL);
        return strdup(
            (const char *)data
                ->return_data); /* FIXME: Memory leak from 'data' variable */
}

NvdDialogBox *nvd_create_adw_dialog(const char *title, const char *message,
                                    const NvdDialogType type) {
        NVD_ASSERT_FATAL(nvd_bound_ctx != NULL);
        NVD_ASSERT_FATAL(nvd_bound_ctx->ready == true);
        NVD_ASSERT_FATAL(
                title != NULL &&
                message != NULL &&
                nvd_bound_ctx->application != NULL
        );
        GtkWidget *dialog = adw_message_dialog_new(NULL, title, message);
        adw_message_dialog_add_responses(ADW_MESSAGE_DIALOG(dialog), "proceed",
                                         "Ok", NULL);
        int response = 0;
        switch (type) {
        /* There isn't a ADW_RESPONSE_WARNING so just going with the error. */
        case NVD_DIALOG_WARNING:
        case NVD_DIALOG_ERROR:
                response = ADW_RESPONSE_DESTRUCTIVE;
                break;
        /* If incorrect, just use the default instead of crashing the entire
         * process. */
        case NVD_DIALOG_SIMPLE:
        default:
                response = ADW_RESPONSE_DEFAULT;
                break;
        }
        adw_message_dialog_set_response_appearance(ADW_MESSAGE_DIALOG(dialog),
                                                   "proceed", response);
        gtk_window_present(GTK_WINDOW(dialog));
        char *_argv = nvd_get_argv();
        assert(_argv != NULL && _argv != 0x1);
        g_application_run(G_APPLICATION(nvd_bound_ctx->application), 1, &_argv);
}