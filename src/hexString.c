/*
 *  hexString.c
 *
 *  Created by Richard Murphy on 3/7/10.
 *  Copyright 2010 McKenzie-Murphy. All rights reserved.
 *
 */

#include "hexString.h"

static uint8_t
nibbleFromChar(char c)
{
	if(c >= '0' && c <= '9') return c - '0';
	if(c >= 'a' && c <= 'f') return c - 'a' + 10;
	if(c >= 'A' && c <= 'F') return c - 'A' + 10;
	return 255;
}

char
*hexStringToString(char *inhex)
{
	char *retval;
	uint8_t *p;
	int len, i;

    len = strlen(inhex) / 2;
	retval = malloc(len+1);
	for(i=0, p = (uint8_t *) inhex; i<len; i++) {
		retval[i] = (char)(nibbleFromChar(*p) << 4) | nibbleFromChar(*(p+1));
		p += 2;
	}
    retval[len] = 0;
	return retval;
}
