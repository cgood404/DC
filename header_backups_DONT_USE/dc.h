#ifndef main_dc_h
#define main_dc_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#include "dc_lexer.h"
#include "dc_parser.h"
#include "dc_token.h"


#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define MAX_INPUT_SIZE 255

struct dc_file {
    char *__name__;
    FILE *file;
};

void readfile(char *file_name);
void raise(char *exception, char *filename, int line, int column);

#endif