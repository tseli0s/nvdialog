# NvDialog roadmap
This is a summary of what NvDialog will implement/fix to reach version 1.0.
Consider this a TODO - And feel free to contribute for any of them.

Please note this is not a generic roadmap of what the library will do. This is what
will be done before the stable release v1.0, to ensure no breakages for years to come.

# API/ABI
- Stable interface to the library (No function declaration changes, no ABI changes (Aka relying exclusively on opaque types), no
change in the linkage, ensure that breaking changes are only done on major version releases)
- No undefined behaviour usage, complete reproducible builds
- Ensure NvDialog works the same regardless of the compiler
- > Ensure that all warnings are either handled or, if ignored, they're ignored for a good reason
- Allow translation of hardcoded strings
- > Add built-in support for other common languages like Spanish, French, Russian (...)
- >> Ensure hardcoded strings use the system language on each platform

# Backends
- Implement X11 backend as Gtk moves more and more to Wayland-specific, Linux-oriented development, to continue supporting BSDs and other Unix-like operating systems
- Implement Haiku backend to make NvDialog available on it
- > Currently loosely handled by the gtk backend, but that is unreliable; gtk support on Haiku is very shaky
- Clean up the codebase from adwaita backend code
- Ensure Wayland and X11 support are on feature parity
- Provide a basic Android backend to be expanded by users (! Uncertain !)

# Codebase
- Formalize use of tools like `clang-format` and `clang-tidy` to catch unexpected behaviour
- > Config files and even CI exists, but goes unused for now
- Improve the Makefile

# Documentation
- Document every single public API
- > Mostly done while developing v0.10, ensure that this is the case before v1.0 is released
- Document any platform-specific behaviour
- > Lack of maintainers in the Cocoa backend makes this harder for macOS

# Versioning
- Publish and formalize clear versioning strategies
- Odd-numbered minor releases will be bug fixes and patches; Even numbered ones will be "stable"
- Settle on a clear release schedule (Every 6 months maximum), with the possibility of releasing earlier

