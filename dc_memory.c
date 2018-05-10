#include "dc_main.h"

Function *function_table;
Variable *variable_table;

VarStack *var_stack;

unsigned long function_table_size;
unsigned long function_table_max;

unsigned long variable_table_size;
unsigned long variable_table_max;

char *reservedKeywords[] = {"define", "lambda", "print", "println", "run", "loop",
                    "delete", "exit", "none", "True", "False"};
int reservedKeywordSize = 11;

Variable none = {.name = "none", .type = _none, .value = {.num = 0}};
Variable True = {.name = "True", .type = _Boolean, .value = {.boolean = 1}};
Variable False = {.name = "False", .type = _Boolean, .value = {.boolean = 0}};

int createTables(){
    function_table = malloc(sizeof(Function));
    variable_table = malloc(sizeof(Variable));

    var_stack = malloc(sizeof(VarStack));

    function_table_size = 0;
    function_table_max = 1;

    variable_table_size = 0;
    variable_table_max = 1;

    var_stack -> cap = 0;
    var_stack -> top = -1;
    var_stack -> stack = malloc(sizeof(Variable));

    return 1;
}

void push(Variable *var){
    if(var_stack -> top == var_stack -> cap){
        Variable *var_stack_backup = malloc(sizeof(*(var_stack -> stack)));
        memmove(var_stack_backup, var_stack -> stack, sizeof(*(var_stack -> stack)));

        var_stack -> stack = malloc(sizeof(*var_stack_backup) * size_inc);
        memcpy(var_stack -> stack, var_stack_backup, sizeof(*var_stack_backup));
    }

    memmove(&var_stack -> stack[++var_stack -> top], var, sizeof(Variable));
}

void pop(){
    if(var_stack -> top == -1){
        raise("StackUnderflowError: Cannot pop variable off stack, stack is empty",
            filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
    }else if(var_stack -> top == var_stack -> cap / 2){
        Variable *var_stack_backup = malloc(sizeof(*(var_stack -> stack)));
        memmove(var_stack_backup, var_stack -> stack, sizeof(*(var_stack -> stack)));

        var_stack -> stack = malloc((size_t) (sizeof(*var_stack_backup) / size_inc));
        memcpy(var_stack -> stack, var_stack_backup, sizeof(*var_stack_backup));
    }
    var_stack -> top--;
}

short stackIsEmpty(){
    if(var_stack -> top > -1){
        return 0;
    }
    return 1;
}

Variable *localdefine(char *funcName, char *name, Token *value){
    if(strcmp(name, funcName) == 0){
            char *buffer = malloc(61 + MAX_INPUT_SIZE);
            sprintf(buffer, "OverwriteError: Cannot overwrite variable of callable: \"%s\"",
                name);
            raise(buffer, filename, value -> line, value -> column);
    }
    for(int i = 0; i < reservedKeywordSize; i++){
        if(strcmp(name, reservedKeywords[i]) == 0){
            char *buffer = malloc(54 + MAX_INPUT_SIZE);
            sprintf(buffer, "OverwriteError: Cannot initialize variable with reserved name: %s",
                name);
            raise(buffer, filename, value -> line, value -> column);
        }
    }
    Variable *var = malloc(sizeof(Variable));

    if(value -> type == _StringToken){
        var -> type = _String;
        strcpy(var -> value.string, strGet(value));
    }else if(value -> type == _NumberToken){
        var -> type = _Number;
        var -> value.num = numGet(value);
    }else if(value -> type == _VarToken){
        var = getVarByName(keywordGet(value));
    }else if(value -> type == _SOL){
        var = sol();
        strcpy(var -> name, name);
    }else{
        char *buffer = malloc(53 + MAX_INPUT_SIZE);
        sprintf(buffer, "SyntaxError: Expected String or Number, received \"%s\" of type %d",
        value -> keyword, value -> type);
        raise(buffer, filename, value -> line, value -> column);
    }

    strcpy(var -> name, name);
    push(var);
    return var;
}

Variable *allocateFunction(char **args, int argsize, int start, int end){
    Function *func = malloc(sizeof(Function));
    func -> arguments = malloc(argsize * sizeof(size_t));
    func -> argsize = argsize;

    for(int i = 0; i < argsize; i++){
        func -> arguments[i] = malloc(strlen(args[i]) * sizeof(char));
        strcpy(func -> arguments[i], args[i]);
    }

    func -> code = malloc((end - start + 1) * sizeof(Token));
    for(int i = 0; i < end - start; i++){
        memcpy(&(func -> code)[i], &file_tokens[start + i], sizeof(Token));
    }
    memcpy(&(func -> code)[end-start], &EOFS, sizeof(Token));

    Variable *functionVar = malloc(sizeof(Variable));
    functionVar -> type = _Function;
    functionVar -> value.function = func;
    return functionVar;
}

Variable *runFunction(char *name){
    for(int i = 0; i < variable_table_size; i++){
        if(strcmp(name, variable_table[i].name) == 0 && variable_table[i].type == _Function){
            // local variables
            currentToken++;
            for(int j = 0; j < variable_table[i].value.function -> argsize; j++){
                if(file_tokens[currentToken].type == _VarToken ||
                        file_tokens[currentToken].type == _NumberToken ||
                        file_tokens[currentToken].type == _StringToken){
                    Variable *var = localdefine(name, variable_table[i].value.function -> arguments[j],
                            &file_tokens[currentToken]);
                    currentToken++;
                }else{
                    char *buffer = malloc(46 + MAX_INPUT_SIZE);
                    sprintf(buffer, "SyntaxError: Expected %d arguments, found %d",
                        variable_table[i].value.function -> argsize, j);
                    raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
                }
            }
            // context switch to function
            Token *main_tokens = file_tokens;
            int main_currentToken = currentToken;

            file_tokens = variable_table[i].value.function -> code;
            currentToken = 0;

            Variable *var = sol();
            // context switch back to main
            file_tokens = main_tokens;
            currentToken = main_currentToken;
            for(int j = 0; j < variable_table[i].value.function -> argsize; j++){
                pop();
            }
            return var;
        }
    }
    char *buffer = malloc(49 + MAX_INPUT_SIZE);
    sprintf(buffer, "SyntaxError: Function with name: %s not defined", name);
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
    if(!stackIsEmpty()){
        for(int i = 0; i <= var_stack -> top; i++){
            if(strcmp(name, var_stack -> stack[i].name) == 0 && var_stack -> stack[i].type != -1){
                // return a copy of the variable, which can safely be free'd after done
                Variable *var = malloc(sizeof(Variable));
                memcpy(var, &var_stack -> stack[i], sizeof(Variable));
                return var;
            }
        }
    }
    for(int i = 0; i < variable_table_size; i++){
        if(strcmp(name, variable_table[i].name) == 0 && variable_table[i].type != -1){
            // return a copy of the variable, which can safely be free'd after done
            Variable *var = malloc(sizeof(Variable));
            memcpy(var, &variable_table[i], sizeof(Variable));
            return var;
        }
    }
    char *buffer = malloc(61 + MAX_INPUT_SIZE);
    sprintf(buffer, "SyntaxError: Variable with name: %s not defined", name);
    raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);

    return NULL;
}