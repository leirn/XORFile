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

#include "options.h"
#include "hexString.h"
#include "utils.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

CONFIG process_options(int argc, char* argv[]) {

    CONFIG options;

    options.valid = 0;
    options.verbose = 0;
    options.recursive = 0;
    options.foldermode = 0;
    memset(options.key, '\0', sizeof(options.key));
    memset(options.infile, '\0', sizeof(options.infile));
    memset(options.outfile, '\0', sizeof(options.outfile));
    memset(options.infolder, '\0', sizeof(options.infolder));
    memset(options.outfolder, '\0', sizeof(options.outfolder));

    if(argc == 1) {
        return options;
    }

    int i;
    for(i=1; i < argc; i++) {
        if(strcmp(argv[i], "--help") == 0) {
            print_help();
            exit(0);;
        }
        else if(strcmp(argv[i], "--folder") == 0) {
            options.foldermode = 1;

            i++;

            if(!isDirectory(argv[i])) {
                printf("Error: Input directory not a valid directory.\n");
                exit(0);
            }

            strcpy(options.infolder, argv[i]);

            if(!isLastCharPathSeparator(argv[i]))
                strcat(options.infolder, PATH_SEPARATOR);

            i++;

            if(!isDirectory(argv[i])) {
                printf("Error: Output directory not a valid directory.\n");
                exit(0);
            }

            strcpy(options.outfolder, argv[i]);

            if(!isLastCharPathSeparator(argv[i]))
                strcat(options.outfolder, PATH_SEPARATOR);

            if(strcmp(options.infolder, options.outfolder) == 0) {
                printf("Error: Input and Output directories cannot be the same.\n");
                exit(0);
            }
            continue;
        }
        else if(strcmp(argv[i], "--keyfile") == 0) {
            i++;
            FILE *h;
            h = fopen(argv[i], "rb");
            fread(options.key, sizeof(char), 1024, h);
            fclose(h);
            continue;
        }
        else if(strcmp(argv[i], "--keyascii") == 0) {
            i++;
            strcpy(options.key, argv[i]);
            continue;
        }
        else if(strcmp(argv[i], "--keyhexa") == 0) {
            i++;
            strcpy(options.key, hexStringToString(argv[i]));
            continue;
        }
        else if(strcmp(argv[i], "--recursive") == 0) {
            options.recursive = 1;
            continue;
        }
        else if(strcmp(argv[i], "--verbose") == 0) {
            options.verbose = 1;
            continue;
        }
        else if (i == 1) {
            strcpy(options.infile, argv[i]);
            i++;
            strcpy(options.outfile, argv[i]);
            continue;
        }
    }
    options.valid = check_config_validity(options);
    return options;
}

int check_config_validity(CONFIG conf) {
    if(strlen(conf.key) == 0) {
        printf("No key found.\n");
        return 0;
    }
    if(conf.infile != NULL && conf.outfile != NULL)
        return 1;
    if (conf.foldermode && conf.infolder != NULL && conf.outfolder != NULL)
        return 1;
    return 0;
}

void print_help() {
    printf("XOR crypt/decrypt tool\n\n");
    printf("Usage:\n");
    printf("\tXORFile.exe --help\n\n");
    printf("\tXORFile.exe infile outfile  [...]\n\n");
    printf("\tXORFile.exe --folder infolder outfolder [...]\n\n");
    printf("Options:\n");
    printf("\t--help\n");
    printf("\t\tDisplay this help message\n\n");
    printf("\t--keyfile\n");
    printf("\t\tFile containing the key\n\n");
    printf("\t--keyascii\n");
    printf("\t\tKey size limit of 1024 characters\n\n");
    printf("\t--keyhexa\n");
    printf("\t\tGive the key has an hexadecimal figures.\n");
    printf("\t\tExemple: XORFile.exe infile outfile --keyhexa ffc0da12\n\n");
    printf("\t--recursive\n");
    printf("\t\tIn folder mode, parse the folder recursively\n\n");
    printf("\t--verbose\n");
    printf("\t\tDisplay extra information at run time\n\n");
}
