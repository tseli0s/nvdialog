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
 * generating documentation for a tutorial page. It won't be installed, it won't be
 * used within the library or by a user, and probably isn't of interest to anyone.
 ************************************************************************************/

#define __nvd_tutorial

/**
 * @page NvDialog Tutorial
 * @version v0.6.1
 * @author Aggelos Tselios

 * # NvDialog Tutorial
 * This page provides a simple tutorial of the NvDialog library. For more information about the
 * library itself, see <b>https://androgr.github.io/nv.dialog</b>.
 * Proper documentation of the API used in this tutorial is also available in the documentation.
 * This tutorial assumes you have already installed NvDialog in your system. If not, visit the [GitHub Repo](https://github.com/AndroGR/nvdialog/#installation).
 * NvDialog is compiler and platform independent, so this tutorial should work as expected on all platforms.
 * # 1. Creating our environment.
 * <b>Skip this step if you aren't interested in the setup.</b>
 * Create a new file named `main.c` and add the following to it:
 * @code
 * #include <nvdialog/nvdialog.h>
 *
 * int main(int argc, char **argv) {
 * 
 * }
 * @endcode
 * This snippet contains a barebones C program which includes NvDialog. You can try compiling this
 * to verify that the headers can be found at compile time.
 * @note Remember that in some platforms headers are installed in non-standard places by CMake. If that's the
 * case, you will have to manually instruct the compiler to find the headers.
 * # 2. Creating a basic dialog box.
 * A dialog box is the simplest and most straightforward feature of NvDialog: It shows a dialog
 * with some parameters given. You will mainly use this for error messages (Although it can be used
 * for literally anything, see @ref NvdDialogType ).
 *
 * To get started, we first need to initialize NvDialog. This can be done with a single call:
 * > Initialization is mainly required by the backends. Each backend is often required to be initialized first.
 * @code
 * if (nvd_init(argv[0]) != 0) { return -1; }
 * @endcode
 * Go to your main function, and create a new dialog box object. The title and the message need to be
 * a regular NULL terminated C string. For the sake of simplicity we will create them in seperate variables:
 * @code
 * const char *title = "Hello NvDialog!";
 * const char *message = "This dialog box was created with NvDialog.";
 *
 * NvdDialogBox *dialog = nvd_dialog_box_new(title, message, NVD_DIALOG_SIMPLE);
 * @endcode
 * @ref nvd_dialog_box_new will return NULL on failure, so you may want to handle that too.
 * # 3. Showing the dialog.
 * Before @version v0.3.0, creating and showing the dialog was a single call. So the above snippet
 * would show us the dialog directly, without any extra calls.
 * This changed because on some platforms (Especially slow ones) caused serious issues that could halt
 * the thread for 1-2 seconds while creating the dialog! So these have been seperated since.
 * Now, we will also have to call @ref nvd_show_dialog :
 * @code
 * nvd_show_dialog(dialog);
 * @endcode
 * The function takes a pointer to the dialog we want to show. For more information read the documentation
 * by clicking the function.
 * # 4. Cleanup and finally compiling.
 * Now, we are technically done. However, we have caused a memory leak here because after all, the
 * @ref NvdDialogBox type like most others is heap-allocated! Which means we need to `free()` it.
 * Calling `free()` directly though will cause undefined behavior. So instead, we will use a special
 * function provided by NvDialog, which frees most types. That function is called @ref nvd_free_object .
 * @code
 * nvd_free_object(dialog);
 * // Not required but let's have it here to indicate success.
 * return 0;
 * @endcode
 * Your final source file should look like this:
 * @code
   #include <nvdialog/nvdialog.h>

   int main(int argc, char **argv) {
        if (nvd_init(argv[0]) != 0) return -1;

        const char *title = "Hello NvDialog!";
        const char *message = "This dialog box was created with NvDialog.";
        NvdDialogBox *dialog = nvd_dialog_box_new(title, message, NVD_DIALOG_SIMPLE);

        nvd_show_dialog(dialog);
        nvd_free_object(dialog);
        return 0;
   }
 * @endcode
 * <b>Now let's compile it:</b>
 * @note Each compiler has different options for the same thing. In this case, I am using GCC 12.1
 * on Arch Linux.
 *
 * On the terminal, go to the directory where your source file is located (Using `cd`).
 * Then run the following command to compile your file:
 * ```sh
 * $ gcc \ # Our compiler
 * $ main.c \ # Your file
 * $ -l nvdialog \ # Link with the NvDialog library
 * $ -o nvdialog-tutorial \ # Executable filename
 * ```
 * And now running it should give you a dialog box.
 * That's all you need to get started. For other dialogs to use, take a look at the
 * following types:
 * - @ref NvdQuestionBox
 * - @ref NvdFileDialog
 * - @ref NvdAboutDialog
 */