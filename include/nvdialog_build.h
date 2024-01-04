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

/************************************************************************************
 * This file is NOT source code. It will just be used by Doxygen when
 * generating documentation for the "Building NvDialog" page. It won't be installed, it won't be
 * used within the library or by a user, and probably isn't of interest to anyone.
 ************************************************************************************/

/**
 * @page building BuildingNvDialog
 * @version v0.6.1
 * @author Aggelos Tselios
 * 
 * # Building NvDialog
 * This document will provide you with all the necessary information / documentation to build
 * NvDialog on your machine. These steps have been verified to work on all supported platforms,
 * thanks to usage of cross-platform tools.
 * 
 * You can also download prebuilt binaries of NvDialog at the [releases page](https://github.com/AndroGR/nvdialog/releases/).
 * This can be useful if you are looking to package NvDialog with your application.
 * 
 * @note NvDialog doesn't officially have support for a sandboxed environment due to filesystem restrictions. For more details see [the tracking issue](https://github.com/AndroGR/nvdialog/issues/36)
 * 
 * ## Dependencies
 * Before proceeding, download and install the following:
 * - [CMake](https://cmake.org)
 * - [ninja](https://ninja-build.org/)
 * - A C Compiler from these three: Clang, GCC or MSVC (Preferably GCC).
 * - If you want to generate the documentation locally: [doxygen](https://doxygen.nl)
 * 
 * ## 1. Downloading the source code.
 * Before continuing, you must acquire the source code somehow. How you will do that depends on what version you want
 * to use:
 * - The git development version is the one where all the development goes. You should avoid it unless you want early access to new features.
 * - The releases provide you with the source code of each release. They're recommended for stability.
 * - Optionally, you can also download a specific branch if you're looking for an unfinished feature.
 * 
 * Each one will be explained below seperately:
 * 
 * ### Git
 * Open a terminal, and `cd` to the directory you want to store the source code. Then type the following two commands:
 * ```sh
 * $ git clone --recursive --depth=1 https://github.com/AndroGR/nvdialog.git
 * $ cd nvdialog/
 * ```
 * 
 * > You can also have NvDialog as a submodule. Just use `git submodule add https://github.com/AndroGR/nvdialog.git` in your source code tree.
 * 
 * ## Releases
 * Go to https://github.com/AndroGR/nvdialog/releases/tag/v0.6.0 and download the source code as a zip file. Extract the
 * archive where you want to store the source code.
 * 
 * ## Specific git branch
 * Same as the git one, but you must change the second command to this:
 * ```sh
 * git clone --branch <branchname> --recursive https://github.com/AndroGR/nvdialog.git
 * ```
 * 
 * ## 2. Building
 * Go to the directory the source code is located. You must have files like `CMakeLists.txt`, `Makefile`, `CHANGELOG.md`
 * and others.
 * > Don't confuse the said directory with the directory named `src/`. Source code in this case means the entire NvDialog folder.
 * 
 * Then, generate the build files, necessary to build the source code:
 * ```sh
 * $ cmake . -B build/ -G "Ninja" -DCMAKE_BUILD_TYPE=Release
 * ```
 * 
 * > You can optionally tweak NvDialog's default settings using the `-D<var>=<value>` CMake flag.
 * 
 * Finally, building the source code is relatively simple:
 * ```sh
 * ninja
 * ```
 * The build takes at most 1 minute.
 * 
 * If you want to install NvDialog on your computer (You probably do), then run this command
 * as well:
 * 
 * ```sh
 * $ sudo ninja install # sudo may be omitted on Windows
 * ```
 * 
 * ## Older distros
 * For older Linux distros that don't have a recent enough version of CMake, there's a `Makefile` provided.
 * You can just run `make && sudo make install` and it should do the exact same thing.
 * 
 * ## Compile-time features:
 * This is a table of features that NvDialog supports enabling at compile time.
 * You can enable features (Or set them appropriately) using the `-D<feature>=<value>` cmake flag.
 * | Feature | Default | Description |
 * | --- | --- | --- |
 * | NVD_USE_GTK4 | OFF | Sets the Linux backend to use `libadwaita` |
 * | WIN32_TARGET | OFF | Builds a Windows library on Unix |
 * | NVDIALOG_MAXBUF | 4096 | Amount of bytes NvDialog will allocate by default (Strings for example) |
 * | NVD_BUILD_STATIC | OFF | Build NvDialog as a static library instead, that will be packaged with your executable |
 * | COCOA_TARGET | ON | Enable Cocoa (macOS) support (Does nothing on non-macOS platforms) |
 */