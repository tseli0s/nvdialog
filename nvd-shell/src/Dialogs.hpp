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

#include <nvdialog.h>

class DialogManager {
private:
        int argc;
        char** argv;
public:
        DialogManager(int argc, char** argv);
        ~DialogManager();
        NvdDialogBox *SimpleDialogBox(const char* title = "nvd-shell",
                                      const char* message = "Battery too low",
                                      NvdDialogType type = NVD_DIALOG_WARNING);

        NvdReply QuestionBox(const char* title = "nvd-shell",
                              const char* question = "Are you sure you want to quit?");
};