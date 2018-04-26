#include "dc_parser.h"


unsigned int current = 0;
unsigned int temp_current = 0;
int parseFile(){
    while(true){
        if(eof(&file_tokens[++current])){
            return EXIT_SUCCESS;
        }else if(sol(&file_tokens[current])){
            //do stuff
        }else parserError("Expected Start of Line token \"(\"",
                        file_tokens[current].line, file_tokens[current].column);
    };
    return EXIT_SUCCESS;
}

int parse(Token *tokens){
    temp_current = 0;
    while(true){
        if(eof(&tokens[++temp_current])){
            return EXIT_SUCCESS;
        }else if(sol(&tokens[temp_current])){
            //do stuff
        }else parserError("Expected Start of Line token \"(\"",
                        tokens[temp_current].line, tokens[temp_current].column);
    };
}

// Nothing below this line changes the "current" variable

void parserError(char *statement, int line, int column){
    perror(statement);
    exit(EXIT_FAILURE);
}

// returns string (type -3), can be formatted in the future with escape characters
char *strGet(Token *token){
    return token -> keyword;
}

// returns number (type -2), can be added to in order to prevent overflow, improper tokens, etc
long double numGet(Token *token){
    long double num = 0;
    num = strtold(token -> keyword, NULL);
    return num;
}

// returns keyword (type -1), reserved words such as "define", "lambda", etc. OR
// user defined functions and/or variables
char *keywordGet(Token *token){
    return token -> keyword;
}

int sol(Token *token){
    
}