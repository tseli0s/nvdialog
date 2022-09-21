<div align="center">
        <h1>nvdialog-rs</h1>
        <img src="../../assets/logo-new.svg" width="256">
        <br>
        <h5>Rust bindings for <code>libnvdialog.</code></h5>
</div>

<br>
This is a Rust library that provides a safe and simple interface to nvdialog in Rust. This is not a Rust-only library; It will still try to link into the host library and panic otherwise. There may be better libraries out there if that's what you're looking for.<br>
<br>
Do note that NvDialog will need to be preinstalled before using this library. If required, ship a build of NvDialog by yourself and install it at runtime.
<br>

# Installation
Add the following to your `Cargo.toml` file:
```toml
[dependencies]
nvdialog = "0.1.5"
```

# Documentation
You can find the documentation for this crate through the [crates.io link.](https://crates.io/).
Do note that documentation is only available since 0.1.5, since before that the main focus was shifted
towards the native (C) library.

# MSRV and NvDialog Compatibility
##### *(Minimum Rust version supported)*
| `nvdialog-rs` | `MSRV` | NvDialog version compatibility |
| --- | --- | --- |
| 0.1.0 | 1.35 | 0.1.0 |
| 0.1.3 | 1.35 | 0.1.3 |
| 0.1.5 | 1.35 | 0.1.3 |

# License
This library is licensed under the MIT License, see [COPYING](./COPYING) for more details.
There is a chance to relicense future versions of this library to Apache-2.0. If your code is incompatible, a dual license will be offered.


