#ifndef lexer_dc_h
#define lexer_dc_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dc_token.h"
#include "dc_parser.h"
#include "dc.h"

extern Token *file_tokens;

void createTokens(void);
void printToken(Token *token);
void lex(char *line, int length);
void lexfile(char *file_name);
int matchToken(Token *token, char *statement, int length);
void slice_str(char *str, char *buffer, int start, int end);
void replace(char* src, int src_length, char oldchar, char newchar);
int matchStart(char *first, char *second, int first_length, int secnod_length);
int addToFile(Token *token);
void resetFile();

#endif