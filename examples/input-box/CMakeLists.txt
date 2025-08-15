cmake_minimum_required(VERSION 3.22)
project(nvdialog-hello-world VERSION 1.0 LANGUAGES C)

add_executable(input_box input_box.c)

# TODO: Create a CMake package file to allow
# projects to import NvDialog through CMake using
# find_package().
target_link_libraries(input_box nvdialog)