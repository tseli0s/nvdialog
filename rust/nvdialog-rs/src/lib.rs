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
use libloading::{
        Library,
        Symbol,
};
#[allow(unused)]
use std::ffi::*;
/*
 * The NvDialogContext is used to connect to the actual library
 * and provide symbols. You should use this to initialize the library.
*/
#[derive(Debug)]
pub struct NvDialogContext {
        bound: bool,
        errcode: u32,
        library: Library,
}

impl NvDialogContext {
        /* Creates a new NvDialogContext object and returns it. */
        pub fn new() -> Self {
                let library;

                unsafe {
                        library = Library::new("/usr/lib/libnvdialog.so.0.1.0")
                        .expect("Couldn't load the native library.");
                }
                Self {
                        bound: false,
                        errcode: 0,
                        library
                }
        }
        /* Initializes nvdialog. This is nvd_init() but in Rust. */
        pub fn init(mut self) -> Self {
                let init_fn: Symbol<unsafe extern "C" fn(*const i8) -> u32>;
                unsafe {
                        init_fn = self.library.get(b"init").expect("Invalid library.");
                        init_fn(
                                CStr::from_bytes_with_nul(
                                        b"hello-world"
                                ).unwrap().as_ptr()
                        );
                }
                self.bound = true;
                self.errcode = 0;

                self
        }

        pub fn message_box(&self, title: &str, message: &str) {
                todo!()
        }
}