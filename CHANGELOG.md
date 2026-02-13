# Changelog -- 0.10.2
- Improved GitHub workflows for more extensive testing
- Fixed a compiler warning in `nvd_image_to_bytes`
- Numerous minor code cleanups and compiler warning fixes
- Fix incorrect return values if a file(name) was not chosen when using `NvdFileDialog` on Windows (See #54)
- nvdialog can now be built as a CMake submodule (See #68)
- Fixed missing header when installing using the [Makefile](./Makefile) (See #66)
- Warn if the target cannot be recognized when initializing backends during `nvd_init()`.

# Changelog -- 0.10.1
- Fixed memory leak when freeing a notification in the `gtk` backend
- Removed checking for libnotify at runtime when on GNU/Linux
- Removed an unused internal function
- Changed assertion macro for stb_image.h to use the NvDialog implementation instead
- Disabled some redundant warnings when building with the Makefile
- Fixed a bug where `nvd_get_capabilities()` returned incorrect values for `NVD_STATIC_LINKAGE` argument
- Added two new internal functions: `nvd_malloc` and `nvd_calloc`. These wrap around libc's implementation of `malloc`/`calloc` with some extra error handling that was necessary. The entire tree has been updated.
- Minimum required CMake version is [3.19](https://cmake.org/cmake/help/latest/release/3.19.html) from this release forward (See `bbed24e`).
- Minor changes to make nvdialog work with more limited and rare compilers
- \[internal] `nvd_set/get_error` is no longer force-inlined, fixing some linking errors on FreeBSD+clang
- Codebase cleanup from legacy functions and variables
- Fixed FileDialog not using file filters and default filename parameters on the `gtk` backend.
- New function `nvd_image_to_bytes()`. This function returns the raw bytes that represent an image inside `NvdImage`
  and can be reused for other purposes.
- Fixed missing definition of `nvd_open_file_dialog_get_raw`
- New `NvdError` member: `NVD_UNSUPPORTED_ACTION`, when the API is disabled for a build of nvdialog.
- Make image functionality optional (enabled by default) so that users that don't need image support can easily get rid of it.

# Changelog -- 0.10.0
- (**BREAKING**) Added new `NvdDynamicString` type and integrated it into various library APIs. This will break the FileDialog and Error groups in preexisting code.
- Added new `NvdInputBox` API - An input box can be used to retrieve simple text input from the user.
- Increased shared file version to 3 (Output files may contain libnvdialog.so.3 now).
- Improved `NvdDialogBox` on Gtk backends by switching to the native `GtkMessageDialog`.
- Improved `NvdQuestionBox` on Gtk backends by switching to the native `GtkMessageDialog`.
- Fixed Windows and macOS backends returning stack pointers from functions (See #53, #56, #58).
- Deprecate libadwaita (Read MR #59 for details and documentation for moving forward)
- Added missing `nvd_dialog_box_set_accept_text` function.
- Fixed `NVD_ASSERT_FATAL` macro failing regardless of condition.
- Added NvdInputBox on `nvd-demo`.
- Fixed tests not working on Windows.
- Fixed some compiler warnings when cross-compiling.
- Merged the `sandbox` with the `gtk` backend. This will not change any functionality for any applications.
- NvDialog will not set the error codes in case something went wrong more often.
- Improved assertion macro.
- Added support for GNUstep.
- The `adw` backend's functions will now simply call directly on the `gtk` implementations.
- Added some notes for other (non-GNU/Linux) operating systems and patched the build system to work with them.
- CMake will no longer be configured to use `/usr` as the install prefix on Unix-like systems. `ld.so.conf` may need to be modified on some GNU/Linux distros.
- Removed `PKGBUILD` file from the tree (Arch Linux users will soon be able to get nvdialog as a package from the AUR instead)
- Small codebase cleanup for easier maintenance (Mostly removing unnecessary assertions, functions and so on)
- Fixed a bug where the `win32` backend ignored filters on file dialogs.
- Fixed `NvdFileDialog` having inaccurate button labels with the `gtk` backend.
- Fixed a double free bug in the `gtk` implementation of `NvdFileDialog`.
- Removed dependency on `libnotify` for notifications. Now nvdialog will use DBus directly instead.
- Deprecated `nvd_add_notification_action` (Now it's a no-op on all backends)

# Changelog -- 0.9.0
- CMake will now only set `CMAKE_INSTALL_PREFIX` to `/usr` if the host is not Windows or macOS. This may fix some installation problems you might have had when previously installing the library.
- Disabled ARC on the `macos` backend (ie. Fixes #55)
- The library will no longer set the compiler flags manually, instead relying on CMake's default choices. Only exception is when cross-compiling from GNU/Linux to Windows.
- Made the CMakeLists.txt options more user-friendly.
- Added support for custom images (See `NvdImage`)
- Fixed a bug where a `char` was accidentally treated as a string (See #56)
- Fixed a bug where the requested title wasn't applied to Windows dialogs
- Fixed a bug where an uninitialized variable was used in the Windows dialog box backend.
- Removed certain backend-specific warnings for the Windows backend
- Added `nvd_open_folder_dialog_new` function: Now you can request to open directories instead of files using an `NvdFileDialog`
- Switch the default backend on Arch Linux from libadwaita to gtk
- Cleaned up and restructured `CMakeLists.txt` (This should not break anything, functionality remains the exact same)
- Provide an option in `CMakeLists.txt` to build the documentation along with the library (Requires `doxygen`)
- Fixed a problem where types/objects were partially initialized leading to memory issues.
- Improved the documentation and fixed some documentation inaccuracies from the past versions.

# Changelog -- 0.8.1
- MacOS about dialog support returned
- (**BREAKING**) Removed first parameter on `nvd_init`, which was already unused since v0.7
- Fixed some warnings on Windows.
- Add icon support for `NvdAboutDialog` on Windows.
- Many improvements in `NvdAboutDialog` on Gtk3.
- Documentation improvements
- Fix `NvdAboutDialog` on Linux not having an icon.
- `NvdDialogBox` will no longer be marked as a popup on Linux/Gtk3. This will fix incorrect positioning on Wayland.

# Changelog -- 0.8.0
- You can now set the dialog button text to something else.
- Dialogs in Gtk3 are now unresizable, due to artifacts formed on some systems
  when resizing and looks.
- Dialogs are now marked as popup windows and not toplevel ones.
- On the Windows backend, NvDialog will now check if sending the notification to the user was succesfull.
- Added destructors on notification objects, to avoid memory leaks.
- Fixed some compiler warnings regarding `const` assignments when compiling the library.
- Fixed Cocoa backend using different implementations of (public) types due to unmaintained code.
- `nvd_get_capabilities()` will now set an error code if the query is not supported (eg. Invalid enum).
- Removed unused functions within the library.
- Fixed `nvd_dialog_box_set_accept_text` crashing on Linux.
- Reduced memory usage by the library (See 3d967e7)
- Fixed missing declaration warning on the Gtk backend.
- Completely removed styling functions (Already deprecated since v0.7.0)
- Increased shared file version to 2 (Output files may contain libnvdialog.so.2 now)
- Fixed libnotify not loading on Linux (See #44 for details)
- Fixed a bug where NvDialog would abort the entire process despite no failure happening.
- Fixed dialog not disappearing after pressing the accept button (See #42)

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

