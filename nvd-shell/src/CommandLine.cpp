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

#include "CommandLine.hpp"
#include <cstring>
#include <string>

int CommandLineParser::ParseArguments(int argc, char **argv)
{
        for (int i = 0; i < argc; i++) {
                if (strcmp(argv[i], "--help") == 0) {
                        break;
                } else if (strcmp(argv[i], "--version") == 0) {
                        this->arguments.begin = false;
                        break;
                } else if (strcmp(argv[i], "--dialog-type") == 0) {
                        this->arguments.type = (NvdDialogType) std::stoi(std::string(argv[i+1]));
                        continue;
                } else if (strcmp(argv[i], "--title") == 0) {
                        this->arguments.title = std::string(argv[i+1]);
                        continue;
                } else if (strcmp(argv[i], "--description") == 0) {
                        this->arguments.contents = std::string(argv[i+1]);
                        continue;
                } else {
                        this->arguments.begin = false;
                        break;
                }
        }
        return 0;
}