# CMake Build Script for libnvdialog.
# This file is part of libnvdialog and is released under the MIT license.

cmake_minimum_required(VERSION 3.18)
project(libnvdialog LANGUAGES C VERSION 0.1.0 DESCRIPTION "A simple and minimal dialog library, with cross-platform support")

option(WIN32_TARGET "Build the library for Windows usage. Requires x86_64-w64-mingw32." OFF)

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

set(CMAKE_C_FLAGS "-Wall -Wextra -O3 -s")

set(NVD_SOURCES src/nvdialog_version.c src/backend/nvdialog_adw.c src/backend/nvdialog_gtk.c src/backend/nvdialog_fallback.c src/nvdialog_main.c)

# If compiling for Windows, only use Win32 API.
# Otherwise, use the standard backends.
if (WIN32 OR WIN32_TARGET)
        add_library(nvdialog SHARED src/nvdialog_version.c src/backend/nvdialog_win32.c src/backend/nvdialog_fallback.c src/nvdialog_main.c)
        message("Compiling a Windows library.")
else()
        add_library(nvdialog SHARED ${NVD_SOURCES})
        find_package(PkgConfig)
        if (PKG_CONFIG_FOUND)
                pkg_check_modules(GTK "gtk+-3.0")
                if (GTK_FOUND)    
                        target_link_libraries(nvdialog ${GTK_LIBRARIES})
                        add_definitions(${GTK_CFLAGS} ${GTK_CFLAGS_OTHER})
                endif()
        endif()

        message("Compiling a GNU/Linux library.")
endif()

set_target_properties(nvdialog PROPERTIES SOVERSION 0)
set_target_properties(nvdialog PROPERTIES VERSION ${PROJECT_VERSION})
target_include_directories(nvdialog PRIVATE include/)
# Required to find the system paths easier.
include(GNUInstallDirs)

# On Windows the installation procedure is a bit different
# so until we resolve this the library and the header have to
# be manually installed.
if (!WIN32_TARGET OR !WIN32)
        install(TARGETS nvdialog LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
        install(FILES include/nvdialog.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
endif()
