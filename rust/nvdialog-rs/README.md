<div align="center">
        <h1>nvdialog-rs</h1>
        <img src="../../assets/logo.svg" width="256">
        <br>
        <h5>Rust bindings for <code>libnvdialog.</code></h5>
</div>

<br>
This is a Rust library that provides a safe and simple interface to nvdialog in Rust. This is not a Rust-only library; It will still try to link into the host library and panic otherwise. There may be better libraries out there if that's what you're looking for.<br>
<br>
<br> <br>

# Installation
Add the following to your `Cargo.toml` file:
```toml
[dependencies]
nvdialog = "0.1.0"
```
<br></br>
# Simple example in Rust:
```rust
/* Importing the library */
extern crate nvdialog;
use nvdialog::NvDialogContext;

fn main() {
        /* Initializing the library */
        let nvd_dialog_ctx = NvdialogContext::new().init();

        /* And creating the dialog */
        nvd_dialog_ctx.messagebox(
                "Hello world from Rust !",
                "This is a simple example in Rust using the nvdialog crate."
        )
}
```


