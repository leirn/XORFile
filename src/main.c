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

#include <stdio.h>
#include <stdlib.h>
#include "xor.h"
#include "options.h"
#include "definitions.h"
#include "dirent.h"
#include "utils.h"

void treatDir(const char * dirname, CONFIG options);

int main(int argc, char* argv[]) {
    CONFIG options = process_options(argc, argv);

    if(options.valid == 0) {
        printf("Unvalid options\n");
        print_help();
        exit(0);
    }
    else if (options.verbose) {
        printf("Valid parameters loaded:\n");
        printf("\tVerbose mode: activated\n");
        if(options.foldermode) {
            printf("\tFolder mode: activated\n");
            printf("\tInput folder: %s\n", options.infolder);
            printf("\tOutput folder: %s\n", options.outfolder);
            printf("\tRecursive mode: %s\n", (options.recursive?"activated":"not activated"));
        }
        else {
            printf("\tInput file: %s\n", options.infile);
            printf("\tOutput file: %s\n", options.outfile);
        }
        printf("\tKey: %s\n", options.key);
    }

    if(options.foldermode) {
        char suffix[MAX_PATH] = "";
        treatDir(suffix, options);
    }
    else
        process_file(options.infile, options.outfile, options);
    return 0;
}

void treatDir(const char * dirname, CONFIG options) {
    if (options.verbose) printf("Entering directory %s%s", options.infolder, dirname);

    DIR *dir;
    char inbuf[MAX_PATH] = "";
    char outbuf[MAX_PATH] = "";
    char recursdir[MAX_PATH] = "";
    strcpy(inbuf, options.infolder);
    strcat(inbuf, dirname);

    struct dirent *dp;
    dir = opendir(inbuf);
    while ((dp=readdir(dir)) != NULL) {
        printf("debug: %s\n", dp->d_name);

        if ( !strcmp(dp->d_name, ".") || !strcmp(dp->d_name, "..") ) {
            // do nothing (straight logic)
            continue;
        }
        strcpy(recursdir, dirname);
        strcat(recursdir, dp->d_name);

        strcpy(inbuf, options.infolder);
        strcat(inbuf, dirname);
        strcat(inbuf, dp->d_name);
        strcpy(outbuf, options.outfolder);
        strcat(outbuf, dirname);
        strcat(outbuf, dp->d_name);

        if (isDirectory(inbuf)) {
            #if defined(_WIN32)
            _mkdir(outbuf);
            #else
            mkdir(outbuf, 0700);
            #endif
            strcat(recursdir, PATH_SEPARATOR);
            treatDir(recursdir, options);
        }
        else {
            process_file(inbuf, outbuf, options);
        }
    }
    closedir(dir);
}
