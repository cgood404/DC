#ifndef lexer_dc_h
#define lexer_dc_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dc_token.h"
#include "dc_parser.h"
#include "dc_memory.h"
#include "dc.h"

extern Token *file_tokens;
extern char *filename;

void createTokens(void);
void printToken();
void lex();
void lexfile();
int matchToken();
void slice_str();
void replace();
int matchStart();
int addToFile();
void resetFile(void);

#endif