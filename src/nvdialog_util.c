/*
 *  The MIT License (MIT)
 *
 *  Copyright (c) 2024 Aggelos Tselios
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include "nvdialog_util.h"
#include "nvdialog_assert.h"
#include "nvdialog_error.h"
#include "nvdialog_macros.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <io.h>
#define access _access
#else
#include <unistd.h> // access()
#endif

static inline bool nvd_file_exists(const char* path) {
    return (access(path, 0) == 0);
}

/**
 * @brief Writes @ref size bytes to @ref ptr to ensure proper initialization.
 * @param ptr A pointer to the data structure where the NULL bytes will be written.
 * @param size The amount of NULL bytes to write before stopping.
 */
static void nvd_zero_memory(void* ptr, size_t size) {
    memset(ptr, 0, size);
}

#if defined (__linux__) || defined (__linux) || defined (__gnu_linux__)
static void nvd_read_os_release(NvdDistroInfo* info) {
    FILE *file = fopen("/etc/os-release", "r");
    NVD_ASSERT(file != NULL);

    char line[NVD_BUFFER_SIZE];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "VERSION_ID=")) {
            if (sscanf(line, "VERSION_ID=\"%ld", &info->version_m) == 1) {
                fclose(file);
                break;
            }
        }
    }
}
#endif /* __linux__ */

NvdProcessID nvd_create_process(void) {
    #if defined (unix) || defined(__APPLE__)
    return (NvdProcessID) fork();
    #else
    return (NvdProcessID) GetCurrentProcessId();
    #endif
}

/* 
 * For some explanation, here's my answer on StackOverflow:
 * https://stackoverflow.com/questions/75274925/is-there-a-way-to-find-out-if-i-am-running-inside-a-flatpak-appimage-or-another
 */
bool nvd_is_sandboxed(void) {
    #if defined(_WIN32) || defined(NVD_USE_COCOA)
    return false; // see documentation
    #else

    if (getenv("container")) {
        return true;
    } else if (getenv("APPIMAGE")) {
        return true;
    } else if (getenv("SNAP")) {
        return true;
    }
    return false;

    #endif
}

char** nvd_seperate_args(const char* str) {
    size_t count = 1;
    const char* ptr = str;
    while (*ptr != '\0') {
        if(*ptr == ';') {
            count++;
        }
        ptr++;
    }
    
    char* words_buffer = (char*)malloc(strlen(str) + 1);
    char** words = (char**)malloc((count + 1) * sizeof(char*));
    if (words_buffer == NULL || words == NULL) {
        free(words_buffer);
        free(words);
        return NULL;
    }
    
    int i = 0;
    ptr = str;
    words[i] = words_buffer;
    while (*ptr != '\0') {
        if (*ptr == ';') {
            *words_buffer = '\0';
            words_buffer++;
            i++;
            words[i] = words_buffer;
        } else {
            *words_buffer = *ptr;
            words_buffer++;
        }
        ptr++;
    }
    *words_buffer = '\0';
    i++;
    words[i] = NULL;
    
    return words;
}

#if defined(__linux) || defined (__linux__) || defined (__gnu_linux__)
NVD_INTERNAL_FUNCTION NvdDistroInfo nvd_get_distro_branch() {
    NvdDistroInfo info;
    nvd_zero_memory(&info, sizeof(NvdDistroInfo));

    #if !defined(__linux__) && !defined(__linux) && !defined (__gnu_linux__)
    /* Yes we don't have a pointer here so we can't return NULL, so let's just return a zeroed-out struct instead. */
    return info;
    #endif

    /* We call nvd_read_os_release in each block separately since we also support rolling release distros. */
    if (nvd_file_exists("/etc/debian_version")) {
        info.name = "Debian";
        nvd_read_os_release(&info);
    } else if (nvd_file_exists("/etc/pacman.conf")) {
        info.name = "Arch";
        info.version_m = -1; // Rolling release
        info.version_s = -1;
    } else if (nvd_file_exists("/etc/dnf/dnf.conf")) {
        info.name = "Fedora";
        nvd_read_os_release(&info);
    } else info.name = "Unknown";
    
    return info;
}

NVD_INTERNAL_FUNCTION char* nvd_get_libnotify_path() {
    size_t max_pathlen = strlen("/usr/lib/x86_64-linux-gnu/libnotify.so");
    char* buffer = malloc(max_pathlen + 16); // 16 byte padding

    NvdDistroInfo info = nvd_get_distro_branch();

    /* TODO: Please add more distribution checks here.*/
    if (strcmp(info.name, "Debian") == 0)
        strcpy(buffer, "/usr/lib/x86_64-linux-gnu/libnotify.so");
    else if (strcmp(info.name, "Arch") == 0)
        strcpy(buffer, "/usr/lib/libnotify.so");
    else
        strcpy(buffer, "/usr/lib/libnotify.so");

    return buffer;
}
#endif /* __linux__ */