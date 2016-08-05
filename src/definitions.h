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

#ifndef HEADER_DEFINITIONS
#define HEADER_DEFINITIONS

#include "dirent.h"

#if defined(WIN32) || defined(_WIN32)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif

typedef struct CONFIG {
    int valid;
    int verbose;
    int recursive;
    int foldermode;
    char key[1024];
    char infile[MAX_PATH];
    char outfile[MAX_PATH];
    char infolder[MAX_PATH];
    char outfolder[MAX_PATH];
} CONFIG;

#endif
