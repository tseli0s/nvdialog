/*
 *  The MIT License (MIT)
 *
 *  Copyright (c) 2023 Aggelos Tselios
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
#include <stdbool.h>

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
    int count = 1;
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