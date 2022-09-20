/*
 *  The MIT License (MIT)
 *
 *  Copyright (c) 2022 Aggelos Tselios
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

mod functions;

extern crate libloading;
use libloading::{Library, Symbol};
#[allow(unused)]
use std::ffi::*;
/*
 * The NvDialogContext is used to connect to the actual library
 * and provide symbols. You should use this to initialize the library.
*/
#[derive(Debug)]
/*
 * The NvDialogContext is used to connect to the actual library and provide
 * symbols. You should use this to call functions from the native library.
*/
pub struct NvDialogContext {
    bound: bool,
    errcode: u32,
    library: Library,
}

/*
 * The type of the dialog to use.
 * You can imagine this as the copy of NvdDialogType.
*/
#[derive(Debug)]
pub enum DialogType {
    SimpleDialog = 0xff,
    WarningDialog,
    ErrorDialog,
}

impl NvDialogContext {
    /* Creates a new NvDialogContext object and returns it. */
    pub fn new() -> Self {
        let library;

        unsafe {
            library = Library::new("/usr/lib/libnvdialog.so")
                .expect("Couldn't load the native library.");
        }
        Self {
            bound: false,
            errcode: 0,
            library,
        }
    }
    /*
     * Initializes NvDialog.
     * This is an important step. See the API reference for more information.
     * Skipping this may result in undefined behavior. Please ensure you call this
     * function.
     * TODO: Return Result on everything.
    */
    pub fn init(mut self, argv_0: &str) -> Self {
        let argv0 = format!("{}{}", argv_0, '\0');
        let init_fn: Symbol<unsafe extern "C" fn(*const i8) -> u32>;
        unsafe {
            init_fn = self.library.get(b"nvd_init").expect("Invalid library");
            init_fn(
                CStr::from_bytes_with_nul(argv0.as_str().as_bytes())
                    .unwrap()
                    .as_ptr(),
            );
        }
        self.bound = true;
        self.errcode = 0;

        self
    }

    /* Shows a simple message box with the title and message given. */
    pub fn message_box(&self, title: &str, message: &str, dialog_type: DialogType) {
        match dialog_type {
            DialogType::SimpleDialog => {
                functions::msgbox(&self.library, title, message);
            }
            DialogType::WarningDialog => {
                functions::warningbox(&self.library, title, message);
            }
            DialogType::ErrorDialog => {
                functions::errorbox(&self.library, title, message);
            }
        }
    }

    /* A function that can be used to show some information about your application. */
    pub fn about_dialog(&self, name: &str, contents: &str, license: &str, icon_name: Option<&str>) {
        let has_icon = icon_name.is_some();
        if has_icon {
            functions::about_dialog(
                &self.library,
                &format!("About {}", name),
                contents,
                license,
                Some(icon_name.unwrap()),
            );
        } else {
            functions::about_dialog(
                &self.library,
                &format!("About {}", name),
                contents,
                license,
                None,
            );
        }
    }
}
