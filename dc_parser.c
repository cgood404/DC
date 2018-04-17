#include "dc_parser.h"

//define, lambda, print, run, exit
unsigned int current = 0;
int parseFile(){
    // while(!eof(&file_tokens[++current])){
    //     sol(&file_tokens[++current]);
    // };
    // return 2;
}

void parserError(char *statement){
    printf("%s\n", statement);
    exit(EXIT_FAILURE);
}

int eof(Token *token){
    if(token -> type == 19){
        printf("Found end of file\n");
        return 1;
    }
    return 0;
}

int sol(Token *token){
    if(token -> type == 1){
        printf("Found start of line\n");
        
        return 1;
    }

    return 0;
}