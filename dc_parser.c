#include "dc_main.h"


unsigned int current = 0;
unsigned int temp_current = 0;

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

int eol(short raiseEx){
    if(file_tokens[current].type == 12){
        current++;
        printf("End of line\n");
        return 1;
    }else{
        if(raiseEx){
            char *buffer = malloc(44 + MAX_INPUT_SIZE);
            sprintf(buffer, "Unclosed statement, received \"%s\" instead.",
            file_tokens[current].keyword);
            raise(buffer, filename, file_tokens[current].line, file_tokens[current].column);
        }else{
            return 0;
        }
    }
    return 0;
}

int eof(){
    if(file_tokens[current].type == 13){
        current++;
        printf("End of file\n");
        return 1;
    }
    return 0;
}

Variable *plus(){
    if(file_tokens[current].type == 2){
        current++;
        num_t total;
        printf("Plus Function\n");
        if(file_tokens[current].type == -2){
            total = numGet(&file_tokens[current]);
        }else if(file_tokens[current].type == -1){
            // variable stuff
            total = 0;
        }else{
            char *buffer = malloc(90 + MAX_INPUT_SIZE);
            sprintf(buffer, "Unexpected token in function \"+\", expected number or variable of type number, found:  %s",
            file_tokens[current].keyword);
            raise(buffer, filename, file_tokens[current].line, file_tokens[current].column);
        }

        current++;
        if(file_tokens[current].type == -1 || file_tokens[current].type == -2){
            if(file_tokens[current].type == -2){
                total += numGet(&file_tokens[current]);
            }else if(file_tokens[current].type == -1){
                // variable stuff
                total += 0;
            }else{
                char *buffer = malloc(90 + MAX_INPUT_SIZE);
                sprintf(buffer, "Unexpected token in function \"+\", expected number or variable of type number, found:  %s",
                file_tokens[current].keyword);
                raise(buffer, filename, file_tokens[current].line, file_tokens[current].column);
            }
            current++;

            Variable *var = malloc(sizeof(Variable));
            var -> value.num = total;
            var -> type = 2;
            eol(1);

            return var;
        }else{
            char *buffer = malloc(52 + MAX_INPUT_SIZE);
            sprintf(buffer, "Expected two arguments in function \"+\", found:  %s",
            file_tokens[current].keyword);
            raise(buffer, filename, file_tokens[current].line, file_tokens[current].column);
        }
    }else{
        char *buffer = malloc(52 + MAX_INPUT_SIZE);
        sprintf(buffer, "Expected function \"+\", found:  %s",
        file_tokens[current].keyword);
        raise(buffer, filename, file_tokens[current].line, file_tokens[current].column);
    }
    return NULL;
}

Variable *min(){
    if(file_tokens[current].type == 3){
        current++;
        num_t total;
        printf("Minus Function\n");
        if(file_tokens[current].type == -2){
            total = numGet(&file_tokens[current]);
        }else if(file_tokens[current].type == -1){
            // variable stuff
            total = 0;
        }else{
            char *buffer = malloc(90 + MAX_INPUT_SIZE);
            sprintf(buffer, "Unexpected token in function \"-\", expected number or variable of type number, found:  %s",
            file_tokens[current].keyword);
            raise(buffer, filename, file_tokens[current].line, file_tokens[current].column);
        }

        current++;
        if(file_tokens[current].type == -1 || file_tokens[current].type == -2){
            if(file_tokens[current].type == -2){
                total -= numGet(&file_tokens[current]);
            }else if(file_tokens[current].type == -1){
                // variable stuff
                total -= 0;
            }else{
                char *buffer = malloc(90 + MAX_INPUT_SIZE);
                sprintf(buffer, "Unexpected token in function \"-\", expected number or variable of type number, found:  %s",
                file_tokens[current].keyword);
                raise(buffer, filename, file_tokens[current].line, file_tokens[current].column);
            }
            current++;

            Variable *var = malloc(sizeof(Variable));
            var -> value.num = total;
            var -> type = 2;
            eol(1);

            return var;
        }else{
            char *buffer = malloc(61 + MAX_INPUT_SIZE);
            sprintf(buffer, "Expected two arguments in function \"-\", found:  %s",
            file_tokens[current].keyword);
            raise(buffer, filename, file_tokens[current].line, file_tokens[current].column);
        }
    }else{
        char *buffer = malloc(52 + MAX_INPUT_SIZE);
        sprintf(buffer, "Expected function \"-\", found:  %s",
        file_tokens[current].keyword);
        raise(buffer, filename, file_tokens[current].line, file_tokens[current].column);
    }
    return NULL;
}

Variable *divs(){
    if(file_tokens[current].type == 5){
        current++;
        num_t total;
        printf("Divide Function\n");
        if(file_tokens[current].type == -2){
            total = numGet(&file_tokens[current]);
        }else if(file_tokens[current].type == -1){
            // variable stuff
            total = 0;
        }else{
            char *buffer = malloc(90 + MAX_INPUT_SIZE);
            sprintf(buffer, "Unexpected token in function \"/\", expected number or variable of type number, found:  %s",
            file_tokens[current].keyword);
            raise(buffer, filename, file_tokens[current].line, file_tokens[current].column);
        }

        current++;
        if(file_tokens[current].type == -1 || file_tokens[current].type == -2){
            if(file_tokens[current].type == -2){
                total /= numGet(&file_tokens[current]);
            }else if(file_tokens[current].type == -1){
                // variable stuff
                total /= 1;
            }else{
                char *buffer = malloc(90 + MAX_INPUT_SIZE);
                sprintf(buffer, "Unexpected token in function \"/\", expected number or variable of type number, found:  %s",
                file_tokens[current].keyword);
                raise(buffer, filename, file_tokens[current].line, file_tokens[current].column);
            }
            current++;

            Variable *var = malloc(sizeof(Variable));
            var -> value.num = total;
            var -> type = 2;
            eol(1);

            return var;
        }else{
            char *buffer = malloc(52 + MAX_INPUT_SIZE);
            sprintf(buffer, "Expected two arguments in function \"/\", found:  %s",
            file_tokens[current].keyword);
            raise(buffer, filename, file_tokens[current].line, file_tokens[current].column);
        }
    }else{
        char *buffer = malloc(52 + MAX_INPUT_SIZE);
        sprintf(buffer, "Expected function \"/\", found:  %s",
        file_tokens[current].keyword);
        raise(buffer, filename, file_tokens[current].line, file_tokens[current].column);
    }
    return NULL;
}

Variable *mult(){
    if(file_tokens[current].type == 4){
        current++;
        num_t total;
        printf("Multiply Function\n");
        if(file_tokens[current].type == -2){
            total = numGet(&file_tokens[current]);
        }else if(file_tokens[current].type == -1){
            // variable stuff
            total = 0;
        }else{
            char *buffer = malloc(90 + MAX_INPUT_SIZE);
            sprintf(buffer, "Unexpected token in function \"*\", expected number or variable of type number, found:  %s",
            file_tokens[current].keyword);
            raise(buffer, filename, file_tokens[current].line, file_tokens[current].column);
        }

        current++;
        if(file_tokens[current].type == -1 || file_tokens[current].type == -2){
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

            Variable *var = malloc(sizeof(Variable));
            var -> value.num = total;
            var -> type = 2;
            eol(1);

            return var;
        }else{
            char *buffer = malloc(61 + MAX_INPUT_SIZE);
            sprintf(buffer, "Expected at least two arguments in function \"*\", found:  %s",
            file_tokens[current].keyword);
            raise(buffer, filename, file_tokens[current].line, file_tokens[current].column);
        }
    }else{
        char *buffer = malloc(52 + MAX_INPUT_SIZE);
        sprintf(buffer, "Expected function \"*\", found:  %s",
        file_tokens[current].keyword);
        raise(buffer, filename, file_tokens[current].line, file_tokens[current].column);
    }
    return NULL;
}

Variable *mod(){
    if(file_tokens[current].type == 6){
        current++;
        printf("Modulus Function\n");
        return NULL;
    }
    return 0;
}

Variable *eql(){
    if(file_tokens[current].type == 7){
        current++;
        printf("Equals function\n");
        return NULL;
    }
    return 0;
}

Variable *noteql(){
    if(file_tokens[current].type == 8){
        current++;
        printf("NotEquals Function\n");
        return NULL;
    }
    return 0;
}

Variable *callBuiltin(){
    if(strcmp(file_tokens[current].keyword, "define")){
        current = define(current);
    }else if(strcmp(file_tokens[current].keyword, "lambda")){
        current = lambda(current);
    }else if(strcmp(file_tokens[current].keyword, "print")){
        current = prints(current);
    }else if(strcmp(file_tokens[current].keyword, "run")){
        current = runs(current);
    }else if(strcmp(file_tokens[current].keyword, "exit")){
        exits(current);
    }
    return NULL;
}

Variable *functioncall(){
    if(file_tokens[current].type == -1){
        printf("Function call\n");
        Variable *var = malloc(sizeof(Variable));
        if((var = callBuiltin()) != NULL){

        }else{

        }
    }
    return 0;
}

Variable *sol(){
    if(file_tokens[current].type == 1){
        current++;
        printf("Start of line\n");
        printf("%s\n", file_tokens[current].keyword);
        if(file_tokens[current].type == -1){
            return functioncall();
        }else if(file_tokens[current].type == 1){
            return sol();
        }else if(file_tokens[current].type == 2){
            return plus();
        }else if(file_tokens[current].type == 3){
            return min();
        }else if(file_tokens[current].type == 4){
            return mult();
        }else if(file_tokens[current].type == 5){
            return divs();
        }else if(file_tokens[current].type == 6){
            return mod();
        }else if(file_tokens[current].type == 7){
            return eql();
        }else if(file_tokens[current].type == 8){
            return noteql();
        }else{
            char *buffer = malloc(40 + MAX_INPUT_SIZE);
            sprintf(buffer, "Invalid statement after start of line: %s", file_tokens[current].keyword);
            raise(buffer, filename, file_tokens[current].line, file_tokens[current].column);
        }
    }else{
        char *buffer = malloc(40 + MAX_INPUT_SIZE);
        sprintf(buffer, "Expected start of line token: \"%s\", found: \"%s\"",
                    SOL.keyword, file_tokens[current].keyword);
        raise(buffer, filename, file_tokens[current].line, file_tokens[current].column);
    }
    return NULL;
}

int parseFile(){
    current++;
    while(true){
        if(eof()){
            return EXIT_SUCCESS;
        }
        printf("%Lg\n", (sol())->value.num);
    };
    return EXIT_SUCCESS;
}