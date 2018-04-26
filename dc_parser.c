#include "dc_parser.h"


unsigned int current = 0;
unsigned int temp_current = 0;

// Nothing below this line changes the "current" variable

void parserError(char *statement, int line, int column){
    raise(statement, filename, line, column);
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

int eof(Token *token){
    if(token -> type == 13){
        return 1;
    }
    return 0;
}

void *plus(Token *token){
    return 0;
}

void *min(Token *token){
    return 0;
}

void *mult(Token *token){
    return 0;
}

void *divs(Token *token){
    return 0;
}

void *mod(Token *token){
    return 0;
}

void *eql(Token *token){
    return 0;
}

void *noteql(Token *token){
    return 0;
}

void *sol(Token *token){
    current++;
    if(token -> type == 1){
        if(file_tokens[current].type == -1){
            // function calls, TODO
        }else if(file_tokens[current].type == 1){
            sol(&file_tokens[current]);
        }else if(file_tokens[current].type == 2){
            plus(&file_tokens[current]);
        }else if(file_tokens[current].type == 3){
            min(&file_tokens[current]);
        }else if(file_tokens[current].type == 4){
            mult(&file_tokens[current]);
        }else if(file_tokens[current].type == 5){
            divs(&file_tokens[current]);
        }else if(file_tokens[current].type == 6){
            mod(&file_tokens[current]);
        }else if(file_tokens[current].type == 6){
            eql(&file_tokens[current]);
        }else if(file_tokens[current].type == 6){
            noteql(&file_tokens[current]);
        }
    }else parserError("Expected Start of Line token \"(\"",
                        token -> line, token -> column);
}

int parseFile(){
    while(true){
        if(eof(&file_tokens[++current])){
            return EXIT_SUCCESS;
        }
        sol(&file_tokens[++current]);
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