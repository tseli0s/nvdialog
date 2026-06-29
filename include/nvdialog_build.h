/************************************************************************************
 * This file is NOT source code. It will just be used by Doxygen when
 * generating documentation for the "Building NvDialog" page. It won't be
 * installed, it won't be used within the library or by a user, and probably
 * isn't of interest to anyone.
 ************************************************************************************/

/**
 * @page building Building NvDialog
 * @version v0.10.0
 * @author Aggelos Tselios
 *
 * # Building NvDialog
 * This document will provide you with all the necessary information /
 * documentation to build NvDialog on your machine. These steps have been
 * verified to work on all supported platforms, thanks to usage of
 * cross-platform tools.
 *
 * You can also download prebuilt binaries of NvDialog at the [releases
 * page](https://github.com/tseli0s/nvdialog/releases/). This can be useful if
 * you are looking to package NvDialog with your application without extra compilation.
 *
 * ## Dependencies
 * Before proceeding, download and install the following:
 * - [CMake](https://cmake.org)
 * - [ninja](https://ninja-build.org/)
 * - A C compiler (e.g. gcc or clang)
 * - If you want to generate the documentation locally:
 * [doxygen](https://doxygen.nl)
 *
 * ## 1. Downloading the source code.
 * Before continuing, you must acquire the source code somehow. How you will do
 * that depends on what version you want to use:
 * - The git development version is the one where all the development goes. You
 * should avoid it unless you want early access to new features, since many things may stay broken there for
 * some time
 * - The releases provide you with the source code of each release. They're
 * recommended for stability and future-proofness, as the final releases usually work
 * with older versions.
 * - Optionally, you can also download a specific branch if you're looking for
 * an unfinished feature.
 *
 * Each one will be explained below seperately:
 *
 * ### Git
 * Open a terminal, and `cd` to the directory you want to store the source code.
 * Then type the following two commands:
 * ```sh
 * $ git clone --recursive --depth=1 https://github.com/tseli0s/nvdialog.git
 * $ cd nvdialog/
 * ```
 *
 * > You can also have NvDialog as a submodule. Just use `git submodule add
 * https://github.com/tseli0s/nvdialog.git` in your source code tree.
 *
 * ## Releases
 * Go to https://github.com/tseli0s/nvdialog/releases/latest and download the
 * source code as a zip file. Extract the archive where you want to store the
 * source code.
 *
 * ## Specific git branch
 * Same as the git one, but you must change the second command to this:
 * ```sh
 * git clone --branch <branchname> --recursive
 * https://github.com/tseli0s/nvdialog.git
 * ```
 *
 * ## 2. Building
 * Go to the directory the source code is located. You must have files like
 * `CMakeLists.txt`, `Makefile`, `CHANGELOG.md` and others. > Don't confuse the
 * said directory with the directory named `src/`. Source code in this case
 * means the entire NvDialog folder.
 *
 * Then, generate the build files, necessary to build the source code:
 * ```sh
 * $ cmake . -B build/ -G "Ninja" -DCMAKE_BUILD_TYPE=Release
 * ```
 *
 * > You can optionally tweak NvDialog's default settings using the
 * `-D<var>=<value>` CMake flag.
 *
 * Finally, building the source code is relatively simple:
 * ```sh
 * ninja
 * ```
 * The build takes at most 1 minute.
 *
 * If you want to install NvDialog on your computer (You probably do), then run
 * this command as well:
 *
 * ```sh
 * $ sudo ninja install # sudo may be omitted on Windows and macOS
 * ```
 *
 * ## Older distros
 * For older Linux distros that don't have a recent enough version of CMake,
 * there's a `Makefile` provided. You can just run `make && sudo make install`
 * and it should do the exact same thing. The downside is that the Makefile
 * doesn't support any options - You will have to modify it manually to tweak
 * any build time functionality.
 *
 * ## Compile-time features:
 * This is a table of features that NvDialog supports enabling at compile time.
 * You can enable features (Or set them appropriately) using the
 * `-D<feature>=<value>` cmake flag.
 * | Feature | Default | Description |
 * | --- | --- | --- |
 * | CROSS_COMPILE_FOR_WIN32 | OFF | Cross compile from a Unix system for a Windows host |
 * | NVD_BUILD_STATIC | ON | Build NvDialog as a static library instead, that will be packaged with your executable |
 * | NVD_GENERATE_DOCS | OFF | Generate the documentation pages along with the source code (Requires doxygen) |
 * | NVD_IMAGE_SUPPORT | ON | Include support for images in the library. |
 * | NVD_USE_GNUSTEP | OFF | Use the GNUstep+Cocoa backend if available on non-macOS platforms. Experimental. |
 */
