#include "dc_parser.h"

//define, lambda, print, run, exit
unsigned int current = 0;
int parseFile(){
    while(!eof(&file_tokens[++current])){
        sol(&file_tokens[++current]);
    };
    return 2;
}

int eof(Token *token){
    return (token -> type == 19);
}

int sol(Token *token){
    if(token -> type == 1){
        return 1;
    }

    return 0;
}