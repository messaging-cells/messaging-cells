/*
  File: e-loader.h

  This file is part of the Epiphany Software Development Kit.

  Copyright (C) 2013 Adapteva, Inc.
  See AUTHORS for list of contributors.
  Support e-mail: <support@adapteva.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License (LGPL)
  as published by the Free Software Foundation, either version 3 of the
  License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  and the GNU Lesser General Public License along with this program,
  see the files COPYING and COPYING.LESSER.  If not, see
  <http://www.gnu.org/licenses/>.
*/

#ifndef BJ_LOADER_H
#define BJ_LOADER_H

#include "e-hal.h"

#ifdef __cplusplus
extern "C"
{
#endif

int bj_load(const char *executable, e_epiphany_t *dev, unsigned row, unsigned col, e_bool_t start);
int bj_load_group(const char *executable, e_epiphany_t *dev, unsigned row, unsigned col, 
						unsigned rows, unsigned cols, e_bool_t start);

#ifdef __cplusplus
}
#endif

#endif // BJ_LOADER_H
