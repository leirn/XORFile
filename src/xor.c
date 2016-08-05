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

#include "xor.h"
#include <stdio.h>
#include <string.h>

int process_file(char * in, char * out, CONFIG options) {

    if(options.verbose) printf("Processing file %s into %s\n", in, out);

    FILE *hi;
    FILE *ho;
    hi = fopen(in, "rb");
    ho = fopen(out, "wb");

    int i, m, key_offset, keylength;
    keylength = strlen (options.key);

    key_offset = 0;

    char val[1024];
    unsigned int t;
    t = 0;
    t -= 1;

    while(1) {
        m = fread(val, sizeof(char), 1024, hi);
        for(i = 0; i < m ; i++) {
            val[i] ^= options.key[key_offset];
            key_offset++;
            if(keylength == key_offset) key_offset = 0;
        }
        fwrite(val, sizeof(char), m, ho);
        if(feof(hi)) break;
    }

    fclose(hi);
    fclose(ho);

    return 0;
}
