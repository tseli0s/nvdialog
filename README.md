
<div align="center">
        <h1>libnvdialog</h1>
        <img src="assets/logo.svg" width="256">
        <br>
        <h5>A cross-platform dialog library.</h5>
</div>

<br>
<code>libnvdialog</code> is a simple dialog box library written in C (Bindings for Rust also exist)
for multiple purposes such as games, app development, simple UI boxes for terminal apps or anything else. If you need something that doesn't require a bunch of setup this library is for you. <br>
<b>If you like this project, support it by recommending it and starring it. Thanks :)</b> <br>
<a href="https://androgr.github.io/libnvdialog">libnvdialog Website</a>
<br> <br>

# Backends
- **Adwaita Backend**\
A backend using `libadwaita` and Gtk4. Currently unsupported because it requires Gtk4 (see the Gtk3 backend below for more).\

- **Gtk3 Backend**\
Some older distributions do not have Adwaita / Gtk4 support yet. The Gtk3 backend can be used in such a situation. However Gtk3 is considered to be deprecated and will be replaced with `libadwaita` later in the library.

- **Win32 Backend**\
Windows-specific backend, used only for Windows compatibility.

- **Fallback Backend**\
This backend is only used if everything else fails. It outputs an error message to the console.

# Example
This is a simple cross-platform example of a simple message box greeting the user:
```c
#include <nvdialog.h>
#include <stdio.h>

int main(int argc, char **argv)
{
        /* Initializing the library. */
        nvd_init(argv[0]);

        /* Creating the dialog. */
        nvd_dialog_box_new(
                "Hello, world!",
                "Hello world ! This is a dialog box created using libnvdialog!",
                NVD_DIALOG_SIMPLE
        );
}
```
Yes, it's that simple ! The library is designed with simplicity in mind so it will not require anything else to work.

# Screenshots
<div align="center">
        <img src="assets/warning_scr.png" width="512"></img>
        <h5><i>Warning dialog using libnvdialog</i></h5>
<br>
<br>
<img src="assets/info_scr.png" width="512"></img>
        <h5><i>Info dialog using libnvdialog</i></h5>
<br>
<br>
<img src="assets/error_scr.png" width="512"></img>
        <h5><i>Error dialog using libnvdialog</i></h5>
</div>
<br>
<br>

# Installation
Make sure you have installed CMake before doing anything else ! The library can only be installed using CMake. See [CMake's website](https://cmake.org/) for more information.
- First, clone the repository:
```sh
$ git clone --depth=1 https://github.com/AndroGR/libnvdialog.git && cd libnvdialog/
```

- Compile the library:
```sh
$ mkdir build/ && cd build/
$ cmake ..
$ make -j`nproc`
```

- And install it on your system:
```sh
$ sudo make install -j`nproc`
```

# License
`nvdialog` is licensed under the MIT license. See [COPYING](./COPYING) for more.
