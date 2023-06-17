# Changelog -- 0.8.0
- You can now set the dialog button text to something else.

# Changelog -- 0.7.0
- Gtk dialogs will now be guaranteed to have their title set.
- Gtk dialogs are now modal, meaning the user can't skip over them without
  responding to them.
- NvDialog will check if it has been initialized before **any** API call.
- Added extra null pointer / invalid parameter checking.
- `nvd_init`: The parameter 'program' of the function is now deprecated.
- Initial work towards sandbox support (See #36), based off the Gtk3 backend.
- File dialogs now support extension filters. See documentation.
- Fixed notifications on Linux failing, NvDialog will now handle `dlopen()` errors.
- All global static variables now are thread local, to improve safety on some platforms.
- GitHub workflows now use a target triple naming (*arch*-*device*-*os*-*toolchain*, eg. 
**x86_64-pc-windows-msvc**)
- C standard is now required to be at least 2011 or newer (See https://github.com/tseli0s/nvdialog/commit/c7e68a04fded266e819e46851b13d74de64cb133).
- Deprecated styling support (Now all backends will just return a "fail value" like a **`NULL`** pointer or a negative integer).

# Changelog -- 0.6.1
- Fixed initialization call failing on Gtk3.
- New `NvdError` member: `NVD_BACKEND_FAILURE`.
- Fixed some build warnings.

# Changelog -- 0.6.0
- Removed domain name support in favor of plain application names.
- Added application name support.
- Added MacOS X Support (Thanks to: @Frityet)
- Fix `nvd_get_error` return type.
- Dialogs will now be destroyed immediately after closing them.
- Added `NVD_API` macro to export functions to Windows (or import them).
- Fixed `nvd_about_dialog_gtk` not working properly under the Gtk4 backend when custom icons were used instead of the default ones.
- New function: `nvd_add_notification_action`. The description of this function is rather long,
  see `include/nvdialog_notification.h` for the declaration and its documentation.
- `nvd_init` will check if the library has been initialized already and return if so.
- Fixed some build errors on newer distributions (Especially on the Adwaita backend).
- Improved the documentation largely. Now `doxygen` will be used to generate documentation.
- Setting the environment variable `NVD_NO_NOTIFS` to `1` will disable the `libnotify` dependency
  on Unix systems.
- New website for the library, created entirely with Doxygen: https://androgr.github.io/nv.dialog/ .
  From now on, the website will also be constantly updated with new documentation.
- Added notification support for Windows (Vista and above will work only).
- Fixed the Gtk4 file dialog not working.

## **WIP:**
- Adding Android support (Should be done by the next version).
- Adding support for sandboxed environments, and by extension, immutable Linux distributions
(such as VanillaOS).

# Changelog -- 0.5.0

- Added custom CSS stylesheet support (`NvdCSSManager`).
- Added notification support (`NvdNotification`).
- Added testing units in CI.
- Fix `nvd_stringify_error` returning invalid pointer, causing undefined behavior.
- Added two new library errors:\
        - `NVD_FILE_INACCESSIBLE` (A file NvDialog tried to access is not accessible),\
        - `NVD_BACKEND_INVALID`   (A backend is invalid, eg. A symbol can't be accessed)
- Added `NVD_VERSION` macro -- Stores the compile time version of NvDialog to the `NvdVersion` variable passed.
- Added `nvd_*_get_raw()` functions -- Allows to get the window implementation behind the dialog to use for the styling API.
- Added `pkg-config` script to make NvDialog compatible with other build systems.
- Removed previously deprecated functions.
- NvDialog can now build with other compilers than GCC and CLang.
- On `Adwaita` backend, the `NvdAboutDialog` will now use `AdwAboutWindow` instead, to make development easier.
- Added `NvdFileDialog` support for save file dialog, mostly working.

# Changelog -- 0.3.0

- Changed the API to now use a new model, where creating and showing the dialog window are now seperate tasks.
- Rewritten the `NvdAboutDialog` with a better UI for Linux.
- The source code tree is now reorganized in a much better working model.
- On Arch Linux, packages are going to be built from the local source code instead of the remote repository one, to allow for better integration with the package manager and stability.
- The Adwaita backend is no longer experimental, and has become the default backend on Unix systems.
- Fix `NvdFileDialog` not working under the Gtk3 backend.
- Refreshed the website a little.
- Added CI, to better test if NvDialog is working properly across platforms. (WIP)
- Resulting shared library version has now been increased to 1. ([f3128b6]())
- Once again, updated the logo. This time it's much more modern and beautiful.

# Changelog -- 0.2.0

- Fixed compilation errors on all backends (Especially Windows).
- API Upgraded to 0.2.0
- New function: `nvd_about_dialog_new` - Shows a window with information about your application.
- New functions:\
        - `nvd_set_parent` - Allows to set a foreign window as the parent of every dialog.\
        - `nvd_get_parent` - Returns the current parent window or NULL otherwise.\
        - `nvd_delete_parent` - Marks that no window is currently considered the parent.
- Implemented Gtk4 backend (Currently still experimental).
- Adwaita Backend now partially available.
- `nvd_about_dialog_new` -> Window size is now more compact (Gtk3 only)
- Simple dialogs are no longer resizable (Gtk3 only).
- Fixed a bug where the process would remain open even though all the windows were closed.
- Added a function to query NvDialog's capabilities at runtime. ([7511aaf](https://github.com/AndroGR/nvdialog/commit/7511aaf9cc1976c81c134feecea3248895f2f133))
- `setlinebuf(stdout)` will no longer be called on Windows.
- NvDialog's website is ready ([Click Here](https://androgr.github.io/libnvdialog/))
- `nvd-shell` is no longer part of this project, considered deprecated until later notice.
- Fixed a bug in `nvd_stringify_error` where a local string would be returned instead of a heap one.
- Assertion failures no longer output red text.
- Function names are now using a GCC extension to allow `main` to become `int main(int, char**)`.
- Ported API changes to Windows.
- Added `PKGBUILD` for Arch Linux.

# Changelog -- 0.1.3

- Fixed multiple compiler / linker errors
- Fixed a buffer overflow by using `NVDIALOG_MAXBUF` instead of a fixed 128 byte buffer.
- New function (Incomplete): `nvd_about_dialog_new`. This function shows a simple dialog similar to those found in some 'About' app menu items. It will be stabilized in 0.2.
- Added new example.
- Removed deprecated code, replaced with more modern and accurate alternatives.
- Partial `libadwaita` support complete.
- New assertion system.
- Remove fallback backend, replaced with raw runtime assertions.
- Headers are now installed inside the `nvdialog/` directory in the standard include directory.
- New logo (May change again)

**WARNING: API breakage may occur. If you are worried, do not upgrade to this release.**

# Changelog -- 0.1.2

- Fixed multiple miscalleneous bugs from 0.1.1 and a few memory leaks.
- Fixed compile error with the Makefie.
- Initial work towards Gtk4 and libadwaita porting.
- Update legacy code to v0.1.2

# Changelog -- 0.1.1

- Fixed memory bugs from the library.
- Returned strings are now returned as `strdup()` to avoid undefined behavior (Remember to free them).
- Documentation on its way by v0.2.0.
- Added `nvd_dialog_question_new` | This function creates a question dialog. A variant for custom buttons is also coming soon.
- Fixed some header issues.
- New build system: Unix Makefiles. This is primarily targeting older systems where the CMake version isn't low enough.

# Changelog -- 0.1.0 (First release)
- Added support for Windows
- Ported all Unix functionality on the Windows side.
- Added minimal Rust support, currently in alpha stage.
- New function (Still a WIP): `nvd_open_file_dialog_new()`. This function opens a window\
that asks for a file through a GUI interface. Not working on Windows and Flatpak, and Unix implementation is still buggy.
- Fixed a bug where the (dialog) process would remain active after closing the window without pressing OK.
- Fixed compilation errors on Windows.
- CMake will no longer attempt to install the built files and headers anywhere.

