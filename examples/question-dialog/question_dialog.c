#include <stdio.h>
#include <errno.h>
#include <nvdialog/nvdialog.h>
#include <stdlib.h>

int main(int argc, char** argv) {
        int result = nvd_init();
        if (result != 0) {
                puts("Error: Couldn't initialize NvDialog.");
                exit(EXIT_FAILURE);
        }

        NvdQuestionBox *dialog = nvd_dialog_question_new("Question dialog", "Press Yes, No or Cancel. Your choice will be printed in stdout.", NVD_YES_NO_CANCEL);
        if (!dialog) {
                puts("Error: Could not construct the dialog.");
                return -ENOMEM;
        }

        NvdReply reply = nvd_get_reply(dialog);
        switch (reply) {
            case NVD_REPLY_OK:
                printf("You chose yes.\n");
                break;
            case NVD_REPLY_NO:
                printf("You chose no.\n");
                break;
            case NVD_REPLY_CANCEL:
                printf("You cancelled.\n");
                break;
        }
        nvd_free_object(dialog);

        return 0;
}
