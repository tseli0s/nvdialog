# CMake Build Script for libnvdialog.
# This file is part of libnvdialog and is released under the MIT license.

cmake_minimum_required(VERSION 3.18)
project(libnvdialog LANGUAGES C VERSION 0.8.1 DESCRIPTION "A simple and minimal dialog library, with cross-platform support")

option(WIN32_TARGET "Cross-compile the library for Windows usage from GNU/Linux. Requires i686-w64-mingw32-gcc-win32." OFF)
option(COCOA_TARGET "Build the library for MacOS/Cocoa usage. Please do not disable if you're not sure of what you're doing." ON)
option(NVD_USE_GTK4 "Instead of using the old Gtk3 backend, use Gtk4 and libadwaita for Linux. Experimental." OFF)
option(NVD_BUILD_STATIC "Build NvDialog as a static library. Experimental." OFF)
option(NVD_SANDBOX_SUPPORT "Enable support for Flatpak applications on Linux" ON)

set(CMAKE_C_STANDARD 11)
set(NVDIALOG_MAXBUF 4096)

# On GNU/Linux, by default CMake installs the libraries and headers under
# /usr/local. There are two problems with this approach:
# 1. Arch Linux and a few other distros consider the path deprecated in favor of /usr
# 2. Most linkers shipped with distributions do not search on /usr/local for shared libraries.
# This means the library won't be found at runtime unless LD_LIBRARY_PATH is set to do so.
# For that reason, we set the prefix to /usr.
if (NOT DEFINED ENV{FLATPAK_ID} AND CMAKE_HOST_UNIX AND NOT CMAKE_HOST_APPLE)
        set(CMAKE_INSTALL_PREFIX /usr)
endif()
        
if (NVD_SANDBOX_SUPPORT)
        add_compile_definitions(NVD_SANDBOX_SUPPORT=1)
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin" OR APPLE)
        set(CMAKE_C_COMPILER clang)
        set(MACOSX TRUE)
        enable_language(OBJC) # See #55
else()
        set(MACOSX FALSE)
endif()

if (UNIX AND NOT MACOSX)
        # Finding the Gtk+ / Libadwaita libraries in Unix is generally
        # only possible using PkgConfig.
        find_package(PkgConfig REQUIRED)
endif()

if(WIN32_TARGET)
        set(CMAKE_C_COMPILER /usr/bin/i686-w64-mingw32-gcc-win32)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-stack-protector -Wno-unused-parameter -Wconversion -Werror=format -Werror=format-security -Winline -Wall -Wextra")
else()
        if (MSVC)
                message(WARNING "Compiling using MSVC is still experimental, prefer GCC or CLang if available.")
                set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4")
                add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
        endif()
endif()

message("-- Compiling with flags:\n  ${CMAKE_C_FLAGS}")
add_compile_definitions(NVDIALOG_MAXBUF=${NVDIALOG_MAXBUF})
add_compile_definitions(NVD_EXPORT_SYMBOLS)
include_directories(${CMAKE_SOURCE_DIR}/src/impl/ ${CMAKE_SOURCE_DIR}/vendor)

if (MACOSX)
        if (WIN32_TARGET OR NVD_USE_GTK4)
                message(CRITICAL "Attempted to compile NvDialog with a foreign backend for the platform.")
        else()
                set(NVD_COCOA_SOURCES src/backend/cocoa/nvdialog_dialog_box.m
                                      src/backend/cocoa/nvdialog_file_dialog.m
                                      src/backend/cocoa/nvdialog_question_dialog.m
                                      src/backend/cocoa/nvdialog_notification.m
                                      src/backend/cocoa/nvdialog_about_dialog.m)
                set(NVD_SOURCES ${NVD_COCOA_SOURCES}
                                src/nvdialog_error.c
                                src/nvdialog_capab.c
                                src/nvdialog_version.c
                                src/nvdialog_image.c
                                src/nvdialog_main.c
                                src/nvdialog_util.c)
                if (NVD_BUILD_STATIC)
                        add_library(nvdialog STATIC ${NVD_SOURCES})
                else(NVD_BUILD_STATIC)
                        add_library(nvdialog SHARED ${NVD_SOURCES})
                endif(NVD_BUILD_STATIC)
                add_compile_definitions(NVD_USE_COCOA=1)
                # See #55
                set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-objc-arc")
                target_link_libraries(nvdialog
                        "-framework AppKit"
                        "-framework Cocoa"
                        "-framework Foundation"
                        "-framework UserNotifications")
        endif()
endif()

if (NOT NVD_USE_GTK4)
        set(NVD_GTK_SOURCES src/backend/gtk/nvdialog_about_dialog.c
                            src/backend/gtk/nvdialog_file_dialog.c
                            src/backend/gtk/nvdialog_dialog_box.c
                            src/backend/gtk/nvdialog_question_dialog.c
                            src/backend/gtk/nvdialog_notification.c)
        if (NVD_SANDBOX_SUPPORT)
                set(NVD_SBX_SOURCES src/backend/sandbox/nvdialog_about_dialog.c
                                    src/backend/sandbox/nvdialog_file_dialog.c
                                    src/backend/sandbox/nvdialog_dialog_box.c
                                    src/backend/sandbox/nvdialog_question_dialog.c
                                    src/backend/sandbox/nvdialog_notification.c)
        endif(NVD_SANDBOX_SUPPORT)
        set(NVD_SOURCES ${NVD_GTK_SOURCES} ${NVD_SBX_SOURCES} src/nvdialog_error.c src/nvdialog_image.c  src/nvdialog_util.c src/nvdialog_capab.c src/nvdialog_version.c src/nvdialog_main.c)
else()
        add_compile_definitions(NVD_USE_GTK4)
        set(NVD_SOURCES src/nvdialog_error.c src/nvdialog_version.c src/nvdialog_main.c src/nvdialog_image.c src/nvdialog_util.c)
endif()
set(NVD_HEADERS include/nvdialog_dialog.h
    include/nvdialog_notification.h
    include/nvdialog_core.h
    include/nvdialog_capab.h
    include/nvdialog_types.h
    include/nvdialog_error.h
    include/nvdialog_platform.h
    include/nvdialog_image.h
    include/nvdialog.h)
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
                        src/nvdialog_capab.c
                        src/nvdialog_error.c
                        src/nvdialog_main.c
                        src/nvdialog_version.c
                        src/nvdialog_image.c
                        src/nvdialog_util.c)
        message("The source code files are:\n  ${NVD_SOURCES}")
        if (NVD_BUILD_STATIC)
                add_library(nvdialog STATIC ${NVD_SOURCES})
                add_compile_definitions(NVD_STATIC_LINKAGE)
        else(NVD_BUILD_STATIC)
                add_library(nvdialog SHARED ${NVD_SOURCES})
        endif(NVD_BUILD_STATIC)
        message("-- Compiling a Windows library.")
        target_link_libraries(nvdialog comdlg32 shell32 user32)
elseif(MACOSX)
else(WIN32 OR WIN32_TARGET)
                find_package(PkgConfig)
                if (PKG_CONFIG_FOUND)
                        if (NVD_USE_GTK4)
                                set(NVD_ADW_SOURCES src/backend/adw/nvdialog_about_dialog.c
                                                    src/backend/adw/nvdialog_file_dialog.c
                                                    src/backend/adw/nvdialog_dialog_box.c
                                                    src/backend/adw/nvdialog_question_dialog.c
                                                    src/backend/adw/nvdialog_notification.c)
                                set(NVD_SOURCES ${NVD_SOURCES} ${NVD_ADW_SOURCES})
                                message("Sources are: ${NVD_SOURCES}")
                                pkg_check_modules(GTK "libadwaita-1") # Well actually, libadwaita isn't Gtk4, but who cares anyways :P
                                message(STATUS "DEBUG: libadwaita flags are: ${GTK_CFLAGS} ${GTK_CFLAGS_OTHER}")
                                add_definitions(${GTK_CFLAGS} ${GTK_CFLAGS_OTHER})
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

set_target_properties(nvdialog PROPERTIES SOVERSION 2)
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
file(GLOB NVDIALOG_TEST_FILES "tests/test_*.c")

set(NVDIALOG_TESTS init;dialogs;multithreading;aboutdlg;question;notification)
foreach(test_executable ${NVDIALOG_TESTS})
        add_executable(nvdialog_${test_executable}_test tests/test_${test_executable}.c)
        target_compile_definitions(nvdialog_${test_executable}_test PRIVATE NVDIALOG_TESTING)
        target_link_libraries(nvdialog_${test_executable}_test nvdialog)
        # This is required as testing takes place before installing. 
        # What kind of logic is that CMake?
        target_include_directories(nvdialog_${test_executable}_test PUBLIC ${CMAKE_SOURCE_DIR}/include/)
        add_test(NAME nvdialog_${test_executable}_test COMMAND $<TARGET_FILE:nvdialog_${test_executable}_test>)
endforeach(test_executable)
