#ifndef parser_dc_h
#define parser_dc_h

#include "dc.h"
#include "dc_token.h"
#include "dc_lexer.h"

int parseFile();
int sol();
int inc();
int dec();
int pluseql();
int mineql();
int multeql();
int diveql();
int plus();
int min();
int mult();
int div();
int mod();
int eql();
int noteql();
int ifs();
int then();
int elses();
int eol();
int eof();


#endif