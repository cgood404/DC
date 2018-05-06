#include "dc_main.h"

Variable *plus(){
    if(file_tokens[currentToken].type == 2){
        currentToken++;
        num_t total;
        if(file_tokens[currentToken].type == -2){
            total = numGet(&file_tokens[currentToken]);
        }else if(file_tokens[currentToken].type == -1){
            Variable *var = getVarByName(keywordGet(&file_tokens[currentToken]));
            if(var -> type == 2){
                total = var -> value.num;
            }else{
                char *buffer = malloc(55 + MAX_INPUT_SIZE);
                sprintf(buffer, "ArithmeticError: Variable \"%s\" is not of type: Number", var -> name);
                raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
            }
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
            Variable *var = getVarByName(keywordGet(&file_tokens[currentToken]));
            if(var -> type == 2){
                total += var -> value.num;
            }else{
                char *buffer = malloc(55 + MAX_INPUT_SIZE);
                sprintf(buffer, "ArithmeticError: Variable \"%s\" is not of type: Number", var -> name);
                raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
            }
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
            Variable *var = getVarByName(keywordGet(&file_tokens[currentToken]));
            if(var -> type == 2){
                total = var -> value.num;
            }else{
                char *buffer = malloc(55 + MAX_INPUT_SIZE);
                sprintf(buffer, "ArithmeticError: Variable \"%s\" is not of type: Number", var -> name);
                raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
            }
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
                Variable *var = getVarByName(keywordGet(&file_tokens[currentToken]));
            if(var -> type == 2){
                total -= var -> value.num;
            }else{
                char *buffer = malloc(55 + MAX_INPUT_SIZE);
                sprintf(buffer, "ArithmeticError: Variable \"%s\" is not of type: Number", var -> name);
                raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
            }
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
            Variable *var = getVarByName(keywordGet(&file_tokens[currentToken]));
            if(var -> type == 2){
                total = var -> value.num;
            }else{
                char *buffer = malloc(55 + MAX_INPUT_SIZE);
                sprintf(buffer, "ArithmeticError: Variable \"%s\" is not of type: Number", var -> name);
                raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
            }
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
                Variable *var = getVarByName(keywordGet(&file_tokens[currentToken]));
            if(var -> type == 2){
                if(var -> value.num == 0){
                    char *buffer = malloc(55 + MAX_INPUT_SIZE);
                    sprintf(buffer, "ArithmeticError: Division by zero with variable \"%s\"", var -> name);
                    raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
                }
                total /= var -> value.num;
            }else{
                char *buffer = malloc(55 + MAX_INPUT_SIZE);
                sprintf(buffer, "ArithmeticError: Variable \"%s\" is not of type: Number", var -> name);
                raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
            }
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
            Variable *var = getVarByName(keywordGet(&file_tokens[currentToken]));
            if(var -> type == 2){
                total = var -> value.num;
            }else{
                char *buffer = malloc(55 + MAX_INPUT_SIZE);
                sprintf(buffer, "ArithmeticError: Variable \"%s\" is not of type: Number", var -> name);
                raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
            }
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
                Variable *var = getVarByName(keywordGet(&file_tokens[currentToken]));
            if(var -> type == 2){
                total *= var -> value.num;
            }else{
                char *buffer = malloc(55 + MAX_INPUT_SIZE);
                sprintf(buffer, "ArithmeticError: Variable \"%s\" is not of type: Number", var -> name);
                raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
            }
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
        raise("NotImplementedError", filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
    }
    return &none;
}

Variable *eql(){
    if(file_tokens[currentToken].type == 7){
        currentToken++;
        Variable *var1 = malloc(sizeof(Variable)),
                 *var2 = malloc(sizeof(Variable));
        if(file_tokens[currentToken].type == 1){
            var1 = sol();
        }else if(file_tokens[currentToken].type == -1){
            var1 = getVarByName(keywordGet(&file_tokens[currentToken]));
            currentToken++;
        }else if(file_tokens[currentToken].type == -2){
            var1 -> value.num = numGet(&file_tokens[currentToken]);
            var1 -> type = 2;
            currentToken++;
        }else if(file_tokens[currentToken].type == -3){
            strcpy(var1 -> value.string, strGet(&file_tokens[currentToken]));
            var1 -> type = 3;
            currentToken++;
        }else{
            char *buffer = malloc(72 + MAX_INPUT_SIZE);
            sprintf(buffer, "SyntaxError: Expected expression evaluating to variable, received \"%s\"",
            file_tokens[currentToken].keyword);
            raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }

        if(file_tokens[currentToken].type == 1){
            var2 = sol();
        }else if(file_tokens[currentToken].type == -1){
            var2 = getVarByName(keywordGet(&file_tokens[currentToken]));
            currentToken++;
        }else if(file_tokens[currentToken].type == -2){
            var2 -> value.num = numGet(&file_tokens[currentToken]);
            var2 -> type = 2;
            currentToken++;
        }else if(file_tokens[currentToken].type == -3){
            strcpy(var1 -> value.string, strGet(&file_tokens[currentToken]));
            var2 -> type = 3;
            currentToken++;
        }else{
            char *buffer = malloc(72 + MAX_INPUT_SIZE);
            sprintf(buffer, "SyntaxError: Expected expression evaluating to variable, received \"%s\"",
            file_tokens[currentToken].keyword);
            raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }

        eol(1);
        if(var1 -> type == var2 -> type){
            if(var1 -> type == 0){
                return &True;
            }else if(var1 -> type == 1){
                if(var1 -> value.num == var2 -> value.num){
                    return &True;
                }else{
                    return &False;
                }
            }else if(var1 -> type == 2){
                if(var1 -> value.num == var2 -> value.num){
                    return &True;
                }else{
                    return &False;
                }
            }else if(var1 -> type == 3){
                if(strcmp(var1 -> value.string, var2 -> value.string) == 0){
                    return &True;
                }else{
                    return &False;
                }
            }
        }else{
            return &False;
        }
        
    }
    char *buffer = malloc(54 + MAX_INPUT_SIZE);
    sprintf(buffer, "SyntaxError: Expected Equals Function, received \"%s\"",
    file_tokens[currentToken].keyword);
    raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
}

Variable *nots(){
    if(file_tokens[currentToken].type == 8){
        currentToken++;
        Variable *var;
        if(file_tokens[currentToken].type == -1){
            var = getVarByName(keywordGet(&file_tokens[currentToken]));
            currentToken++;
            eol(1);
        }else if(file_tokens[currentToken].type == 1){
            var = sol();
            eol(1);
        }else if(file_tokens[currentToken].type == 7){
            var = eql();
        }else if(file_tokens[currentToken].type == 8){
            var = nots();
        }else if(file_tokens[currentToken].type == 15){
            var = lessEql();
        }else if(file_tokens[currentToken].type == 16){
            var = grtrEql();
        }else if(file_tokens[currentToken].type == 17){
            var = less();
        }else if(file_tokens[currentToken].type == 18){
            var = grtr();
        }

        if(var -> type == 0){
            return &True;
        }else if(var -> type == 1){
            if(var -> value.num == 1){
                return &False;
            }else if(var -> value.num == 0){
                return &True;
            }
        }else{
            return &False;
        }
    }else{
        char *buffer = malloc(57 + MAX_INPUT_SIZE);
        sprintf(buffer, "SyntaxError: Expected not statement, received token: \"%s\"",
        file_tokens[currentToken].keyword);
        raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
    }
}

Variable *lessEql(){
    return &none;
}

Variable *grtrEql(){
    return &none;
}

Variable *less(){
    return &none;
}

Variable *grtr(){
    return &none;
}

Variable *define(){
    if(file_tokens[currentToken].type == -1){
        currentToken++;
        char *name = keywordGet(&file_tokens[currentToken]);
        if(strcmp(name, "none") == 0){
            raise("OverwriteError: Cannot overwrite none variable", filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }else if(strcmp(name, "True") == 0 || strcmp(name, "False") == 0){
            raise("OverwriteError: Cannot overwrite Boolean variable", filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }
        // if variable is already declared, redefine it
        for(int i = 0; i < variable_table_size; i++){
            if(strcmp(variable_table[i].name, name) == 0){
                Variable *var = malloc(sizeof(Variable));
                strcpy(var -> name, name);
                currentToken++;
                if(file_tokens[currentToken].type == -3){
                    var -> type = 3;
                    strcpy(var -> value.string, strGet(&file_tokens[currentToken]));
                    currentToken++;
                }else if(file_tokens[currentToken].type == -2){
                    var -> type = 2;
                    var -> value.num = numGet(&file_tokens[currentToken]);
                    currentToken++;
                }else if(file_tokens[currentToken].type == -1){
                    Variable *cpyvar = getVarByName(keywordGet(&file_tokens[currentToken]));
                    var -> type = cpyvar -> type;
                    memcpy(&(var -> value), &(cpyvar -> value), sizeof(_VARIABLE));
                    currentToken++;
                }else if(file_tokens[currentToken].type == 1){
                    var = sol();
                }else{
                    char *buffer = malloc(53 + MAX_INPUT_SIZE);
                    sprintf(buffer, "SyntaxError: Expected String or Number, received \"%s\" of type %d",
                    file_tokens[currentToken].keyword, file_tokens[currentToken].type);
                    raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
                }

                variable_table[i] = *var;
                eol(1);
                return var;
            }
        }

        Variable *var = malloc(sizeof(Variable));
        currentToken++;

        if(file_tokens[currentToken].type == -3){
            var -> type = 3;
            strcpy(var -> value.string, strGet(&file_tokens[currentToken]));
            currentToken++;
        }else if(file_tokens[currentToken].type == -2){
            var -> type = 2;
            var -> value.num = numGet(&file_tokens[currentToken]);
            currentToken++;
        }else if(file_tokens[currentToken].type == -1){
            Variable *cpyvar = getVarByName(keywordGet(&file_tokens[currentToken]));
            var -> type = cpyvar -> type;
            memcpy(&(var -> value), &(cpyvar -> value), sizeof(_VARIABLE));
            currentToken++;
        }else if(file_tokens[currentToken].type == 1){
            var = sol();
        }else{
            char *buffer = malloc(53 + MAX_INPUT_SIZE);
            sprintf(buffer, "SyntaxError: Expected String or Number, received \"%s\" of type %d",
            file_tokens[currentToken].keyword, file_tokens[currentToken].type);
            raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }

        strcpy(var -> name, name);
        addVariable(var);
        eol(1);

        return var;
    }else{
        return &none;
    }
}

Variable *lambda(){
    if(file_tokens[currentToken].type == 6){
        raise("NotImplementedError", filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
    }
    return &none;
}

void printsVar(Variable *var){
    if(var -> type == 0){
        printf("none");
    }else if(var -> type == 1){
        if(var -> value.num == 0){
            printf("False");
        }else if(var -> value.num == 1){
            printf("True");
        }
    }else if(var -> type == 2){
        printf("%Lg", var->value.num);
    }else if(var -> type == 3){
        printf("%s", var->value.string);
    }
}

Variable *prints(){
    if(file_tokens[currentToken].type == -1 && strcmp(file_tokens[currentToken].keyword, "print") == 0){
        currentToken++;
        while(!eol(0)){
            if(file_tokens[currentToken].type == 1){
                printsVar(sol());
            }else if(file_tokens[currentToken].type == -1){
                printsVar(getVarByName(keywordGet(&file_tokens[currentToken])));
                currentToken++;
            }else if(file_tokens[currentToken].type == -2){
                printf("%Lg", numGet(&file_tokens[currentToken]));
                currentToken++;
            }else if(file_tokens[currentToken].type == -3){
                printf("%s", strGet(&file_tokens[currentToken]));
                currentToken++;
            }else{
                char *buffer = malloc(57 + MAX_INPUT_SIZE);
                sprintf(buffer, "SyntaxError: Unprintable statement, received token: \"%s\"",
                file_tokens[currentToken].keyword);
                raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
            }
        }
    }else{
        char *buffer = malloc(61 + MAX_INPUT_SIZE);
        sprintf(buffer, "SyntaxError: Expected print statement, received token: \"%s\"",
        file_tokens[currentToken].keyword);
        raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
    }
    printf("\n");
    return &none;
}

Variable *runs(){
    if(file_tokens[currentToken].type == -1){
        
    }
    return &none;
}

void exits(){
    // free all malloc'd memory and exit using given exit status, if any
    if(strcmp(file_tokens[currentToken].keyword, "exit") == 0){
        currentToken++;
        if(file_tokens[currentToken].type == -2){
            int status = (int) numGet(&file_tokens[currentToken]);

            free(file_tokens);
            free(function_table);
            free(variable_table);

            exit(status);
        }else{
            eol(1);

            free(file_tokens);
            free(function_table);
            free(variable_table);

            exit(EXIT_SUCCESS);
        }
    }else{
        char *buffer = malloc(36 + MAX_INPUT_SIZE);
        sprintf(buffer, "Expected exit token, received \"%s\"",
        file_tokens[currentToken].keyword);
        raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
    }
}
