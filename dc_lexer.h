#ifndef lexer_dc_h
#define lexer_dc_h

#include "dc.h"
#include "dc_token.h"

void createTokens(void);

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
void define(char* keyword, int length);
void print(char* keyword, int length);
void run(char* keyword, int length);
void eol(char* keyword, int length);
void eof(char* keyword, int length);

#endif