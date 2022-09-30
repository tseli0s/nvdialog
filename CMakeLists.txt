# CMake Build Script for libnvdialog.
# This file is part of libnvdialog and is released under the MIT license.

cmake_minimum_required(VERSION 3.18)
project(libnvdialog LANGUAGES C VERSION 0.1.3 DESCRIPTION "A simple and minimal dialog library, with cross-platform support")

option(WIN32_TARGET "Build the library for Windows usage. Requires x86_64-w64-mingw32." OFF)
option(NVD_USE_GTK4 "Instead of using the old Gtk3 backend, use Gtk4 and libadwaita for Linux. Experimental.")
option(NVD_BUILD_STATIC "Build NvDialog as a static library. Experimental." OFF) # TODO: Turn this ON by default (0.2)

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
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -flto -Wno-unused-parameter --param ssp-buffer-size=4 -Wconversion -Werror=format -Werror=format-security -Winline -Wall -Wextra")
add_compile_definitions(_FORTIFY_SOURCE=2)
add_compile_definitions(NVDIALOG_MAXBUF=${NVDIALOG_MAXBUF})
if (NOT NVD_USE_GTK4)
        set(NVD_SOURCES src/nvdialog_error.c src/nvdialog_capab.c src/nvdialog_version.c src/backend/nvdialog_gtk.c src/nvdialog_main.c)
else()
        add_compile_definitions(NVD_USE_GTK4)
        message("-- NOTE: Compiling NvDialog using the experimental Gtk4+Libadwaita backend.")
        set(NVD_SOURCES src/nvdialog_error.c src/nvdialog_version.c src/backend/nvdialog_adw.c src/nvdialog_main.c)
endif()
message("-- NVDIALOG_MAXBUF equals ${NVDIALOG_MAXBUF}. If buffer overflows are detected, increase this number.")
set(NVD_HEADERS include/nvdialog_dialog.h include/nvdialog_core.h include/nvdialog_capab.h include/nvdialog_types.h include/nvdialog_error.h include/nvdialog.h)
# If compiling for Windows, only use Win32 API.
# Otherwise, use the standard backends.
if (WIN32 OR WIN32_TARGET)
        if (NVD_BUILD_STATIC)
                add_library(nvdialog STATIC src/nvdialog_error.c src/nvdialog_version.c src/backend/nvdialog_win32.c src/nvdialog_capab.c src/nvdialog_main.c)
        else(NVD_BUILD_STATIC)
                add_library(nvdialog SHARED src/nvdialog_error.c src/nvdialog_version.c src/backend/nvdialog_win32.c src/nvdialog_capab.c src/nvdialog_main.c)
        endif(NVD_BUILD_STATIC)
        message("-- Compiling a Windows library.")
        target_link_libraries(nvdialog comdlg32)
else()
        if (NVD_BUILD_STATIC)
                add_library(nvdialog STATIC ${NVD_SOURCES})
        else(NVD_BUILD_STATIC)
                add_library(nvdialog SHARED ${NVD_SOURCES})
        endif(NVD_BUILD_STATIC)
        find_package(PkgConfig)
        if (PKG_CONFIG_FOUND)
                if (NVD_USE_GTK4)
                        pkg_check_modules(GTK "libadwaita-1") # Well actually, libadwaita isn't Gtk4, but who cares anyways :P
                else(NVD_USE_GTK4)
                        pkg_check_modules(GTK "gtk+-3.0")
                endif(NVD_USE_GTK4)
                if (GTK_FOUND)    
                        target_link_libraries(nvdialog ${GTK_LIBRARIES})
                        add_definitions(${GTK_CFLAGS} ${GTK_CFLAGS_OTHER})
                else(GTK_FOUND)
                        message(FATAL_ERROR "CRITICAL: Gtk libraries not found, aborting.")
                endif()
        endif()

        message("-- Compiling a GNU/Linux library.")
endif()

set_target_properties(nvdialog PROPERTIES SOVERSION 0)
set_target_properties(nvdialog PROPERTIES VERSION ${PROJECT_VERSION})
target_include_directories(nvdialog PRIVATE include/)
# Required to find the system paths easier.
include(GNUInstallDirs)

# On Windows the installation procedure is a bit different
# so until we resolve this the library and the header have to
# be manually installed.
install(TARGETS nvdialog LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(DIRECTORY DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/nvdialog/ )
install(FILES ${NVD_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/nvdialog/)
