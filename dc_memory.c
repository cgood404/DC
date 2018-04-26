#include "dc_memory.h"

struct _variable{
    char name[MAX_INPUT_SIZE];
    int type;
};
struct _function {
    char name[MAX_INPUT_SIZE];
    Variable arguments[MAX_FUNCTION_ARGS];
    Token code[MAX_FUNCTION_SIZE];
};