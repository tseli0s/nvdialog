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

use core::ptr::null_mut;
use libloading::*;
use std::ffi::CStr;
use std::ptr::null;

/*
 * WARNING:
 * This file contains alot of FFI function interfaces intended purely for internal use.
 * They are not intended to be used directly, or even exist as anything more than a bridge
 * for actual functions. If you wish to contribute, this is probably not where you want to.
 * If you do insist on reading this source code, be prepared for alot of "wrong ideas".
*/

fn symbol_fmt(s: &str) -> String {
    format!("{}{}", s, '\0')
}

pub(super) fn msgbox(library: &Library, title: &str, msg: &str) -> Result<(), crate::error::Error> {
    unsafe {
        let func: Symbol<unsafe extern "C" fn(*const i8, *const i8, u32) -> *mut libc::c_void> =
            library
                .get(symbol_fmt("nvd_dialog_box_new").as_bytes())
                .expect("Invalid library");
        let result = func(title.as_ptr() as *const i8, msg.as_ptr() as *const i8, 255);
        if result == null_mut() {
            Err(crate::error::Error::NVD_INTERNAL_ERROR)
        } else {
            Ok(())
        }
    }
}

pub(super) fn warningbox(
    library: &Library,
    title: &str,
    msg: &str,
) -> Result<(), crate::error::Error> {
    unsafe {
        let func: Symbol<unsafe extern "C" fn(*const i8, *const i8, u32) -> *mut libc::c_void> =
            library
                .get(symbol_fmt("nvd_dialog_box_new").as_bytes())
                .expect("Invalid library");
        if func(title.as_ptr() as *const i8, msg.as_ptr() as *const i8, 256) == null_mut() {
            Err(crate::error::Error::NVD_INTERNAL_ERROR)
        } else {
            Ok(())
        }
    }
}

pub(super) fn errorbox(
    library: &Library,
    title: &str,
    msg: &str,
) -> Result<(), crate::error::Error> {
    unsafe {
        let func: Symbol<unsafe extern "C" fn(*const i8, *const i8, u32) -> *mut libc::c_void> =
            library
                .get(symbol_fmt("nvd_dialog_box_new").as_bytes())
                .expect("Invalid library");
        if func(title.as_ptr() as *const i8, msg.as_ptr() as *const i8, 257) == null_mut() {
            Err(crate::error::Error::NVD_INTERNAL_ERROR)
        } else {
            Ok(())
        }
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

pub(super) fn get_error(library: &Library) -> i32 {
    unsafe {
        let fnc: Symbol<unsafe extern "C" fn() -> std::os::raw::c_int> =
            library.get(b"nvd_get_error").expect("Invalid library.");

        fnc()
    }
}

pub(super) fn stringify_error(library: &Library, error: crate::error::Error) -> String {
    unsafe {
        let fnc: Symbol<unsafe extern "C" fn(crate::error::Error) -> *const i8> =
            library.get(b"nvd_get_error").expect("Invalid library.");

        String::from(CStr::from_ptr(fnc(error)).to_str().unwrap())
    }
}
