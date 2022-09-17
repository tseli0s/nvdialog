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

use libloading::*;
use std::ptr::{null, null_mut};

fn symbol_fmt(s: &str) -> String {
    format!("{}{}", s, '\0')
}

pub(super) fn msgbox(library: &Library, title: &str, msg: &str) {
    unsafe {
        let func: Symbol<unsafe extern "C" fn(*const i8, *const i8, u32) -> *mut libc::c_void> =
            library
                .get(symbol_fmt("nvd_dialog_box_new").as_bytes())
                .expect("Invalid library");
        func(title.as_ptr() as *const i8, msg.as_ptr() as *const i8, 255);
    }
}

pub(super) fn warningbox(library: &Library, title: &str, msg: &str) {
    unsafe {
        let func: Symbol<unsafe extern "C" fn(*const i8, *const i8, u32) -> *mut libc::c_void> =
            library
                .get(symbol_fmt("nvd_dialog_box_new").as_bytes())
                .expect("Invalid library");
        func(title.as_ptr() as *const i8, msg.as_ptr() as *const i8, 256);
    }
}

pub(super) fn errorbox(library: &Library, title: &str, msg: &str) {
    unsafe {
        let func: Symbol<unsafe extern "C" fn(*const i8, *const i8, u32) -> *mut libc::c_void> =
            library
                .get(symbol_fmt("nvd_dialog_box_new").as_bytes())
                .expect("Invalid library");
        func(title.as_ptr() as *const i8, msg.as_ptr() as *const i8, 257);
    }
}

pub(super) fn about_dialog(
    library: &Library,
    title: &str,
    content: &str,
    license: &str,
    icon: Option<&str>,
) {
    unsafe {
        let func: Symbol<
            unsafe extern "C" fn(*const i8, *const i8, *const i8, *const i8) -> *mut libc::c_void,
        > = library
            .get(symbol_fmt("nvd_about_dialog_new").as_bytes())
            .expect("Invalid library");

        let used_icon: *const i8;
        let has_icon = icon.is_some();
        if has_icon {
            used_icon = icon.unwrap().as_ptr() as *const i8;
        } else {
            used_icon = null();
        }
        func(
            title.as_ptr() as *const i8,
            content.as_ptr() as *const i8,
            license.as_ptr() as *const i8,
            used_icon,
        );
    }
}
