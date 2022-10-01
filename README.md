<div align="center">
        <h1>libnvdialog</h1>
        <img src="assets/logo-new.svg" width="244">
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
A backend using Gtk4 and `libadwaita`. Currently experimental, however it is expected to be ported to stable by 0.2.0. Also note, this backend makes use of hardware acceleration, which sometimes breaks games in Wayland.

- **Gtk3 Backend**\
Some older distributions do not have Adwaita / Gtk4 support yet. The Gtk3 backend can be used in such a situation. However Gtk3 is considered to be deprecated and will be replaced with `libadwaita` later in the library. This backend will be replaced with Qt6 later.

- **Win32 Backend**\
Windows-specific backend, used only for Windows compatibility. This backend is mainly tested on GNU/Linux with `wine`, and so some bugs may not be detected. Open an issue if that's the case.

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
        <img src="assets/warning_scr.png"></img>
        <h5><i>Warning dialog using libnvdialog</i></h5>
<img src="assets/info_scr.png"></img>
        <h5><i>Info dialog using libnvdialog</i></h5>
<img src="assets/error_scr.png"></img>
        <h5><i>Error dialog using libnvdialog</i></h5>
</div>

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
$ cmake --build .
```

- And install it on your system:
```sh
$ sudo cmake --install .
```

# Installing on Arch Linux
###### *TODO: Upload the library to the AUR.*
For Arch Linux and derivatives, a `PKGBUILD` is provided to build the library as a package. It is recommended to use it this way to allow uninstalling the library easily.\
To install the library as an Arch Linux package, enter the following commands:

**Download `git`** (Required to download the source code)
```bash
$ sudo pacman -S git
```
**Clone the repository (To download the source code)**
```bash
$ git clone --depth=1 https://github.com/AndroGR/nvdialog.git
$ cd nvdialog/
```
**Build the package:**
```bash
$ makepkg --clean --install
```

# License
`nvdialog` is licensed under the MIT license. See [COPYING](./COPYING) for more.
All contributions made to the library are assumed to be licensed under the MIT license as well. However, you may specify a different license if you wish.