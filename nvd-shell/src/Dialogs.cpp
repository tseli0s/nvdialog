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

#include "Dialogs.hpp"

DialogManager::DialogManager(int argc, char **argv)
{
        this->argc = argc;
        this->argv = argv;
}

DialogManager::~DialogManager(void)
{
        this->argc = 0;
        this->argv = nullptr;
}

NvdReply DialogManager::QuestionBox(const char* title,
                                    const char* question)
{
        return nvd_dialog_question_new(title, question, NVD_YES_NO_CANCEL);
}

NvdDialogBox* DialogManager::SimpleDialogBox(const char* title,
                                             const char* message,
                                             NvdDialogType type)
{
        return nvd_dialog_box_new(title, message, type);
}
