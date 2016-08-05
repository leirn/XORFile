/**
 *  This file is part of XORFile.
 *  Copyright (C) 2016 Laurent Vromman
 *
 *  XORFile is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 *  XORFile is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XORFile.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef HEADER_UTILS
#define HEADER_UTILS

int isFileExist (char *filename);

int isDirectory(const char *path);

int isLastCharPathSeparator(const char *path);

#endif
