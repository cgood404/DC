#include "dc_main.h"


unsigned int currentToken = 0;
unsigned int temp_current = 0;

void parserError(char *statement, int line, int column){
    raise(statement, filename, line, column);
}

// returns string (type -3), can be formatted in the future with escape characters
char *strGet(Token *token){
    if(token -> type == _StringToken){
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
    if(token -> type == _NumberToken){
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
    if(token -> type == _VarToken){
        return token -> keyword;
    }else{
        char *buffer = malloc(63 + MAX_INPUT_SIZE);
        sprintf(buffer, "SyntaxError: Expected variable or function name, received %s",
        file_tokens[currentToken].keyword);
        raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
    }

    return NULL;
}

char *varTypeGet(Variable *var){
    if(var -> type == _none){
        return "none";
    }else if(var -> type == _Boolean){
        return "Boolean";
    }else if(var -> type == _Number){
        return "Number";
    }else if(var -> type == _String){
        return "String";
    }

    char *buffer = malloc(54 + MAX_INPUT_SIZE);
    sprintf(buffer, "TypeError: No variable of type %d exists",
        var -> type);
    raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);

    return NULL;
}


int eol(short raiseEx){
    if(file_tokens[currentToken].type == _EOL){
        if(raiseEx){
            currentToken++;
            return 1;
        }else{
            return 1;
        }
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
    if(file_tokens[currentToken].type == _EOF){
        currentToken++;
        return 1;
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
    return NULL;
}

Variable *functioncall(){
    if(file_tokens[currentToken].type == _VarToken){
        return callBuiltin();
    }
    return 0;
}

Variable *sol(){
    if(file_tokens[currentToken].type == _SOL){
        currentToken++;
        if(file_tokens[currentToken].type == _VarToken){
            Variable *var = functioncall();
            eol(1);
            return var;
        }else if(file_tokens[currentToken].type == _SOL){
            Variable *var = sol();
            eol(1);
            return var;
        }else if(file_tokens[currentToken].type == _Plus){
            Variable *var = plus();
            eol(1);
            return var;
        }else if(file_tokens[currentToken].type == _Min){
            Variable *var = min();
            eol(1);
            return var;
        }else if(file_tokens[currentToken].type == _Mult){
            Variable *var = mult();
            eol(1);
            return var;
        }else if(file_tokens[currentToken].type == _Div){
            Variable *var = divs();
            eol(1);
            return var;
        }else if(file_tokens[currentToken].type == _Mod){
            Variable *var = mod();
            eol(1);
            return var;
        }else if(file_tokens[currentToken].type == _If){
            Variable *var = ifs();
            eol(1);
            return var;
        }else if(file_tokens[currentToken].type == _Eql){
            Variable *var = eql();
            eol(1);
            return var;
        }else if(file_tokens[currentToken].type == _Not){
            Variable *var = nots();
            eol(1);
            return var;
        }else if(file_tokens[currentToken].type == _LessEql){
            Variable *var = lessEql();
            eol(1);
            return var;
        }else if(file_tokens[currentToken].type == _GrtrEql){
            Variable *var = grtrEql();
            eol(1);
            return var;
        }else if(file_tokens[currentToken].type == _Less){
            Variable *var = less();
            eol(1);
            return var;
        }else if(file_tokens[currentToken].type == _Grtr){
            Variable *var = grtr();
            eol(1);
            return var;
        }else if(file_tokens[currentToken].type == _EOL){
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

    return NULL;
}

int parseFile(){
    if(currentToken == 0){
        currentToken++;
    }
    while(true){
        if(eof() || file_size == currentToken){
            return EXIT_SUCCESS;
        }
        sol();
    };
    return EXIT_SUCCESS;
}