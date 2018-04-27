#include "dc_parser.h"

#define num_t long double


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
num_t numGet(Token *token){
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
        current++;
        printf("End of file\n");
        return 1;
    }
    return 0;
}

num_t plus(Token *token){
    if(token -> type == 2){
        current++;
        num_t total;
        printf("Plus Function\n");
        if(file_tokens[current].type == -2){
            total = numGet(&file_tokens[current]);
        }else if(file_tokens[current].type == -1){
            // variable stuff
            total = 0;
        }else{
            char *buffer = malloc(67 + MAX_INPUT_SIZE);
            sprintf(buffer, "Unexpected token in function \"+\", expected number or variable of type number, found:  %s",
            file_tokens[current].keyword);
            raise(buffer, filename, file_tokens[current].line, file_tokens[current].column);
        }

        current++;
        if(file_tokens[current].type == -1 || file_tokens[current].type == -2){
            while(file_tokens[current].type != 12){
                if(file_tokens[current].type == -2){
                    total += numGet(&file_tokens[current]);
                }else if(file_tokens[current].type == -1){
                    // variable stuff
                    total += 0;
                }else{
                    char *buffer = malloc(67 + MAX_INPUT_SIZE);
                    sprintf(buffer, "Unexpected token in function \"+\", expected number or variable of type number, found:  %s",
                    file_tokens[current].keyword);
                    raise(buffer, filename, file_tokens[current].line, file_tokens[current].column);
                }
                current++;
            }
            printf("%LG\n", total);
        }else{
            char *buffer = malloc(67 + MAX_INPUT_SIZE);
            sprintf(buffer, "Expected at least two arguments in function \"+\", found:  %s",
            file_tokens[current].keyword);
            raise(buffer, filename, file_tokens[current].line, file_tokens[current].column);
        }
    }
}

num_t min(Token *token){
    if(token -> type == 3){
        current++;
        num_t total;
        printf("Minus Function\n");
        if(file_tokens[current].type == -2){
            total = numGet(&file_tokens[current]);
        }else if(file_tokens[current].type == -1){
            // variable stuff
            total = 0;
        }else{
            char *buffer = malloc(67 + MAX_INPUT_SIZE);
            sprintf(buffer, "Unexpected token in function \"-\", expected number or variable of type number, found:  %s",
            file_tokens[current].keyword);
            raise(buffer, filename, file_tokens[current].line, file_tokens[current].column);
        }

        current++;
        if(file_tokens[current].type == -1 || file_tokens[current].type == -2){
            while(file_tokens[current].type != 12){
                if(file_tokens[current].type == -2){
                    total -= numGet(&file_tokens[current]);
                }else if(file_tokens[current].type == -1){
                    // variable stuff
                    total -= 0;
                }else{
                    char *buffer = malloc(67 + MAX_INPUT_SIZE);
                    sprintf(buffer, "Unexpected token in function \"-\", expected number or variable of type number, found:  %s",
                    file_tokens[current].keyword);
                    raise(buffer, filename, file_tokens[current].line, file_tokens[current].column);
                }
                current++;
            }
            printf("%LG\n", total);
        }else{
            char *buffer = malloc(67 + MAX_INPUT_SIZE);
            sprintf(buffer, "Expected at least two arguments in function \"-\", found:  %s",
            file_tokens[current].keyword);
            raise(buffer, filename, file_tokens[current].line, file_tokens[current].column);
        }
    }
}

num_t divs(Token *token){
    if(token -> type == 3){
        current++;
        num_t total;
        printf("Divide Function\n");
        if(file_tokens[current].type == -2){
            total = numGet(&file_tokens[current]);
        }else if(file_tokens[current].type == -1){
            // variable stuff
            total = 0;
        }else{
            char *buffer = malloc(67 + MAX_INPUT_SIZE);
            sprintf(buffer, "Unexpected token in function \"/\", expected number or variable of type number, found:  %s",
            file_tokens[current].keyword);
            raise(buffer, filename, file_tokens[current].line, file_tokens[current].column);
        }

        current++;
        if(file_tokens[current].type == -1 || file_tokens[current].type == -2){
            while(file_tokens[current].type != 12){
                if(file_tokens[current].type == -2){
                    total /= numGet(&file_tokens[current]);
                }else if(file_tokens[current].type == -1){
                    // variable stuff
                    total /= 0;
                }else{
                    char *buffer = malloc(67 + MAX_INPUT_SIZE);
                    sprintf(buffer, "Unexpected token in function \"/\", expected number or variable of type number, found:  %s",
                    file_tokens[current].keyword);
                    raise(buffer, filename, file_tokens[current].line, file_tokens[current].column);
                }
                current++;
            }
            printf("%LG\n", total);
        }else{
            char *buffer = malloc(67 + MAX_INPUT_SIZE);
            sprintf(buffer, "Expected at least two arguments in function \"/\", found:  %s",
            file_tokens[current].keyword);
            raise(buffer, filename, file_tokens[current].line, file_tokens[current].column);
        }
    }
}

num_t mult(Token *token){
    if(token -> type == 3){
        current++;
        num_t total;
        printf("Multiply Function\n");
        if(file_tokens[current].type == -2){
            total = numGet(&file_tokens[current]);
        }else if(file_tokens[current].type == -1){
            // variable stuff
            total = 0;
        }else{
            char *buffer = malloc(67 + MAX_INPUT_SIZE);
            sprintf(buffer, "Unexpected token in function \"*\", expected number or variable of type number, found:  %s",
            file_tokens[current].keyword);
            raise(buffer, filename, file_tokens[current].line, file_tokens[current].column);
        }

        current++;
        if(file_tokens[current].type == -1 || file_tokens[current].type == -2){
            while(file_tokens[current].type != 12){
                if(file_tokens[current].type == -2){
                    total *= numGet(&file_tokens[current]);
                }else if(file_tokens[current].type == -1){
                    // variable stuff
                    total *= 0;
                }else{
                    char *buffer = malloc(67 + MAX_INPUT_SIZE);
                    sprintf(buffer, "Unexpected token in function \"*\", expected number or variable of type number, found:  %s",
                    file_tokens[current].keyword);
                    raise(buffer, filename, file_tokens[current].line, file_tokens[current].column);
                }
                current++;
            }
            printf("%LG\n", total);
        }else{
            char *buffer = malloc(67 + MAX_INPUT_SIZE);
            sprintf(buffer, "Expected at least two arguments in function \"*\", found:  %s",
            file_tokens[current].keyword);
            raise(buffer, filename, file_tokens[current].line, file_tokens[current].column);
        }
    }
}

num_t mod(Token *token){
    if(token -> type == 6){
        current++;
        printf("Modulus Function\n");
        return 1;
    }
    return 0;
}

int eql(Token *token){
    if(token -> type == 7){
        current++;
        printf("End of file\n");
        return 1;
    }
    return 0;
}

int noteql(Token *token){
    if(token -> type == 8){
        current++;
        printf("End of file\n");
        return 1;
    }
    return 0;
}

num_t sol(Token *token){
    if(token -> type == 1){
        current++;
        printf("Start of line\n");

        if(file_tokens[current].type == -1){
            // function calls, TODO
        }else if(file_tokens[current].type == 1){
            return sol(&file_tokens[current]);
        }else if(file_tokens[current].type == 2){
            return plus(&file_tokens[current]);
        }else if(file_tokens[current].type == 3){
            return min(&file_tokens[current]);
        }else if(file_tokens[current].type == 4){
            return mult(&file_tokens[current]);
        }else if(file_tokens[current].type == 5){
            return divs(&file_tokens[current]);
        }else if(file_tokens[current].type == 6){
            return mod(&file_tokens[current]);
        }else if(file_tokens[current].type == 7){
            return eql(&file_tokens[current]);
        }else if(file_tokens[current].type == 8){
            return noteql(&file_tokens[current]);
        }else{
            char *buffer = malloc(40 + MAX_INPUT_SIZE);
            sprintf(buffer, "Invalid statement after start of line: %s", file_tokens[current].keyword);
            parserError(buffer, token -> line, token -> column);
        }
    }else{
        char *buffer = malloc(40 + MAX_INPUT_SIZE);
        sprintf(buffer, "Expected start of line token: \"%s\", found: \"%s\"",
                    SOL.keyword, file_tokens[current].keyword);
        parserError(buffer, token -> line, token -> column);
    }
}

int parseFile(){
    while(true){
        current++;
        if(eof(&file_tokens[current])){
            return EXIT_SUCCESS;
        }
        sol(&file_tokens[current]);
    };
    return EXIT_SUCCESS;
}