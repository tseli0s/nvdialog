# CMake Build Script for libnvdialog.
# This file is part of libnvdialog and is released under the MIT license.

cmake_minimum_required(VERSION 3.18)
project(libnvdialog LANGUAGES C VERSION 0.3.0 DESCRIPTION "A simple and minimal dialog library, with cross-platform support")

option(WIN32_TARGET "Build the library for Windows usage. Requires x86_64-w64-mingw32." OFF)
option(NVD_USE_GTK4 "Instead of using the old Gtk3 backend, use Gtk4 and libadwaita for Linux. Experimental." ON) # Default since 0.2.0-plus-some-commits.
option(NVD_BUILD_STATIC "Build NvDialog as a static library. Experimental." OFF)

set(NVDIALOG_MAXBUF 4096)

# On GNU/Linux, by default CMake installs the libraries and headers under
# /usr/local. There are two problems with this approach:
# 1. Arch Linux and a few other distros consider the path deprecated in favor of /usr
# 2. Most linkers shipped with distributions do not search on /usr/local for shared libraries.
# This means the library won't be found at runtime unless LD_LIBRARY_PATH is set to do so.
# For that reason, we set the prefix to /usr.
if (UNIX)
        set(CMAKE_INSTALL_PREFIX /usr)
endif()

if(WIN32_TARGET)
        set(CMAKE_C_COMPILER /usr/bin/x86_64-w64-mingw32-gcc)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-stack-protector -Wno-unused-parameter -Wconversion -Werror=format -Werror=format-security -Winline -Wall -Wextra")
else()
        if (MSVC)
                # MSVC doesn't really like GNU style arguments
                message("NOTE: Compiling using MSVC is still experimental, prefer GCC or CLang if available.")
                set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4")
        else()
                set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fstack-protector-all -fstack-clash-protection -Wno-unused-parameter --param ssp-buffer-size=4 -Wconversion -Werror=format -Werror=format-security -Winline -Wall -Wextra")
        endif()
endif()

message("-- Compiling with flags:\n  ${CMAKE_C_FLAGS}")
add_compile_definitions(NVDIALOG_MAXBUF=${NVDIALOG_MAXBUF})
if (NOT NVD_USE_GTK4)
        set(NVD_GTK_SOURCES src/backend/gtk/nvdialog_about_dialog.c
                            src/backend/gtk/nvdialog_file_dialog.c
                            src/backend/gtk/nvdialog_dialog_box.c
                            src/backend/gtk/nvdialog_question_dialog.c
                            src/backend/gtk/nvdialog_css_manager.c
                            src/backend/gtk/nvdialog_notification.c)
        set(NVD_SOURCES ${NVD_GTK_SOURCES} src/nvdialog_error.c src/nvdialog_capab.c src/nvdialog_version.c src/nvdialog_main.c)
else()
        add_compile_definitions(NVD_USE_GTK4)
        set(NVD_SOURCES src/nvdialog_error.c src/nvdialog_version.c src/nvdialog_main.c)
endif()
message("-- NVDIALOG_MAXBUF equals ${NVDIALOG_MAXBUF}. If buffer overflows are detected, increase this number.")
set(NVD_HEADERS include/nvdialog_dialog.h include/nvdialog_css_manager.h include/nvdialog_notification.h include/nvdialog_core.h include/nvdialog_capab.h include/nvdialog_types.h include/nvdialog_error.h include/nvdialog.h)
set(NVD_EXTRA_HEADERS include/dialogs/nvdialog_file_dialog.h include/dialogs/nvdialog_about_dialog.h include/dialogs/nvdialog_dialog_box.h)

# If compiling for Windows, only use Win32 API.
# Otherwise, use the standard backends.
if (WIN32 OR WIN32_TARGET)
        set(NVD_WIN32_SOURCES src/backend/win32/nvdialog_about_dialog.c
                              src/backend/win32/nvdialog_dialog_box.c
                              src/backend/win32/nvdialog_question_dialog.c
                              src/backend/win32/nvdialog_file_dialog.c
                              src/backend/win32/nvdialog_notification.c)
        set(NVD_SOURCES ${NVD_WIN32_SOURCES}
                        src/core/nvdialog_structs.c
                        src/nvdialog_error.c
                        src/nvdialog_version.c
                        src/nvdialog_capab.c
                        src/nvdialog_main.c)
        message("The source code files are:\n  ${NVD_SOURCES}")
        if (NVD_BUILD_STATIC)
                add_library(nvdialog STATIC ${NVD_SOURCES})
        else(NVD_BUILD_STATIC)
                add_library(nvdialog SHARED ${NVD_SOURCES})
                add_compile_definitions(NVD_STATIC_LINKAGE)
        endif(NVD_BUILD_STATIC)
        message("-- Compiling a Windows library.")
        target_link_libraries(nvdialog comdlg32 shell32 user32)
else(WIN32 OR WIN32_TARGET)
                find_package(PkgConfig)
                if (PKG_CONFIG_FOUND)
                        if (NVD_USE_GTK4)
                                set(NVD_ADW_SOURCES src/backend/adw/nvdialog_about_dialog.c
                                                    src/backend/adw/nvdialog_file_dialog.c
                                                    src/backend/adw/nvdialog_dialog_box.c
                                                    src/backend/adw/nvdialog_css_manager.c
                                                    src/backend/adw/nvdialog_question_dialog.c
                                                    src/backend/adw/nvdialog_notification.c)
                                set(NVD_SOURCES ${NVD_SOURCES} ${NVD_ADW_SOURCES})
                                message("Sources are: ${NVD_SOURCES}")
                                pkg_check_modules(GTK "libadwaita-1") # Well actually, libadwaita isn't Gtk4, but who cares anyways :P
                        else(NVD_USE_GTK4)
                                pkg_check_modules(GTK "gtk+-3.0")
                        endif(NVD_USE_GTK4)
                        if (GTK_FOUND)
                                add_definitions(${GTK_CFLAGS} ${GTK_CFLAGS_OTHER})
                        else(GTK_FOUND)
                                message(FATAL_ERROR "CRITICAL: Gtk libraries not found, aborting.")
                        endif(GTK_FOUND)
                endif(PKG_CONFIG_FOUND)
                message("-- Compiling a GNU/Linux library.")
                if (NVD_BUILD_STATIC)
                        add_library(nvdialog STATIC ${NVD_SOURCES})
                        target_link_libraries(nvdialog ${GTK_LIBRARIES})
                        add_compile_definitions(NVD_STATIC_LINKAGE)
                else(NVD_BUILD_STATIC)
                        add_library(nvdialog SHARED ${NVD_SOURCES})
                        target_link_libraries(nvdialog ${GTK_LIBRARIES})
                endif()
endif(WIN32 OR WIN32_TARGET)

set_target_properties(nvdialog PROPERTIES SOVERSION 1)
set_target_properties(nvdialog PROPERTIES VERSION ${PROJECT_VERSION})
target_include_directories(nvdialog PRIVATE include/)
# Required to find the system paths easier.
include(GNUInstallDirs)

find_package(PkgConfig)
if (PKG_CONFIG_FOUND)
        message(STATUS "pkg-config was detected, NvDialog will generate a pkg-config script too.")
        set(target1 nvdialog)
        set(pc_libs_private)
        set(pc_req_private)
        set(pc_req_public)
        configure_file(pkg-config/nvdialog.pc.in nvdialog.pc @ONLY)

        set(NVDIALOG_PKG_CONFIG_FILE ${CMAKE_SOURCE_DIR}/build/nvdialog.pc)
        install(FILES ${NVDIALOG_PKG_CONFIG_FILE} DESTINATION ${CMAKE_INSTALL_PREFIX}/share/pkgconfig)
endif()

# On Windows the installation procedure is a bit different
# so until we resolve this the library and the header have to
# be manually installed.
install(TARGETS nvdialog LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(DIRECTORY DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/nvdialog/)
install(DIRECTORY DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/nvdialog/dialogs)
install(FILES ${NVD_EXTRA_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/nvdialog/dialogs)
install(FILES ${NVD_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/nvdialog/)

enable_testing()
add_executable(nvdialog_test ${CMAKE_SOURCE_DIR}/tests/nvdialog_test.c)
if (LINUX)
        target_link_libraries(nvdialog_test PRIVATE nvdialog notify)
else(LINUX)
        target_link_libraries(nvdialog_test PRIVATE nvdialog)
endif(LINUX)
target_include_directories(nvdialog_test PRIVATE ${CMAKE_SOURCE_DIR}/include/) # Required
add_test(
        NAME    nvdialog_test
        COMMAND $<TARGET_FILE:nvdialog_test>
)
