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

#include "nvdialog_gtk.h"
#include "../nvdialog_error.h"
#include "nvdialog.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#ifndef NVD_PADDING_SIZE
#define NVD_PADDING_SIZE (12)  /* TODO: Make this
                                changeable at compile time
                                */
#endif  /* NVD_PADDING_SIZE */

#define NVD_CHECK_GTK_INIT                                                     \
        if (!gtk_init_check(NULL, NULL)) {                                     \
                nvd_set_error(NVD_NOT_INITIALIZED);                            \
                nvd_print(nvd_stringify_error(nvd_get_error()));               \
                return NULL;                                                   \
        }

#define NVD_CHECK_GTK_INIT_INT if (!gtk_init_check(NULL, NULL)) {              \
                nvd_set_error(NVD_NOT_INITIALIZED);                            \
                nvd_print(nvd_stringify_error(nvd_get_error()));               \
                return -1;                                                     \
        }

#ifndef NVDIALOG_MAXBUF
#define NVDIALOG_MAXBUF 4096
#endif /* NVDIALOG_MAXBUF */

static NvdReply __dialog_reply = -1; /* By default invalid. */

/*
 * A few callbacks for the response buttons.
 * TODO: Perhaps make this entire code better,
 * by passing a pointer argument to a local variable instead?
 */

static inline void ok_clicked(void)
{
        __dialog_reply = NVD_REPLY_OK;
}

static inline void cancel_clicked(void)
{
        __dialog_reply = NVD_REPLY_CANCEL;
}

static inline void no_clicked(void)
{
        __dialog_reply = NVD_REPLY_NO;
}

/*
 * Sets equal padding for a Gtk widget.
 * Basically a shortcut for gtk_widget_set_margin_*
*/
static inline void nvd_set_margin(GtkWidget *widget)
{
        gtk_widget_set_margin_top(widget, NVD_PADDING_SIZE);
        gtk_widget_set_margin_bottom(widget, NVD_PADDING_SIZE);
        gtk_widget_set_margin_start(widget, NVD_PADDING_SIZE);
        gtk_widget_set_margin_end(widget, NVD_PADDING_SIZE);
}

/*
 * FIXME: This function segfaults apparently. I can't find why.
 * Perhaps it's a bug in Gtk3?
 */
const char *nvd_open_file_dialog_gtk(const char *title,
                                     const char *file_extensions) {
        NVD_CHECK_GTK_INIT;

        /* Creating the dialog. */
        GtkWidget *dialog = gtk_file_chooser_dialog_new(
            title, NULL, GTK_FILE_CHOOSER_ACTION_OPEN, "Open",
            GTK_RESPONSE_ACCEPT, "Cancel", GTK_RESPONSE_CANCEL, NULL);
        /* Running the dialog and checking the user's action. */
        int result = gtk_dialog_run(GTK_DIALOG(dialog));
        if (result == GTK_RESPONSE_ACCEPT) {
                GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
                char *filename = gtk_file_chooser_get_filename(chooser);
                /* The dialog should be destroyed at this stage. */
                gtk_widget_destroy(dialog);

                printf("Filename: %s", filename);
                return strdup(filename);
        } else if (result == GTK_RESPONSE_CANCEL) {
                gtk_main_quit();
                return NULL;
        }
        return NULL;
}

void *nvd_create_gtk_dialog(const char *title, const char *message,
                            NvdDialogType type) {
        NVD_CHECK_GTK_INIT;
        GtkWidget *dialog, *label, *content_area, *ok_button, *image;
        GtkDialogFlags flags = GTK_DIALOG_USE_HEADER_BAR;

        char *icon = NULL;
        switch (type) {
        case NVD_DIALOG_ERROR:
                icon = "dialog-error";
                break;
        case NVD_DIALOG_SIMPLE:
                icon = "dialog-information";
                break;
        case NVD_DIALOG_WARNING:
                icon = "dialog-warning";
                break;
        default:
                return NULL;
        }

        image = gtk_image_new_from_icon_name(icon, GTK_ICON_SIZE_DIALOG);
        dialog = gtk_dialog_new_with_buttons(title, NULL, flags, NULL,
                                             GTK_RESPONSE_NONE, NULL);
        content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
        label = gtk_label_new(message);
        ok_button = gtk_button_new_with_label("Ok");

        gtk_widget_set_margin_bottom(ok_button, 6);
        gtk_widget_set_margin_start(ok_button, 6);
        gtk_widget_set_margin_end(ok_button, 6);
        gtk_widget_set_margin_top(ok_button, 6);

        gtk_widget_set_margin_bottom(image, 12);
        gtk_widget_set_margin_start(image, 12);
        gtk_widget_set_margin_end(image, 12);
        gtk_widget_set_margin_top(image, 12);

        g_signal_connect_swapped(dialog, "response", G_CALLBACK(gtk_main_quit),
                                 NULL);
        g_signal_connect_swapped(ok_button, "clicked",
                                 G_CALLBACK(gtk_main_quit), NULL);
        GtkWidget *grid = gtk_grid_new();
        gtk_grid_set_row_spacing(GTK_GRID(grid), 12);
        gtk_container_add(GTK_CONTAINER(content_area), grid);

        gtk_grid_attach(GTK_GRID(grid), image, 0, 0, 1, 1);
        gtk_grid_attach(GTK_GRID(grid), label, 1, 0, 1, 1);
        gtk_grid_attach(GTK_GRID(grid), ok_button, 2, 1, 1, 1);

        gtk_widget_show_all(dialog);
        gtk_main();

        return dialog;
}

NvdReply nvd_question_gtk(const char *title,
                          const char *question,
                          NvdQuestionButton button)
{
        NVD_CHECK_GTK_INIT_INT;

        const char* icon_name = "dialog-question";
        GtkWidget*  dialog, *grid, *button_yes, *button_no, *button_cancel, *text, *icon;

        dialog = gtk_dialog_new();
        gtk_window_set_title(GTK_WINDOW (dialog), title);
        text   = gtk_label_new(question);
        grid   = gtk_grid_new();
        gtk_container_add (GTK_CONTAINER (dialog), grid);
        icon = gtk_image_new_from_icon_name(icon_name, GTK_ICON_SIZE_DIALOG);
        button_yes = gtk_button_new_with_label("Yes");
        g_signal_connect_swapped(button_yes, "clicked",
                                 G_CALLBACK(ok_clicked), NULL);

        button_no     = NULL;
        button_cancel = NULL;

        switch (button)
        {
                case NVD_YES_NO:
                button_no = gtk_button_new_with_label("No");
                /* Yes already created, skipping. */
                break;

                case NVD_YES_NO_CANCEL:
                button_cancel = gtk_button_new_with_label("Cancel");
                button_no = gtk_button_new_with_label("No");
                break;

                case NVD_YES_CANCEL:
                button_cancel = gtk_button_new_with_label("Cancel");
        }

        gtk_grid_attach(GTK_GRID (grid), icon, 0, 0, 1, 1);
        gtk_grid_attach(GTK_GRID (grid), text, 1, 0, 1, 1);
        gtk_grid_attach(GTK_GRID (grid), button_yes, 0, 1, 1, 1);

        nvd_set_margin(button_yes);
        nvd_set_margin(button_no );
        nvd_set_margin(button_cancel);
        nvd_set_margin(icon);
        nvd_set_margin(text);

        if (button_no)
        {
                gtk_grid_attach(GTK_GRID (grid), button_no, 1, 1, 1, 1);
                g_signal_connect_swapped(button_no, "clicked",
                                 G_CALLBACK(no_clicked), NULL);
        }
        if (button_cancel)
        {
                gtk_grid_attach(GTK_GRID (grid), button_cancel, 2, 1, 1, 1);
                g_signal_connect_swapped(button_cancel, "clicked",
                                 G_CALLBACK(cancel_clicked), NULL);
        }

        gtk_grid_set_row_spacing(GTK_GRID(grid), 12);

        gtk_widget_show_all(dialog);
        gtk_main();
        return __dialog_reply;
}