extern crate nvdialog;
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
    ctx.message_box(
        "Hello World!",
        "This is a dialog created with the Rust bindings of libnvdialog.\n
        Newlines and other common features are supported!
        ",
        ErrorDialog,
    )
}
