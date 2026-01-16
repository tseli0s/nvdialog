# CMake Build Script for libnvdialog.
# This file is part of libnvdialog and is released under the MIT license.

cmake_minimum_required(VERSION 3.19)
project(libnvdialog VERSION 0.10.1 LANGUAGES C DESCRIPTION "A simple and minimal dialog library, with cross-platform support")

option(CROSS_COMPILE_FOR_WIN32 "Cross-compile the library for Windows from Linux." OFF)
option(NVD_BUILD_STATIC "Build NvDialog as a static library." ON)
option(NVD_GENERATE_DOCS "Generate documentation for NvDialog. Requires doxygen to be installed" OFF) # Off by default because doxygen may not be available
option(NVD_USE_GNUSTEP "Use the GNUstep+Cocoa backend on generation. Only intended for testing." OFF)
option(NVD_IMAGE_SUPPORT "Add support for images through nvdialog, only disable this if you're building nvdialog statically!" ON)

set(CMAKE_C_STANDARD 11)
add_compile_definitions(NVDIALOG_MAXBUF=4096 NVD_EXPORT_SYMBOLS)
if (NVD_IMAGE_SUPPORT)
    add_compile_definitions(_NVD_SUPPORT_IMAGES)
endif()

if (NVD_USE_GTK4)
    message(WARNING "**IMPORTANT** The build system detected that you are trying to build this library with the Gtk4/libadwaita backend. This backend is being deprecated as of version v0.10. For future-proofness, resort to the default gtk backend instead. See PR #59 on the repository for further details.")
    message("-- If you are building for Windows/macOS, you can ignore the warning above.")
endif()

if(APPLE OR NVD_USE_GNUSTEP)
    enable_language(OBJC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-objc-arc")
elseif(CROSS_COMPILE_FOR_WIN32)
    set(CMAKE_C_COMPILER /usr/bin/i686-w64-mingw32-gcc)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-stack-protector -Wno-unused-parameter -Wconversion -Werror=format -Werror=format-security -Winline -Wall -Wextra")
elseif(MSVC)
    message(WARNING "MSVC is experimental; prefer GCC/Clang.")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /Wall")
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()


if (NOT MSVC)
	add_compile_options(-Wall -Wextra)
endif()

set(NVD_HEADERS
    include/nvdialog_dialog.h
    include/nvdialog_notification.h
    include/nvdialog_core.h
    include/nvdialog_capab.h
    include/nvdialog_types.h
    include/nvdialog_error.h
    include/nvdialog_platform.h
    include/nvdialog_image.h
    include/nvdialog_string.h
    include/nvdialog.h)

set(NVD_EXTRA_HEADERS
    include/dialogs/nvdialog_file_dialog.h
    include/dialogs/nvdialog_about_dialog.h
    include/dialogs/nvdialog_dialog_box.h
    include/dialogs/nvdialog_input_box.h)

set(NVD_COMMON_SOURCES
    src/nvdialog_error.c
    src/nvdialog_image.c
    src/nvdialog_util.c
    src/nvdialog_capab.c
    src/nvdialog_version.c
    src/nvdialog_init.c
    src/nvdialog_string.c
    src/nvdialog_main.c)

if(WIN32 OR CROSS_COMPILE_FOR_WIN32)
    set(NVD_SOURCES
        src/backend/win32/nvdialog_about_dialog.c
        src/backend/win32/nvdialog_dialog_box.c
        src/backend/win32/nvdialog_question_dialog.c
        src/backend/win32/nvdialog_file_dialog.c
        src/backend/win32/nvdialog_notification.c
        src/backend/win32/nvdialog_input_box.c
        ${NVD_COMMON_SOURCES})
elseif(APPLE OR NVD_USE_GNUSTEP)
    set(NVD_SOURCES
        src/backend/cocoa/nvdialog_dialog_box.m
        src/backend/cocoa/nvdialog_file_dialog.m
        src/backend/cocoa/nvdialog_input_box.m
        src/backend/cocoa/nvdialog_question_dialog.m
        src/backend/cocoa/nvdialog_notification.m
        src/backend/cocoa/nvdialog_about_dialog.m
        src/backend/cocoa/nvdialog_cocoa_init.m
        ${NVD_COMMON_SOURCES})
    add_compile_definitions(NVD_USE_COCOA=1)
else()
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK REQUIRED gtk+-3.0)
    pkg_check_modules(DBUS REQUIRED dbus-1)
    if(NVD_USE_GTK4)
        set(NVD_SOURCES
            src/backend/adw/nvdialog_about_dialog.c
            src/backend/adw/nvdialog_file_dialog.c
            src/backend/adw/nvdialog_dialog_box.c
            src/backend/adw/nvdialog_question_dialog.c
            src/backend/adw/nvdialog_notification.c

            # Since v0.10, the entire adw backend will simply call the equivalent gtk backend
            # functions. This is to keep preexisting code working but no longer depend on libadwaita
            # and having to keep up with all the changes.

            src/backend/gtk/nvdialog_about_dialog.c
            src/backend/gtk/nvdialog_file_dialog.c
            src/backend/gtk/nvdialog_dialog_box.c
            src/backend/gtk/nvdialog_question_dialog.c
            src/backend/gtk/nvdialog_notification.c
            src/backend/gtk/nvdialog_input_dialog.c

            ${NVD_COMMON_SOURCES})
    else()
        set(NVD_SOURCES
            src/backend/gtk/nvdialog_about_dialog.c
            src/backend/gtk/nvdialog_file_dialog.c
            src/backend/gtk/nvdialog_dialog_box.c
            src/backend/gtk/nvdialog_question_dialog.c
            src/backend/gtk/nvdialog_notification.c
            src/backend/gtk/nvdialog_input_dialog.c
            ${NVD_COMMON_SOURCES})
    endif()
    add_definitions(${GTK_CFLAGS} ${GTK_CFLAGS_OTHER})
endif()

if(NVD_BUILD_STATIC)
    add_library(nvdialog STATIC ${NVD_SOURCES})
    add_compile_definitions(NVD_STATIC_LINKAGE)
else()
    add_library(nvdialog SHARED ${NVD_SOURCES})
endif()

target_include_directories(nvdialog PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/impl/ ${CMAKE_CURRENT_SOURCE_DIR}/vendor)

if(APPLE)
    target_link_libraries(nvdialog
        "-framework AppKit"
        "-framework Cocoa"
        "-framework Foundation"
        "-framework UserNotifications"
    )
elseif(NVD_USE_GNUSTEP)
    message(WARNING "You are building with GNUstep. This is intended for development only -- Stability may suffer.")
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GNUSTEP REQUIRED gnustep-base gnustep-gui)

    include_directories(${GNUSTEP_INCLUDE_DIRS})
    link_directories(${GNUSTEP_LIBRARY_DIRS})

    add_compile_definitions(_NVD_USE_GNUSTEP=1)
    target_link_libraries(nvdialog gnustep-base gnustep-gui objc m)
elseif(CROSS_COMPILE_FOR_WIN32 OR WIN32)
    target_link_libraries(nvdialog comdlg32 shell32 user32 gdi32 ole32)
elseif(UNIX AND NOT APPLE)
    target_link_libraries(nvdialog ${GTK_LIBRARIES} ${DBUS_LIBRARIES})
    if (UNIX AND NOT LINUX)
        message(WARNING "Building on a Unix-like OS that is not GNU/Linux has not been verified to work as reliably, results may vary!")
    endif()
endif()

set_target_properties(nvdialog PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION 3)
target_include_directories(nvdialog PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if (NVD_GENERATE_DOCS)
    set(NVD_DOXYFILE ${CMAKE_SOURCE_DIR}/Doxyfile)
    set(NVD_DOC_OUTPUT ${CMAKE_SOURCE_DIR}/docs/html/index.html)
    find_package(Doxygen REQUIRED)
    
    add_custom_command(
        OUTPUT ${NVD_DOC_OUTPUT}
        COMMAND ${DOXYGEN_EXECUTABLE} ${NVD_DOXYFILE}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Generating Doxygen documentation"
        VERBATIM
    )
    add_custom_target(nvd_docs ALL DEPENDS ${NVD_DOC_OUTPUT})
endif()

include(GNUInstallDirs)
install(TARGETS nvdialog LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES ${NVD_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/nvdialog/)
install(FILES ${NVD_EXTRA_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/nvdialog/dialogs)

find_package(PkgConfig)
if(PKG_CONFIG_FOUND)
    message(STATUS "pkg-config found, generating .pc file")
    configure_file(pkg-config/nvdialog.pc.in nvdialog.pc @ONLY)
    install(FILES ${CMAKE_BINARY_DIR}/nvdialog.pc DESTINATION ${CMAKE_INSTALL_PREFIX}/share/pkgconfig)
endif()

enable_testing()
set(NVDIALOG_TESTS init dialogs multithreading aboutdlg question notification)
foreach(test_exe ${NVDIALOG_TESTS})
    add_executable(nvdialog_${test_exe}_test tests/test_${test_exe}.c)
    target_compile_definitions(nvdialog_${test_exe}_test PRIVATE NVDIALOG_TESTING)
    target_link_libraries(nvdialog_${test_exe}_test nvdialog)
    target_include_directories(nvdialog_${test_exe}_test PUBLIC ${CMAKE_SOURCE_DIR}/include/)
    add_test(NAME nvdialog_${test_exe}_test COMMAND $<TARGET_FILE:nvdialog_${test_exe}_test>)
endforeach()
