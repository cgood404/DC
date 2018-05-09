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
    function_table = malloc(sizeof(Function));
    variable_table = malloc(sizeof(Variable));
    function_table_size = 0;
    function_table_max = 1;

    variable_table_size = 0;
    variable_table_max = 1;
    return 1;
}

Variable *allocateFunction(char *name, char **args, int argsize, int start, int end){
    Function *func = malloc(sizeof(Function));
    func -> arguments = malloc(argsize * sizeof(Variable));

    for(int i = 0; i < argsize; i++){
        strcpy(func -> arguments[i].name, args[i]);
    }

    func -> code = malloc((end - start) * sizeof(Token));
    for(int i = 0; i < end - start; i++){
        memcpy(&(func -> code)[i], &file_tokens[start + i], sizeof(Token));
    }

    Variable *functionVar = malloc(sizeof(Variable));
    strcpy(functionVar -> name, name);
    functionVar -> type = _Function;
    functionVar -> value.function = func;
    return functionVar;
}

Variable *addFunction(Variable *function){
    if(function_table_size >= function_table_max){
        Function *buffer = malloc((int) (sizeof(Function) * function_table_size * size_inc));
        memmove(buffer, function_table, (sizeof(Function) * function_table_size) + 0);

        free(function_table);
        function_table_max *= size_inc;
        function_table = buffer;
    }

    memmove(&function_table[function_table_size], function, sizeof(Function));

    function_table_size++;
    return &none;
}

Variable *runFunction(char *name){
    for(int i = 0; i < variable_table_size; i++){
        if(strcmp(name, variable_table[i].name) == 0 && variable_table[i].type == _Function){
            // return a copy of the variable, which can safely be free'd after done
            Variable *var = malloc(sizeof(Variable));
            memcpy(var, &variable_table[i], sizeof(Variable));
            return var;
        }
    }
    char *buffer = malloc(47 + MAX_INPUT_SIZE);
    sprintf(buffer, "SyntaxError: Variable with name: %s not defined", name);
    raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);

    return NULL;
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
            // return a copy of the variable, which can safely be free'd after done
            Variable *var = malloc(sizeof(Variable));
            memcpy(var, &variable_table[i], sizeof(Variable));
            return var;
        }
    }
    char *buffer = malloc(47 + MAX_INPUT_SIZE);
    sprintf(buffer, "SyntaxError: Variable with name: %s not defined", name);
    raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);

    return NULL;
}