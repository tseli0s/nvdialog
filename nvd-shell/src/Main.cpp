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

#include <nvdialog/nvdialog.h>
#include "Dialogs.hpp"

/* Any version before 0.1.3 is incompatible with nvd-shell. */
#if NVDIALOG_VERSION_PATCH < 1
#error NvDialog version >= 0.1.3 is incompatible with nvd-shell.
#endif /* NVDIALOG_VERSION_PATCH */

int main(int argc, char **argv)
{
        DialogManager *mgr = new DialogManager(argc, argv);
        nvd_init(argv[0]);

        return 0;
}