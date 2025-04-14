#include <unistd.h>
#include <stdlib.h>
#include <nvdialog/nvdialog.h>
#include <stdio.h>

static void die(const char *msg) {
    fprintf(stderr, "Error: %s", msg);
    abort();
}

int main(void) {
    if (nvd_init() != 0)
        die("Couldn't initialize NvDialog");

    NvdDialogBox *dialog = nvd_dialog_box_new("Introduction", "This is a basic dialog box created with NvDialog.", NVD_DIALOG_SIMPLE);
    NvdDialogBox *warning = nvd_dialog_box_new("Warning", "This is a warning dialog box created with NvDialog.", NVD_DIALOG_WARNING);

    if (!dialog || !warning)
        die("Couldn't create dialog boxes");

    nvd_show_dialog(dialog);
    nvd_show_dialog(warning);

    NvdQuestionBox *question = nvd_dialog_question_new("Question", "Do you like NvDialog so far? (If not, file an issue please :)))", NVD_YES_NO);
    if (!question) die("Couldn't create question dialog box");

    NvdReply reply = nvd_get_reply(question);
    if (reply == NVD_REPLY_OK) {
        NvdDialogBox *success = nvd_dialog_box_new("Thanks", "Thank you! Make sure to star the project on GitHub. Your support means a lot :)", NVD_DIALOG_SIMPLE);
        nvd_dialog_box_set_accept_text(success, "I will star!");
        nvd_show_dialog(success);
        nvd_free_object(success);
    } else {
        NvdDialogBox *error = nvd_dialog_box_new("Sad", "That's alright, make sure to report any issues you have in our repository!", NVD_DIALOG_ERROR);
        nvd_show_dialog(error);
        nvd_free_object(error);
    }

    NvdNotification *notif = nvd_notification_new("Whoop!", "Seems like a notification was sent from NvDialog...", NVD_NOTIFICATION_WARNING);
    nvd_send_notification(notif);
    nvd_delete_notification(notif);

    NvdFileDialog *choose_dir = nvd_open_folder_dialog_new("Pick the new directory of the process", NULL);
    if (!choose_dir) die("Couldn't create folder dialog");
    const char *dir_buffer;
    nvd_get_file_location(choose_dir, &dir_buffer);
    if (dir_buffer) chdir(dir_buffer);

    NvdFileDialog *choose_icon = nvd_open_file_dialog_new("Pick the icon for the next dialog", NULL);
    const char *file_buffer;
    nvd_get_file_location(choose_icon, &file_buffer);
    NvdAboutDialog *about_dialog = nvd_about_dialog_new("NvDialog Demo", "This is a demo application to show how NvDialog works. It is also used to test if the library works as expected across platforms.", NULL);
    if (!about_dialog) die("Couldn't create NvdAboutDialog");
    int w, h;
    const uint8_t *buffer = nvd_image_from_filename(file_buffer, &w, &h);
    NvdImage *image = nvd_create_image(buffer, w, h);
    nvd_dialog_set_icon(about_dialog, image);
    nvd_show_about_dialog(about_dialog);

    nvd_free_object(question);
    nvd_free_object(dialog);
    nvd_free_object(warning);
    nvd_free_object(about_dialog);
    nvd_free_object(choose_dir);
    nvd_free_object(choose_icon);

    return 0;
}