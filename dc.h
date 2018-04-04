#ifndef main_DC_h
#define main_DC_h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

// typedef struct _TOKEN {
//     char *keyword;
//     int value_ptr;
// } TOKEN;
enum {
    Plus, Min, Mult, Div, Mod, Inc, Dec,
    Assn, Eql, NotEql, If, Else,
    Func, Main, Var, Print, EOL
};
struct dc_file {
    char *__name__;
    FILE *file;
};

void readfile(char *file_name);

#endif