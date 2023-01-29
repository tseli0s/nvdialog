set(NVDIALOG_SANDBOXED_SOURCES
    nvdialog_sandboxed_file_dialog.c)

add_library(nvdialog_sandbox_impl STATIC ${NVDIALOG_SANDBOXED_SOURCES})
find_package(PkgConfig)
pkg_check_modules(GTK "libadwaita-1")
add_definitions(${GTK_CFLAGS} ${GTK_CFLAGS_OTHER})
target_include_directories(nvdialog_sandbox_impl PRIVATE ${CMAKE_SOURCE_DIR}/include/ ${GTK_INCLUDE_DIRS})