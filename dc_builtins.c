#include "dc_main.h"

int define(int current){
    if(file_tokens[current].type == -1){
        
    }
    return 0;
}

int lambda(int current){
    if(file_tokens[current].type == -1){

    }
    return 0;
}

int prints(int current){
    if(file_tokens[current].type == -1){

    }
    return 0;
}

int runs(int current){
    if(file_tokens[current].type == -1){
        
    }
    return 0;
}

void exits(int current){
    if(file_tokens[current].type == -1 && strcmp(file_tokens[current].keyword, "exit")){
        current++;
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
