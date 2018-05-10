#include "dc_main.h"

void readfile(char *file_name){
    lexfile(file_name);
    // for(int i = 0; i < file_size; i++){
    //     printToken(&file_tokens[i]);
    // }
    parseFile();
}

void raise(char *error_statement, char *filename, int line, int column){
    column++;
    printf(ANSI_COLOR_RED "Traceback Error in source file: \"%s\" at line: %d, column: %d\n" ANSI_COLOR_RESET, filename, line, column);
    printf(ANSI_COLOR_RED "%s\n" ANSI_COLOR_RESET, error_statement);
    printf(ANSI_COLOR_RED "System Failure, Exiting...\n" ANSI_COLOR_RESET);
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv){
    _init_();
    if(argc > 1 && argv[1]){ // if user specifies a file to open
        readfile(argv[1]);
    }
    else{ // if user wants a command line
        printf("DC v1.3.0\nNo copyright, no money back, no nothin\'\nPress ^C or type (exit) to exit\n\n");
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