extern crate nvdialog;
use nvdialog::error::Error::NVD_INTERNAL_ERROR;
use nvdialog::{DialogType::*, NvDialogContext};

fn main() {
    let mut argv_0: String = String::new();
    for (i, arg) in std::env::args().enumerate() {
        if i == 0 {
            argv_0 = arg
        } else {
            break;
        }
    }
    let ctx = NvDialogContext::new().init(&argv_0);
    if ctx.get_error() != 0 {
        println!("Error: {}", ctx.stringify_error(NVD_INTERNAL_ERROR));
        panic!("Library failure");
    }
    ctx.message_box(
        "Hello World!",
        "This is a dialog created with the Rust bindings of libnvdialog.\n
        Newlines and other common features are supported!
        ",
        ErrorDialog,
    ).expect("NvDialog failed to be used.");
}
