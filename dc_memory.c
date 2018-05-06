#include "dc_main.h"

Function *function_table;
Variable *variable_table;
unsigned long function_table_size;
unsigned long function_table_max;

unsigned long variable_table_size;
unsigned long variable_table_max;

Variable none = {.name = "none", .type = _none, .value = {.num = 0}};
Variable True = {.name = "True", .type = _Boolean, .value = {.boolean = 1}};
Variable False = {.name = "False", .type = _Boolean, .value = {.boolean = 0}};

int createTables(){
    function_table = malloc(sizeof(Variable));
    variable_table = malloc(sizeof(Function));
    function_table_size = 0;
    function_table_max = 1;

    variable_table_size = 0;
    variable_table_max = 1;
    return 1;
}

int addFunction(Function *function){
    if(function_table_size >= function_table_max){
        Function *buffer = malloc((int) (sizeof(Function) * function_table_size * size_inc));
        memmove(buffer, function_table, (sizeof(Function) * function_table_size) + 0);

        free(function_table);
        function_table_max *= size_inc;
        function_table = buffer;
    }

    memmove(&function_table[function_table_size], function, sizeof(*function));

    function_table_size++;
    return 1;
}

int addVariable(Variable *variable){
    if(variable_table_size >= variable_table_max){
        Variable *buffer = malloc((int) (sizeof(Variable) * variable_table_size * size_inc));
        memmove(buffer, variable_table, (sizeof(Variable) * variable_table_size) + 0);

        free(variable_table);
        variable_table_max *= size_inc;
        variable_table = buffer;
    }

    memmove(&variable_table[variable_table_size], variable, sizeof(*variable));

    variable_table_size++;
    return 1;
}

Variable *getVarByName(char *name){
    for(int i = 0; i < variable_table_size; i++){
        if(strcmp(name, variable_table[i].name) == 0){
            return &variable_table[i];
        }
    }
    char *buffer = malloc(47 + MAX_INPUT_SIZE);
    sprintf(buffer, "VariableError: Variable with name: %s not defined", name);
    raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);

    return NULL;
}