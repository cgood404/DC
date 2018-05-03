#ifndef MAX_INPUT_SIZE
#define MAX_INPUT_SIZE 255
#endif

#ifndef memory_dc_h
#define memory_dc_h

#include "dc_parser.h"
#include "dc_builtins.h"
#include "dc.h"
#include "dc_token.h"

#define MAX_FUNCTION_ARGS 16
#define MAX_FUNCTION_SIZE 256
#define num_t long double

typedef struct _variable Variable;
typedef struct _function Function;
typedef union __VARIABLE  _VARIABLE;
extern Function *function_table;
extern Variable *variable_table;
extern unsigned long sizeofVariable;

union __VARIABLE { // unions share memory space
    char string[MAX_INPUT_SIZE];
    num_t num;
};

struct _variable {
    char name[MAX_INPUT_SIZE];
    int type;
    union __VARIABLE value;
};

struct _function {
    char name[MAX_INPUT_SIZE];
    Variable arguments[MAX_FUNCTION_ARGS];
    Token code[MAX_FUNCTION_SIZE];
};
#endif