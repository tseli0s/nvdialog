#!/bin/bash

#
#     The MIT License (MIT)
#     Copyright (c) 2022 Aggelos Tselios
#     This file is part of NvDialog.
#
#  Permission is hereby granted, free of charge, to any person obtaining a copy
#  of this software and associated documentation files (the "Software"), to
#  deal in the Software without restriction, including without limitation the
#  rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
#  sell copies of the Software, and to permit persons to whom the Software is
#  furnished to do so, subject to the following conditions:
#
#  The above copyright notice and this permission notice shall be included in
#  all copies or substantial portions of the Software.
#
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
# IN THE SOFTWARE.

# This script is used to generate a prebuilt copy of NvDialog for a variety
# of platforms. It can only be ran on Linux (Since it's a shell script).
# For help, pass --help as an argument.

OUTPUT_DIR="../../prebuilt/"
BUILD_FIRST=0 # Set to 1 if --build-first is specified
PLATFORMID=Windows

usage() {
        echo "Usage: $0 [ Arguments ]"
        echo "Arguments available: "
        echo ""
        echo "--output-directory <directory> | Where to put the generated files."
        echo "--help                         | Print this message and exit."
        echo "--build-first                  | (Re)build NvDialog before generating the files."
        echo "--platform <Platform ID>       | Set which platform to build for."
}

if [[ -z "$1" ]]; then
        echo "Please specify an action."
        usage
        exit -1
else
        while [[ $# -gt 0 ]]; do
                case "$1" in
                --output-directory)
                        if [[ -z "$2" ]]; then
                                echo "Error: --output-directory needs an argument."
                                exit 22
                        fi

                        OUTPUT_DIR="$2"
                        shift
                        ;;
                --build-first)
                        BUILD_FIRST=1
                        shift
                        ;;
                --platform)
                        echo "Error: Currently only Linux is supported."
                        exit 1
                        ;;
                --help)
                        usage
                        exit 0
                        ;;
                *)
                        usage
                        exit 22
                esac
                shift
        done

        [[ -d $OUTPUT_DIR ]] || mkdir $OUTPUT_DIR && cd "$OUTPUT_DIR"

        if [[ $BUILD_FIRST -eq 1 ]]; then
                [[ -d build/ ]] || mkdir build && cd build/
                echo "Currently at directory $(pwd)"
                cmake -S ../../ -B .               \
                        -DNVD_USE_GTK4=ON          \
                        -DNVD_BUILD_STATIC=OFF     \
                        -DNVDIALOG_MAXBUF=4096     \
                        -G "Ninja"                 \
                        -DWIN32_TARGET=OFF         \
                        -DCMAKE_BUILD_TYPE=Release || exit 4

                cmake --build .
                cd ..

                cp build/libnvdialog.so.* .
                cp ../include/ . -r
                cp ../COPYING  .
                cp ../assets/README.txt .

                zip prebuilt.zip libnvdialog.so.* include/*/* COPYING README.txt
        fi

        echo "  -- Finished."
fi

exit 0