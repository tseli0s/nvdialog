cmake_minimum_required(VERSION 3.22)
project(nvdialog-question-dialog VERSION 1.0 LANGUAGES C)

add_executable(question-dialog question_dialog.c)
target_link_libraries(question-dialog nvdialog)