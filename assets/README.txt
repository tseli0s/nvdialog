This library is NvDialog, a minimal library to create window dialogs in a cross platform way,
that use the system's look and feel and do not feel clumsy.  This is not the official README,
but a simplified text version to instruct on how to get started.

You are expected to have this file along with a prebuilt version of NvDialog, and its
headers as well from somewhere, perhaps from the Releases. If that's the case, keep reading
to get started. Otherwise, visit https://github.com/tseli0s/nvdialog/ and see there for more.

You should have either a .so file or a .dll file in the same folder in this file. This is the actual
library itself. You can copy this somewhere in your project or even on a system-wide path,
like /usr/lib for GNU/Linux. The prebuilt library shipped is a 64-bit binary with aggressive (-O3) optimizations
as well as CMake-specific ones. Just make sure your project finds it at runtime, usually by setting LD_LIBRARY_PATH.

There should also be another folder named 'include'. This folder contains all the headers.
You should copy this folder EXACTLY with the same layout structure as it is, somewhere
that your project can find. Also indicate to your compiler the headers are there in the first place, by using
the -I flag or by setting it in your IDE.

For support, open an issue on the GitHub of NvDialog: https://github.com/tseli0s/nvdialog/issues.
Feel free to also use the discussions, for suggestions or questions you may have.