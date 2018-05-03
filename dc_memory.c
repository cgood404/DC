#include "dc_memory.h"

union __VARIABLE { // unions share memory space
    char string[MAX_INPUT_SIZE];
    num_t num;
};

struct _variable {
    char name[MAX_INPUT_SIZE];
    int type;
    _VARIABLE value;
};

struct _function {
    char name[MAX_INPUT_SIZE];
    Variable arguments[MAX_FUNCTION_ARGS];
    Token code[MAX_FUNCTION_SIZE];
};