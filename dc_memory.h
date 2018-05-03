#ifndef memory_dc_h
#define memory_dc_h

#include "dc_parser.h"
#include "dc_builtins.h"
#include "dc.h"
#include "dc_token.h"

#define MAX_FUNCTION_ARGS 16
#define MAX_FUNCTION_SIZE 256

typedef struct _variable Variable;
typedef struct _function Function;
typedef union __VARIABLE  _VARIABLE;
extern Function *function_table;
extern Variable *variable_table;

#endif