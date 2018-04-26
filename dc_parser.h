#ifndef parser_dc_h
#define parser_dc_h

#include "dc.h"
#include "dc_token.h"
#include "dc_lexer.h"
#include "dc_builtins.c"
#include "dc_memory.h"

int parseFile();
int parse();
void parserError(char *statement, int line, int column);

char *strGet();
long double numGet();
char *keywordGet();

#endif