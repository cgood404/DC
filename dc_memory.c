#include "dc_memory.h"

struct _variable{
    char name[256];
    int type;
};
struct _function {
    char name[256];
    Variable arguments[MAX_FUNCTION_ARGS];
    Token code[MAX_FUNCTION_SIZE];
};