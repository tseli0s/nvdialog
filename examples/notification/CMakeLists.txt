cmake_minimum_required(VERSION 3.22)
project(nvdialog-notification-example VERSION 1.0 LANGUAGES C)

add_executable(notification-example notification.c)
target_link_libraries(notification-example nvdialog)