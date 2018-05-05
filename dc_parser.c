#include "dc_main.h"


unsigned int currentToken = 0;
unsigned int temp_current = 0;

void parserError(char *statement, int line, int column){
    raise(statement, filename, line, column);
}

// returns string (type -3), can be formatted in the future with escape characters
char *strGet(Token *token){
    if(token -> type == -3){
        return token -> keyword;
    }else{
        char *buffer = malloc(47 + MAX_INPUT_SIZE);
        sprintf(buffer, "StringError: Expected string or expression resolving to string, received %s",
        file_tokens[currentToken].keyword);
        raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
    }

    return NULL;
}

// returns number (type -2), can be added to in order to prevent overflow, improper tokens, etc
num_t numGet(Token *token){
    if(token -> type == -2){
        long double num = 0;
        num = strtold(token -> keyword, NULL);
        return num;
    }else{
        char *buffer = malloc(81 + MAX_INPUT_SIZE);
        sprintf(buffer, "ArithmeticError: Expected number or expression resolving to number, received %s",
        file_tokens[currentToken].keyword);
        raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
    }

    return 0;
}

// returns keyword (type -1), reserved words such as "define", "lambda", etc. OR
// user defined functions and/or variables
char *keywordGet(Token *token){
    if(token -> type == -1){
        return token -> keyword;
    }else{
        char *buffer = malloc(63 + MAX_INPUT_SIZE);
        sprintf(buffer, "SyntaxError: Expected variable or function name, received %s",
        file_tokens[currentToken].keyword);
        raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
    }

    return NULL;
}


int eol(short raiseEx){
    if(file_tokens[currentToken].type == 12){
        currentToken++;
        return 1;
    }else{
        if(raiseEx){
            char *buffer = malloc(54 + MAX_INPUT_SIZE);
            sprintf(buffer, "SyntaxError: Unclosed statement, received \"%s\" instead.",
            file_tokens[currentToken].keyword);
            raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }else{
            return 0;
        }
    }
    return 0;
}

int eof(){
    if(file_tokens[currentToken].type == 13){
        currentToken++;
        printf("End of file\n");
        return 1;
    }
    return 0;
}

Variable *plus(){
    if(file_tokens[currentToken].type == 2){
        currentToken++;
        num_t total;
        if(file_tokens[currentToken].type == -2){
            total = numGet(&file_tokens[currentToken]);
        }else if(file_tokens[currentToken].type == -1){
            // variable stuff
            total = 0;
        }else if(file_tokens[currentToken].type == 1){
            Variable *t_var = sol();
            if(t_var -> type == 2){
                total = t_var -> value.num;
            }else{
                char *buffer = malloc(107 + MAX_INPUT_SIZE);
                sprintf(buffer, "ArithmeticError: Unexpected token in function \"+\", expected number or variable of type number, found:  %s",
                file_tokens[currentToken].keyword);
                raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
            }
        }else{
            char *buffer = malloc(107 + MAX_INPUT_SIZE);
            sprintf(buffer, "ArithmeticError: Unexpected token in function \"+\", expected number or variable of type number, found:  %s",
            file_tokens[currentToken].keyword);
            raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }

        currentToken++;
        if(file_tokens[currentToken].type == -2){
            total += numGet(&file_tokens[currentToken]);
        }else if(file_tokens[currentToken].type == -1){
            // variable stuff
            total += 0;
        }else if(file_tokens[currentToken].type == 1){
            Variable *t_var = sol();
            if(t_var -> type == 2){
                total = t_var -> value.num;
            }else{
                char *buffer = malloc(107 + MAX_INPUT_SIZE);
                sprintf(buffer, "ArithmeticError: Unexpected token in function \"+\", expected number or variable of type number, found:  %s",
                file_tokens[currentToken].keyword);
                raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
            }
        }else{
            char *buffer = malloc(107 + MAX_INPUT_SIZE);
            sprintf(buffer, "ArithmeticError: Unexpected token in function \"+\", expected number or variable of type number, found:  %s",
            file_tokens[currentToken].keyword);
            raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }
        currentToken++;

        Variable *var = malloc(sizeof(Variable));
        var -> value.num = total;
        var -> type = 2;
        eol(1);

        return var;
    }else{
        char *buffer = malloc(52 + MAX_INPUT_SIZE);
        sprintf(buffer, "ArithmeticError: Expected function \"+\", found:  %s",
        file_tokens[currentToken].keyword);
        raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
    }
    return NULL;
}

Variable *min(){
    if(file_tokens[currentToken].type == 3){
        currentToken++;
        num_t total;
        if(file_tokens[currentToken].type == -2){
            total = numGet(&file_tokens[currentToken]);
        }else if(file_tokens[currentToken].type == -1){
            // variable stuff
            total = 0;
        }else{
            char *buffer = malloc(107 + MAX_INPUT_SIZE);
            sprintf(buffer, "ArithmeticError: Unexpected token in function \"-\", expected number or variable of type number, found:  %s",
            file_tokens[currentToken].keyword);
            raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }

        currentToken++;
        if(file_tokens[currentToken].type == -1 || file_tokens[currentToken].type == -2){
            if(file_tokens[currentToken].type == -2){
                total -= numGet(&file_tokens[currentToken]);
            }else if(file_tokens[currentToken].type == -1){
                // variable stuff
                total -= 0;
            }else{
                char *buffer = malloc(107 + MAX_INPUT_SIZE);
                sprintf(buffer, "ArithmeticError: Unexpected token in function \"-\", expected number or variable of type number, found:  %s",
                file_tokens[currentToken].keyword);
                raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
            }
            currentToken++;

            Variable *var = malloc(sizeof(Variable));
            var -> value.num = total;
            var -> type = 2;
            eol(1);

            return var;
        }else{
            char *buffer = malloc(69 + MAX_INPUT_SIZE);
            sprintf(buffer, "ArithmeticError: Expected two arguments in function \"-\", found:  %s",
            file_tokens[currentToken].keyword);
            raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }
    }else{
        char *buffer = malloc(52 + MAX_INPUT_SIZE);
        sprintf(buffer, "ArithmeticError: Expected function \"-\", found:  %s",
        file_tokens[currentToken].keyword);
        raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
    }
    return NULL;
}

Variable *divs(){
    if(file_tokens[currentToken].type == 5){
        currentToken++;
        num_t total;
        if(file_tokens[currentToken].type == -2){
            total = numGet(&file_tokens[currentToken]);
        }else if(file_tokens[currentToken].type == -1){
            // variable stuff
            total = 0;
        }else{
            char *buffer = malloc(107 + MAX_INPUT_SIZE);
            sprintf(buffer, "ArithmeticError: Unexpected token in function \"/\", expected number or variable of type number, found:  %s",
            file_tokens[currentToken].keyword);
            raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }

        currentToken++;
        if(file_tokens[currentToken].type == -1 || file_tokens[currentToken].type == -2){
            if(file_tokens[currentToken].type == -2){
                total /= numGet(&file_tokens[currentToken]);
            }else if(file_tokens[currentToken].type == -1){
                // variable stuff
                total /= 1;
            }else{
                char *buffer = malloc(107 + MAX_INPUT_SIZE);
                sprintf(buffer, "ArithmeticError: Unexpected token in function \"/\", expected number or variable of type number, found:  %s",
                file_tokens[currentToken].keyword);
                raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
            }
            currentToken++;

            Variable *var = malloc(sizeof(Variable));
            var -> value.num = total;
            var -> type = 2;
            eol(1);

            return var;
        }else{
            char *buffer = malloc(69 + MAX_INPUT_SIZE);
            sprintf(buffer, "ArithmeticError: Expected two arguments in function \"/\", found:  %s",
            file_tokens[currentToken].keyword);
            raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }
    }else{
        char *buffer = malloc(52 + MAX_INPUT_SIZE);
        sprintf(buffer, "ArithmeticError: Expected function \"/\", found:  %s",
        file_tokens[currentToken].keyword);
        raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
    }
    return NULL;
}

Variable *mult(){
    if(file_tokens[currentToken].type == 4){
        currentToken++;
        num_t total;
        if(file_tokens[currentToken].type == -2){
            total = numGet(&file_tokens[currentToken]);
        }else if(file_tokens[currentToken].type == -1){
            // variable stuff
            total = 0;
        }else{
            char *buffer = malloc(107 + MAX_INPUT_SIZE);
            sprintf(buffer, "ArithmeticError: Unexpected token in function \"*\", expected number or variable of type number, found:  %s",
            file_tokens[currentToken].keyword);
            raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }

        currentToken++;
        if(file_tokens[currentToken].type == -1 || file_tokens[currentToken].type == -2){
            if(file_tokens[currentToken].type == -2){
                total *= numGet(&file_tokens[currentToken]);
            }else if(file_tokens[currentToken].type == -1){
                // variable stuff
                total *= 0;
            }else{
                char *buffer = malloc(107 + MAX_INPUT_SIZE);
                sprintf(buffer, "ArithmeticError: Unexpected token in function \"*\", expected number or variable of type number, found:  %s",
                file_tokens[currentToken].keyword);
                raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
            }
            currentToken++;

            Variable *var = malloc(sizeof(Variable));
            var -> value.num = total;
            var -> type = 2;
            eol(1);

            return var;
        }else{
            char *buffer = malloc(69 + MAX_INPUT_SIZE);
            sprintf(buffer, "ArithmeticError: Expected two arguments in function \"*\", found:  %s",
            file_tokens[currentToken].keyword);
            raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }
    }else{
        char *buffer = malloc(52 + MAX_INPUT_SIZE);
        sprintf(buffer, "ArithmeticError: Expected function \"*\", found:  %s",
        file_tokens[currentToken].keyword);
        raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
    }
    return NULL;
}

Variable *mod(){
    if(file_tokens[currentToken].type == 6){
        currentToken++;
        return NULL;
    }
    return 0;
}

Variable *eql(){
    if(file_tokens[currentToken].type == 7){
        currentToken++;
        printf("Equals function\n");
        return NULL;
    }
    return 0;
}

Variable *noteql(){
    if(file_tokens[currentToken].type == 8){
        currentToken++;
        printf("NotEquals Function\n");
        return NULL;
    }
    return 0;
}

Variable *callBuiltin(){
    if(strcmp(file_tokens[currentToken].keyword, "define") == 0){
        return define();
    }else if(strcmp(file_tokens[currentToken].keyword, "lambda") == 0){
        return lambda();
    }else if(strcmp(file_tokens[currentToken].keyword, "print") == 0){
        return prints();
    }else if(strcmp(file_tokens[currentToken].keyword, "run") == 0){
        return runs();
    }else if(strcmp(file_tokens[currentToken].keyword, "exit") == 0){
        exits();
    }
    return 0;
}

Variable *functioncall(){
    if(file_tokens[currentToken].type == -1){
        return callBuiltin();
    }
    return 0;
}

Variable *sol(){
    if(file_tokens[currentToken].type == 1){
        currentToken++;
        if(file_tokens[currentToken].type == -1){
            return functioncall();
        }else if(file_tokens[currentToken].type == 1){
            return sol();
        }else if(file_tokens[currentToken].type == 2){
            return plus();
        }else if(file_tokens[currentToken].type == 3){
            return min();
        }else if(file_tokens[currentToken].type == 4){
            return mult();
        }else if(file_tokens[currentToken].type == 5){
            return divs();
        }else if(file_tokens[currentToken].type == 6){
            return mod();
        }else if(file_tokens[currentToken].type == 7){
            return eql();
        }else if(file_tokens[currentToken].type == 8){
            return noteql();
        }else if(file_tokens[currentToken].type == 12){
            eol(1);
            return &none;
        }else{
            char *buffer = malloc(40 + MAX_INPUT_SIZE);
            sprintf(buffer, "SyntaxError: Invalid statement after start of line: %s", file_tokens[currentToken].keyword);
            raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }
    }else{
        char *buffer = malloc(40 + MAX_INPUT_SIZE);
        sprintf(buffer, "SyntaxError: Expected start of line token: \"%s\", found: \"%s\"",
                    SOL.keyword, file_tokens[currentToken].keyword);
        raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
    }
    char *buffer = malloc(40 + MAX_INPUT_SIZE);
    sprintf(buffer, "SyntaxError: Expected start of line token: \"%s\", found: \"%s\"",
                SOL.keyword, file_tokens[currentToken].keyword);
    raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
}

int parseFile(){
    currentToken++;
    while(true){
        if(eof()){
            return EXIT_SUCCESS;
        }
        sol();
    };
    return EXIT_SUCCESS;
}