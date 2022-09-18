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

#include <iostream>
#include <nvdialog.h>

/* The data passed to nvd-shell from the command line. */
typedef struct {
        std::string title, contents;
        NvdDialogType type;
        bool begin; // False means don't show any dialogs, eg when calling --version.
} ArgumentCollection;

class CommandLineParser {
private:
        bool inv_argument;
        ArgumentCollection arguments;
public:
        inline CommandLineParser(void) {
            this->inv_argument = false;
        }

        int ParseArguments(int argc, char **argv);
        ArgumentCollection GetArgumentOptions() {
                return this->arguments;
        }
};