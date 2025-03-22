cmake_minimum_required(VERSION 3.22)
project(nvdialog-hello-world VERSION 1.0 LANGUAGES C)

add_executable(dialog-with-image dialog-with-image.c)
target_link_libraries(dialog-with-image nvdialog)