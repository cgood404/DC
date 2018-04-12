#include "dc.h"
#include "dc_token.h"
#include "dc_lexer.h"

#define MAX_INPUT_SIZE 256


void readfile(char *file_name){
    FILE *file = fopen(file_name, "r");
    if(file == NULL || file <= 0){
        printf("FileNotFoundError: %s\n", file_name);
        exit(1);
    }
    
    fclose(file);
}

void raise(char *exception, int line, int column){
    exit(1);
}

int main(int argc, char **argv){
    createTokens();
    if(argc > 1 && argv[1]){ // if user specifies a file to open
        readfile(argv[1]);
    }
    else{ // if user wants a command line
        printf("DC v0.0.1\nNo copyright, no money back, no nothin\'\nPress ^C or type (exit) to exit\n\n");
        while(true){
            char *inputstr = malloc(MAX_INPUT_SIZE);
            printf(">> ");
            fgets(inputstr, MAX_INPUT_SIZE, stdin);
            lex(inputstr, strlen(inputstr));
        }
        
    }
    return 0;
}