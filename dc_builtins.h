#ifndef dc_builtins_h
#define dc_builtins_h

#include "dc.h"
#include "dc_token.h"
#include "dc_parser.h"
#include "dc_memory.h"

int define(int current);
int lambda(int current);
int print(int current);
int run(int current);
void exit(int current);

#endif