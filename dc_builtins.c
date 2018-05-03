#include "dc_main.h"

int define(int current){
    if(file_tokens[current].type == -1){

    }
    return current;
}

int lambda(int current){
    if(file_tokens[current].type == -1){

    }
    return current;
}

int prints(int current){
    if(file_tokens[current].type == -1){

    }
    return current;
}

int runs(int current){

    if(file_tokens[current].type == -1){
        
    }
    return current;
}

void exits(int current){
    // free all malloc'd memory and exit using given exit status, if any
    if(file_tokens[current].type == -1 && strcmp(file_tokens[current].keyword, "exit")){
        current++;
        eol(1);
        if(file_tokens[current].type == -2){
            int status = (int) numGet(file_tokens[current]);

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
    }
}
