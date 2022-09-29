#include <nvdialog/nvdialog.h>
int main(int argc, char **argv) {
        nvd_init(argv[0]);
        NvdReply reply = nvd_dialog_question_new("Exit Now?",
                                                 "Are you sure you want to exit?",
                                                 NVD_YES_NO_CANCEL);
        switch (reply) {
                case NVD_REPLY_NO:
                case NVD_REPLY_CANCEL:
                        /* Cancel or No pressed in the dialog */
                        return argc; /* Just to avoid an unused parameter warning */
                case NVD_REPLY_OK:
                        return 0;
        }
}