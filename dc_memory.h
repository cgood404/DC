#ifndef memory_dc_h
#define memory_dc_h

#include "dc_token.h"
#include "dc_parser.h"
#include "dc_builtins.h"
#include "dc.h"

typedef struct {
    char *name;
    Token *code;
} Function;

typedef struct {
    char *name;
    void *value;
    int type;
} Variable;

extern Function function_table[];
extern Variable variable_table[];

#endif