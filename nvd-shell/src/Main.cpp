/*
 * Copyright (C) 2022 Aggelos Tselios. This file is part of nvd-shell.
 *
 * nvd-shell is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * nvd-shell is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with nvd-shell.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <string.h>
#include <nvdialog/nvdialog.h>
#include "Dialogs.hpp"
#include "CommandLine.hpp"
#include <iostream>


/* Any version before 0.1.3 is incompatible with nvd-shell. */
#if NVDIALOG_VERSION_PATCH < 1
#error NvDialog version >= 0.1.3 is incompatible with nvd-shell.
#endif /* NVDIALOG_VERSION_PATCH */

/* The output of the --help flag. */
static void usage(const char* program)
{
        std::cout << "nvd-shell is a command line tool for displaying dialog boxes using NvDialog." << std::endl;
        std::cout << "Usage: " << program << " [ FLAGS | OPTIONS ]" << std::endl;

        std::cout << "Flags:" << std::endl;
        std::cout << "--help -> Show this information." << std::endl;
        std::cout << "--version -> Show version information and exit" << std::endl;
        std::cout << "--title -> Set the dialog's title" << std::endl;
        std::cout << "--description -> Set the dialog's content message." << std::endl;
        std::cout << "--dialog-type -> Choose what dialog to display (See manpage for values)" << std::endl;

        return;
}

int main(int argc, char **argv)
{
        if (argv[1]) {
                ArgumentCollection args;
                CommandLineParser cmp;
                if (strcmp(argv[1], "--help") == 0) {
                        usage(argv[0]);
                        return 0;
                } else {
                        cmp.ParseArguments(argc, argv);
                        args = cmp.GetArgumentOptions();
                        char* title, *contents;
                        title = (char*) args.title.c_str();
                        contents = (char*) args.contents.c_str();

                        if (args.begin != 73) {
                                /* TODO: Based on --dialog-type, find the appropriate dialog to show */
                                nvd_dialog_box_new(title,
                                                   contents,
                                                   NVD_DIALOG_SIMPLE);
                        }
                }
        } else {
                usage(argv[0]);
                return -1;
        }

        DialogManager *mgr = new DialogManager(argc, argv);
        nvd_init(argv[0]);
        return 0;
}