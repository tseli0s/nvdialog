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
