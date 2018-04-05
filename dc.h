#ifndef main_dc_h
#define main_dc_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#include "dc_token.h"

struct dc_file {
    char *__name__;
    FILE *file;
};

void readfile(char *file_name);

#endif