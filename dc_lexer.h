#ifndef lexer_dc_h
#define lexer_dc_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dc_token.h"

#define true 1
#define false 0

void createTokens(void);
void printToken(Token token);
int lex(char *line, int length);
int matchToken(Token token, char *statement, int length);
void slice_str(const char *str, char *buffer, size_t start, size_t end);
int matchStart(char *first, char *second, int first_length, int secnod_length);

void sol(char* keyword, int length);
void plus(char* keyword, int length);
void min(char *keyword, int length);
void mult(char* keyword, int length);
void divide(char* keyword, int length);
void mod(char* keyword, int length);
void inc(char* keyword, int length);
void dec(char* keyword, int length);
void assn(char* keyword, int length);
void eql(char* keyword, int length);
void noteql(char* keyword, int length);
void ifs(char* keyword, int length);
void thens(char* keyword, int length);
void elses(char* keyword, int length);
void eol(char* keyword, int length);
void eof(char* keyword, int length);

#endif