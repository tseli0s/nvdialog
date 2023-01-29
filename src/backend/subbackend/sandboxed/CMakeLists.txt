set(NVDIALOG_SANDBOXED_SOURCES
    nvdialog_sandboxed_file_dialog.c
    nvdialog_sandboxed_dialog_box.c
    nvdialog_sandboxed_question_dialog.c)

add_library(nvdialog_sandbox_impl STATIC ${NVDIALOG_SANDBOX_SOURCES})