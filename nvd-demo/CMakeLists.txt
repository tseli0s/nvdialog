cmake_minimum_required(VERSION 3.10)
project(nvd-demo LANGUAGES C VERSION 0.1.0)

add_executable(nvd-demo src/main.c)
target_link_libraries(nvd-demo nvdialog)
