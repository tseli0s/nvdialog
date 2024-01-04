<div align="center">
        <img src="assets/logo.svg" width="244">
        <h1>NvDialog</h1>
        <a href="#example">Examples</a> | 
        <a href="#screenshots">Screenshots</a> |
        <a href="#installation">Installing</a> |
        <a href="https://github.com/AndroGR/nvdialog/releases">Releases</a>
        <h5><b>A simple, cross-platform dialog box library.</b></h5>
<code>libnvdialog</code> is a simple dialog box library written in C
for multiple purposes such as games, app development, simple UI boxes for terminal apps or pretty much anything else. NvDialog uses the host's UI library (eg. <a href="https://gtk.org">Gtk3 / Gtk4</a> on Linux and other Unix like OSes, <a href="https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/CocoaFundamentals/WhatIsCocoa/WhatIsCocoa.html">the Cocoa API</a> on MacOS X or the <a href="https://learn.microsoft.com/en-us/windows/win32/apiindex/windows-api-list">WinAPI</a> for Windows) to achieve a look and feel that follows the system theme and design guidelines.
<br>
<br>
<img src="https://img.shields.io/github/license/tseli0s/nvdialog?color=blue&label=License">
<img src="https://img.shields.io/github/issues/tseli0s/nvdialog">
<img src="https://img.shields.io/github/commits-since/tseli0s/nvdialog/v0.6.1?label=Commits%20since%200.6.1&logo=git">
<br>
<img src="https://img.shields.io/github/actions/workflow/status/AndroGR/nvdialog/x86_64-pc-linux-gnu.yml?label=Ubuntu">
<img src="https://img.shields.io/github/actions/workflow/status/AndroGR/nvdialog/x86_64-apple-darwin.yml?branch=master&label=MacOS%20X&logo=github">
<img src="https://img.shields.io/github/actions/workflow/status/AndroGR/nvdialog/i686-pc-windows-msvc.yml?branch=master&label=Windows%2010&logo=github">
<br> <br>
<h6><i>This project is in immediate need of macOS-based contributors for the Cocoa backend. If you use this library consider contributing to support it.</i></h6>
</div>

# Features
- Simple, high level C API with low overhead (See [examples/](./examples/)).
- 100% guaranteed native looking dialogs.
- MIT Licensed.
- Cross-compiler (Actively tested with `gcc`, `clang` and MSVC).
- Supports most desktop platforms through 4 different implementations (Backends).
- Legacy version support (See [OS Versions Supported](#os-versions-supported))

# Backends
- **Gtk3 Backend**\
The most maintained backend, used mainly for GNU/Linux distributions (And FreeBSD). It is based off Gtk3 and has been the primary focus since this library was started.

- **Adwaita Backend**\
The Adwaita backend is more experimental and overall you can expect some bugs with it. However it provides
better integration with Linux distributions that are based on the GNOME ecosystem. Do note that sometimes
this backend can break games on Wayland due to hardware acceleration.

- **Sandbox Backend**\
The sandbox backend is used in place of the other backends when the process is under some kind of sandbox (Flatpak, AppImage, etc). It is mostly identical to the Gtk3 one but differs slightly in the implementation. This one is chosen automatically if enabled at compile time.

- **Cocoa Backend**\
The Cocoa backend was recently added to NvDialog for MacOS X support. It is written in Objective-C for better integration with the OS, and is still in the experimental stage. Please report any bugs or features that need to be fixed / implemented.

- **Win32 Backend**\
Windows-specific backend, used only for Windows compatibility. This backend is mainly tested on GNU/Linux with `wine`, and so some bugs may not be detected. Open an issue if that's the case.

# Example
This is a simple cross-platform example of a simple message box greeting the user:
```c
#include <stdlib.h>
#include <nvdialog/nvdialog.h>

int main(int argc, char **argv)
{
        if (nvd_init(argv[0]) != 0) {
                puts("Failed to initialize NvDialog.\n");
                exit(EXIT_FAILURE);
        }

        NvdDialogBox* dialog = nvd_dialog_box_new(
                "Hello, world!", // Title of the dialog
                "Hello world ! This is a dialog box created using libnvdialog!", // Message of the dialog
                NVD_DIALOG_SIMPLE // What is the dialog representing? (Eg a warning). In this
                                  // case, it represents a simple dialog with no context.
        );

        nvd_show_dialog(dialog);
        nvd_free_object(dialog);
        return 0;
}
```

# Screenshots
<div>
        <h4><b>"About application" dialog.</b></h4>
        <img src="assets/about-dialog-scr.png"></img>
        <h4><b>Dialog box with a warning.</b></h4>
        <img src="assets/dialog-scr.png"></img>
        <h4><b>Question dialog box</b></h4>
        <img src="assets/question-scr.png"></img>
</div>

# Installation
Make sure you have installed [CMake](https://cmake.org) before doing anything else ! The library can only be installed using CMake. See [CMake's website](https://cmake.org/) for more information.
- First, download the source code in your preferred way. The [Releases](https://github.com/AndroGR/nvdialog/releases/) are recommended if you are looking for stability, but you can also optionally compile from the `master` branch directly, by cloning the source code.
- Install dependencies (This is only required on Linux, and only if you're building from source):
```sh
$ sudo apt update && sudo apt install libgtk-3-dev build-essential gcc
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

# OS Versions Supported
## Windows
The oldest OS NvDialog has ran on is Windows XP, although some calls did not produce any change / output (But did not fail either). The recommended minumum is Windows 8 / 8.1, and any later version should work as expected.

## macOS
Only the very latest versions of macOS are supported. Older releases will at best throw a compiler error if compiling from source or a linking error otherwise.

Some deprecated functions are used here and there when building for macOS. This shouldn't worry you since Apple does give enough time for developers to switch away without enforcing it.

## GNU/Linux
Since there are well over 1000 distributions, there is no specific distribution requirement. However, your system must have these installed:
- Gtk 3 (3.18 or later) or `libadwaita` + Gtk4, the latest releases of each.
- Linux kernel 2.6 or newer (All modern distros include at least 4.x kernels so nothing to worry here).
- X11 or Wayland as the display server. Mir is not supported. Note that Wayland is more hardened that X11 and
some planned features cannot be introduced to it reliably.

Common distros officially supported:
| Distro | Version |
|   ---  |   ---   |
| Arch Linux | (Rolling) |
| Ubuntu and derivatives | >16.04 |
| Debian and derivatives | >Debian 7 |
| Slackware Linux | Latest |

## Android
Android support will not be implemented anytime soon (Neither iOS support). You are advised instead to use Android's `AlertDialog` class or your UI library, which would achieve the same effect.

## Other OSes
Other OSes are assumed to be supported. To make sure they do indeed work, you need to make sure the given OS supports **all** of the following features:
- Unix-like, or alternatively, **very closely** resembling Windows (If the latter, ignore the following).
- X11 or Wayland as the windowing system
- Gtk3, or Gtk4 and Libadwaita

# License
`nvdialog` is licensed under the MIT license. See [COPYING](./COPYING) for more.
All contributions made to the library are assumed to be licensed under the MIT license as well. However, you may specify a different license if you wish.
