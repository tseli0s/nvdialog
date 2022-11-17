# Contributing to NvDialog
NvDialog is an open source project, which apart from all the freedoms it gives you on distribution and usage, it also allows other developers (And not only!) to develop it at the same time. This is entirely voluntary: NvDialog doesn't rely on a lot of developers anyways, and development won't halt if not enough people are interested in contributions.

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
- If an include was changed or new functions were added, the commit message will start with the file name. Eg:
```sh
$ git commit -m "src/nvdialog_main.c: Fix incorrect include." -m "Fixed an incorrect include within the file causing a compile error due to recent changes."
```
- If a new function was added, then the function name will be used instead:
```sh
$ git commit -m "nvdialog_dialog_box_win32: Implement function." -m "Implemented new API function for the WinAPI backend."
```
- For some directory-wide changes (Like adding a new API set), the directory name should be used (Not as a nested directory, see below). 
```sh
$ git commit -m "gtk/: Add notification support for Gtk3 backend."
```
- For everything else, you can just say the commit message, omitting filenames, functions etc. Eg:
```sh
$ git commit -m "Fixed crash when using the Adwaita backend."
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
else nvd_print_error("%s", "nothing");

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