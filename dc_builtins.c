#include "dc_main.h"

Variable *define(){
    printf("Define Function\n");
    if(file_tokens[currentToken].type == -1){
        currentToken++;
        char *name = keywordGet(&file_tokens[currentToken]);
        if(strcmp(name, "none") == 0){
            raise("Cannot overwrite none variable", filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }
        // if variable is already declared, redefine it
        for(int i = 0; i < variable_table_size; i++){
            if(strcmp(variable_table[i].name, name) == 0){
                Variable *var = malloc(sizeof(Variable));
                strcpy(var -> name, name);
                currentToken++;

                if(file_tokens[currentToken].type == -2){
                    var -> type = 2;
                    var -> value.num = numGet(&file_tokens[currentToken]);
                }else if(file_tokens[currentToken].type == -3){
                    var -> type = 3;
                    strcpy(var -> value.string, strGet(&file_tokens[currentToken]));
                }else{
                    char *buffer = malloc(53 + MAX_INPUT_SIZE);
                    sprintf(buffer, "Expected String or Number, received \"%s\" of type %d",
                    file_tokens[currentToken].keyword, file_tokens[currentToken].type);
                    raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
                }

                variable_table[i] = *var;
                currentToken++;
                eol(1);
                return var;
            }
        }

        Variable *var = malloc(sizeof(Variable));
        strcpy(var -> name, name);
        currentToken++;

        if(file_tokens[currentToken].type == -2){
            var -> type = 2;
            var -> value.num = numGet(&file_tokens[currentToken]);
        }else if(file_tokens[currentToken].type == -3){
            var -> type = 3;
            strcpy(var -> value.string, strGet(&file_tokens[currentToken]));
        }else{
            char *buffer = malloc(53 + MAX_INPUT_SIZE);
            sprintf(buffer, "Expected String or Number, received \"%s\" of type %d",
            file_tokens[currentToken].keyword, file_tokens[currentToken].type);
            raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }

        addVariable(var);
        currentToken++;
        eol(1);
        return var;
    }else{
        return &none;
    }
}

Variable *lambda(){
    if(file_tokens[currentToken].type == -1){

    }
    return &none;
}

void printsVar(Variable *var){
    if(var -> type == 2){
        printf("%Lg\n", var->value.num);
    }if(var -> type == 3){
        printf("%s\n", var->value.string);
    }
}

Variable *prints(){
    if(file_tokens[currentToken].type == -1){
        currentToken++;
        if(file_tokens[currentToken].type == 1){
            printsVar(sol());
        }else if(file_tokens[currentToken].type == -1){

        }
    }
    return &none;
}

Variable *runs(){
    if(file_tokens[currentToken].type == -1){
        
    }
    return &none;
}

void exits(){
    // free all malloc'd memory and exit using given exit status, if any
    if(strcmp(file_tokens[currentToken].keyword, "exit") == 0){
        currentToken++;
        if(file_tokens[currentToken].type == -2){
            int status = (int) numGet(&file_tokens[currentToken]);

            free(file_tokens);
            free(function_table);
            free(variable_table);

            exit(status);
        }else{
            eol(1);

            free(file_tokens);
            free(function_table);
            free(variable_table);

            exit(EXIT_SUCCESS);
        }
    }else{
        char *buffer = malloc(36 + MAX_INPUT_SIZE);
        sprintf(buffer, "Expected exit token, received \"%s\"",
        file_tokens[currentToken].keyword);
        raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
    }
}
