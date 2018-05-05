#include "dc_main.h"

Variable *define(){
    if(file_tokens[currentToken].type == -1){
        currentToken++;
        char *name = keywordGet(&file_tokens[currentToken]);

        // if variable is already declared, redefine it
        for(int i = 0; i < variable_table_size; i++){
            if(strcmp(variable_table[i].name, name)){
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
                eol(1);
                return 1;
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
        eol(1);
        return 1;
    }else{
        return 0;
    }
}

Variable *lambda(){
    if(file_tokens[currentToken].type == -1){

    }
    return 1;
}

Variable printsVar(Variable *variable){
    
}

Variable *prints(){
    if(file_tokens[currentToken].type == -1){
        currentToken++;
        if(file_tokens[currentToken].type == 1){
            printsVar(sol());
        }
    }
    return 1;
}

Variable *runs(){
    if(file_tokens[currentToken].type == -1){
        
    }
    return 1;
}

void exits(){
    // free all malloc'd memory and exit using given exit status, if any
    if(file_tokens[currentToken].type == -1 && strcmp(file_tokens[currentToken].keyword, "exit")){
        currentToken++;
        eol(1);
        if(file_tokens[currentToken].type == -2){
            int status = (int) numGet(&file_tokens[currentToken]);

            free(file_tokens);
            free(function_table);
            free(variable_table);

            exit(status);
        }else{
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
