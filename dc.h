#ifndef main_DC_h
#define main_DC_h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

const char *KEYWORDS[] = {"print", "conjure", "string", "num", "bool"};

struct variable {
    char *name;
    int pvalue;
};
struct dc_file {
    char *__name__;
    FILE *file;
};

void readfile(char *file_name);

#endif