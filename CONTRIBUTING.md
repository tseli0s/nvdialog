# Contributing to NvDialog
NvDialog is an open source project, which apart from all the freedoms it gives you on distribution and usage, it also allows other developers (And not only!) to develop it at the same time.

## 1. Creating merge requests:
NvDialog uses `git` as it VCS. Although you are expected to know how to use it, here are some simple instructions on creating a pull request from a local copy of the repository:
1. Fork this repository, and make sure it's public so CI can run.
2. Clone the forked repository locally (You won't need to do this more than once; Work on each feature / bug fix from the repository without duplicating it):
```sh
$ git clone https://github.com/USERNAME/nvdialog.git --depth=1 && cd nvdialog/
```
3. For your new code, do **NOT** commit to the master branch. Instead, create and switch to a new branch, named after what you are planning to contribute:
```sh
$ git fetch upstream
$ git checkout -b new-feature upstream/master
# Here you need to commit your changes.
$ git add src/some-file.c && git commit -m "some-file.c: Create new feature."
$ git push -u origin new-feature
```
## 2. Commit Messages
NvDialog uses a very simple model for commit messages:
- If an include was changed or new functions were added, the commit message will start with the new function's name or the filename (without the extension, the `nvdialog_` prefix, and any dirs). Eg:
```sh
$ git commit -m "main: Fix incorrect include." -m "Fixed an incorrect include within the file causing a compile error due to recent changes."
```
- If a new function was added, for the public API (Aka what the end user is going to use), the function name should be used.
```sh
$ git commit -m "nvd_dialog_box_new_improved: Implement function." -m "Implemented new function."
```
- For backend-wide changes such as implementing a platform-dependent functionality, use the backend/&gt;BACKEND&lt;
```sh
$ git commit -m "backend/gtk: Add notification support for Gtk3 backend."
```
- For everything else, you can just use the commit message, omitting filenames, functions etc. Eg:
```sh
$ git commit -m "tree: Fix compilation errors on Windows 11."
```
- **Descriptions of the commit should just extend the first commit message, adding notices if necessary, and if needed, also specifying which commit do they fix.**

# Coding Style
Initially, NvDialog used the LLVM coding style because it was simple and straightforward. In order to ensure formatting took place project-wide, `clang-format` was used. Since v0.5.0, although still influential, that coding style along with the use of `clang-format` is considered deprecated. Instead,
now there are just a new simple rules for everything (Everything left out can be inspired by existing code but doesn't have to follow it).
## - **Brackets**
Brackets shall be placed to the end of the declaration or statement:
```c
if (there_was_something_wrong) {
        free(something);
        exit(EXIT_FAILURE);
}

/* And they should also be entirely avoided when possible: */
if (something) nvd_print_error("%s", "something");
else           nvd_print_error("%s", "nothing");

switch (type) {
case 0: cleanup();
case 1: break;
default: nvd_print_error("Invalid enum.");
}

NVD_WONT_RETURN void nvd_out_of_memory(void) {
        die("Out of memory");
}
```

## - **Function declarations (Parameters, return values, etc):**
Generally, function declarations depend on how long the declaration is on the line.
If too many arguments are needed or the return value is also having a long declaration,
we break lines when appropriate, in this style:
```c
uint32_t nvd_do_something_extraordinaly_large(const char* str,
                                              const uint32_t num,
                                              const NvdDialogType __enum);

void nvd_simple_fn(const char* str, const char* second_str);

void nvd_not_as_simple_fn(const char* str,
                          const char* second_str);

static inline struct test_struct
nvd_very_long_declaration(const char* str,
                          uint32_t    something,
                          uint8_t     buffer);
```
## - **Formatting**

Try to align everything equally per-line. This gives an amazing code look that is also easy to understand. Remember that between actions, you should always have a newline to make it easier to find where needed code is in the future. Here are some examples:
```c
void* nvd_do_something(const char **buffer, int *param) {
        *buffer = "Test";
        *param  = 732;

        some_function   ((char**) &buffer);
        another_function((char**) &buffer);
        yet_another_one (param,    buffer);

        return NULL;
}

uint32_t bunch_of_assignments(int *param) {
        uint16_t first, second, third, and_another_one;

        first  = 1;
        second = 2;
        third  = 3;
        
        and_another_one = 0;
        return and_another_one;
}
```
## - **Naming**
- **Function naming is a combination of:**
1. The library prefix for symbols (`nvd_`),
2. The dialog they are handling   (eg. `dialog_box_`)
3. The action they are doing      (eg. `new`, `set_accept_label`);

- **Types use a CamelCase syntax, examples:**
- `NvdDialogBox`
- `NvdAboutDialog`
- `NvdFileDialog`

- **Macros should be capitalized and use underscores, eg:**
- `NVD_RETURN_IF_NULL(x)`
- `NVD_CHECK_INITIALIZATION_OR(x)`

- **Variables always use snake_case syntax. For example:**
- `int some_var;`
- `int another_var;`
- `void*(*function_pointer)(void*);`

## - **Indentation**
Lines should be at most 60 characters long. Exceptions are allowed if there is a good reason for it, but should always be avoided.

# Adding new backends
You may wish to expand the library's platform support for a specific project. Since v0.8, the way each backend is initialized is much more modular and independent, making the process much easier to understand and document.

> [!NOTE] 
> In the (long) future, a plugin system will be introduced that allows developers to add their own backends and load them at runtime, eg. based on the desktop environment used. This is intended to allow the library to be expanded to multiple platforms without bloating the core library.

There are three major steps to adding a new backend:
1. Add a new directory under `src/backend` with the name of the backend. Then write the code for it with a unique suffix in each function. For example, this is how an `NvdDialogBox` is created with the `gtk` backend:
```c
// Notice the _gtk suffix:
NvdDialogBox *nvd_dialog_box_gtk(const char *title, const char *message,
                                 NvdDialogType type) {
        NvdDialogBox *dialog = malloc(sizeof(NvdDialogBox));
        NVD_RETURN_IF_NULL(dialog);

        dialog->accept_label = "Okay";
        dialog->content = (char *)message;
        dialog->msg = (char *)title;
        dialog->type = type;

        GtkMessageType gtk_type;
        switch (type) {
                case NVD_DIALOG_WARNING:
                        gtk_type = GTK_MESSAGE_WARNING;
                        break;
                case NVD_DIALOG_ERROR:
                        gtk_type = GTK_MESSAGE_ERROR;
                        break;
                default:
                case NVD_DIALOG_SIMPLE:
                        gtk_type = GTK_MESSAGE_INFO;
                        break;
        }

        dialog->window_handle =
                gtk_message_dialog_new(nvd_get_parent(), GTK_DIALOG_MODAL | GTK_DIALOG_USE_HEADER_BAR,
                                       gtk_type, GTK_BUTTONS_OK, "%s", message);
        gtk_window_set_title(GTK_WINDOW(dialog->window_handle), title);
        GtkWidget *ok_button = gtk_dialog_get_widget_for_response(
                GTK_DIALOG(dialog->window_handle), GTK_RESPONSE_OK);
        dialog->accept_button = ok_button;
        g_signal_connect_swapped(dialog->window_handle, "response",
                                 G_CALLBACK(gtk_widget_destroy),
                                 GTK_WIDGET(dialog->window_handle));

        return dialog;
}

```
2. In `src/nvdialog_init.c`, register the functions of the backend for each functionality in a separate function that'll be called later.
Examine the `NvdbackendMask` (defined in the header) and preexisting implementations to understand the pattern.
3. In `CMakeLists.txt`, make sure you register the backend's source code and includes. For example, this is how the `win32` backend registers its own files:
```cmake
# You can also use a wildcard, although it is discouraged.
if(WIN32 OR CROSS_COMPILE_FOR_WIN32)
    set(NVD_SOURCES
        src/backend/win32/nvdialog_about_dialog.c
        src/backend/win32/nvdialog_dialog_box.c
        src/backend/win32/nvdialog_question_dialog.c
        src/backend/win32/nvdialog_file_dialog.c
        src/backend/win32/nvdialog_notification.c
        ${NVD_COMMON_SOURCES})
```

4. Test the backend to make sure it works as expected. [This subproject](./nvd-demo/) may be of interest to you.

# AI Policy
Contributions with code partially or completely generated by generative AI models (Such as ChatGPT) have to be marked as such (If only part of the pull request was written by AI, then mention the specific parts only). When you provide AI generated code, make sure that code was not directly ripped off of another project through the AI's training data, as that may create legal problems and gray areas.

You are free to use AI for any purpose, as long as you follow the rules above. I strongly recommend avoiding it where possible though, for ethical and practical reasons.
