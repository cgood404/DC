#include "dc_main.h"

Function *function_table;
Variable *variable_table;

int createTables(){
    function_table = malloc(sizeof(Variable));
    variable_table = malloc(sizeof(Function));
    unsigned long function_table_size = 0;
    unsigned long function_table_max = 1;

    unsigned long variable_table_size = 0;
    unsigned long variable_table_max = 1;
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