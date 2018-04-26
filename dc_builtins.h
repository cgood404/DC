#ifndef dc_builtins_h
#define dc_builtins_h

#include "dc.h"
#include "dc_token.h"
#include "dc_lexer.h"
#include "dc_parser.h"

int define();
int lambda();
int print();
int run();
void exit();

#endif