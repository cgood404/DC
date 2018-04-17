#include "dc.h"

void readfile(char *file_name){
    lexfile(file_name);
    parseFile();
    for(int i = 0; i < file_size; i++){
        printToken(&file_tokens[i]);
    }
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
        char *inputstr = malloc(MAX_INPUT_SIZE);
        while(true){
            printf(">> ");
            fgets(inputstr, MAX_INPUT_SIZE, stdin);
            lex(inputstr, strlen(inputstr));
            parseFile();
        }
        
    }
    return 0;
}