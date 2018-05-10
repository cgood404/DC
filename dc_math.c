#include "dc_main.h"


Variable *plus(){
    if(file_tokens[currentToken].type == _Plus){
        currentToken++;
        Variable total;

        if(file_tokens[currentToken].type == _StringToken){
            strcpy(total.value.string, strGet(&file_tokens[currentToken]));
            total.type = _String;
            currentToken++;
        }else if(file_tokens[currentToken].type == _NumberToken){
            total.value.num = numGet(&file_tokens[currentToken]);
            total.type = _Number;
            currentToken++;
        }else if(file_tokens[currentToken].type == _VarToken){
            Variable *var = getVarByName(keywordGet(&file_tokens[currentToken]));
            total.type = var -> type;
            total.value = var -> value;
            currentToken++;
        }else if(file_tokens[currentToken].type == _SOL){
            Variable *t_var = sol();
            total.type = t_var -> type;
            total.value = t_var -> value;
        }else{
            char *buffer = malloc(107 + MAX_INPUT_SIZE);
            sprintf(buffer, "ArithmeticError: Unexpected token in function \"+\", expected Number or variable of type Number, found:  %s",
                file_tokens[currentToken].keyword);
            raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }

        if(file_tokens[currentToken].type == _StringToken){
            if(total.type == _String){
                strcat(total.value.string, strGet(&file_tokens[currentToken]));
                currentToken++;
            }else{
                char *buffer = malloc(107 + MAX_INPUT_SIZE);
                sprintf(buffer, "TypeError: Conflicting types for function: \"+\", expected type \"%s\" found:  %s",
                    varTypeGet(&total), file_tokens[currentToken].keyword);
                raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
            }
        }else if(file_tokens[currentToken].type == _NumberToken){
            if(total.type == _Number){
                total.value.num += numGet(&file_tokens[currentToken]);
                currentToken++;
            }else {
                char *buffer = malloc(107 + MAX_INPUT_SIZE);
                sprintf(buffer, "TypeError: Conflicting types for function: \"+\", expected type \"%s\" found:  %s",
                     varTypeGet(&total), file_tokens[currentToken].keyword);
                raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
            }
        }else if(file_tokens[currentToken].type == _VarToken){
            Variable *var = getVarByName(keywordGet(&file_tokens[currentToken]));
            if(var -> type == _Number && total.type == _Number){
                total.value.num += var -> value.num;
                free(var);
                currentToken++;
            }else if(var -> type == _String && total.type == _String){
                strcat(total.value.string, var -> value.string);
                currentToken++;
            }else{
                char *buffer = malloc(107 + MAX_INPUT_SIZE);
                sprintf(buffer, "TypeError: Conflicting types for function: \"+\", expected type \"%s\" found:  %s",
                     varTypeGet(&total), varTypeGet(var));
                raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
            }
        }else if(file_tokens[currentToken].type == _SOL){
            Variable *t_var = sol();
             
            if(t_var -> type == _Number && total.type == _Number){
                total.value.num += t_var -> value.num;
                free(t_var);
            }else if(t_var -> type == _String && total.type == _String){
                strcat(total.value.string, t_var -> value.string);
            }else{
                char *buffer = malloc(107 + MAX_INPUT_SIZE);
                sprintf(buffer, "TypeError: Conflicting types for function: \"+\", expected type \"%s\" found:  %s",
                     varTypeGet(&total), varTypeGet(t_var));
                raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
            }
        }else{
            char *buffer = malloc(107 + MAX_INPUT_SIZE);
            sprintf(buffer, "ArithmeticError: Unexpected token in function \"+\", expected Number or variable of type Number, found:  %s",
            file_tokens[currentToken].keyword);
            raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }

        Variable *var = malloc(sizeof(Variable));
        var -> value = total.value;
        var -> type = total.type;

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
    if(file_tokens[currentToken].type == _Min){
        currentToken++;
        num_t total;
        if(file_tokens[currentToken].type == _NumberToken){
            total = numGet(&file_tokens[currentToken]);
            currentToken++;
        }else if(file_tokens[currentToken].type == _VarToken){
            Variable *var = getVarByName(keywordGet(&file_tokens[currentToken]));
            if(var -> type == _Number){
                total = var -> value.num;
                free(var);
                currentToken++;
            }else{
                char *buffer = malloc(65 + MAX_INPUT_SIZE);
                sprintf(buffer, "ArithmeticError: Variable \"%s\" is of type: %s, expected: Number",
                    var -> name, varTypeGet(var));
                raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
            }
        }else if(file_tokens[currentToken].type == _SOL){
            Variable *t_var = sol();
             
            if(t_var -> type == _Number){
                total = t_var -> value.num;
                free(t_var);
            }else{
                char *buffer = malloc(107 + MAX_INPUT_SIZE);
                sprintf(buffer, "ArithmeticError: Unexpected token in function \"-\", expected Number or variable of type Number, found:  %s",
                    file_tokens[currentToken].keyword);
                raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
            }
        }else{
            char *buffer = malloc(107 + MAX_INPUT_SIZE);
            sprintf(buffer, "ArithmeticError: Unexpected token in function \"-\", expected Number or variable of type Number, found:  %s",
                file_tokens[currentToken].keyword);
            raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }

        if(file_tokens[currentToken].type == _NumberToken){
            total -= numGet(&file_tokens[currentToken]);
            currentToken++;
        }else if(file_tokens[currentToken].type == _VarToken){
            Variable *var = getVarByName(keywordGet(&file_tokens[currentToken]));
            if(var -> type == _Number){
                total -= var -> value.num;
                free(var);
                currentToken++;
            }else{
                char *buffer = malloc(65 + MAX_INPUT_SIZE);
                sprintf(buffer, "ArithmeticError: Variable \"%s\" is of type: %s, expected: Number",
                    var -> name, varTypeGet(var));
                raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
            }
        }else if(file_tokens[currentToken].type == _SOL){
            Variable *t_var = sol();
             
            if(t_var -> type == _Number){
                total -= t_var -> value.num;
                free(t_var);
            }else{
                char *buffer = malloc(107 + MAX_INPUT_SIZE);
                sprintf(buffer, "ArithmeticError: Unexpected token in function \"-\", expected Number or variable of type Number, found:  %s",
                    file_tokens[currentToken].keyword);
                raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
            }
        }else{
            char *buffer = malloc(107 + MAX_INPUT_SIZE);
            sprintf(buffer, "ArithmeticError: Unexpected token in function \"-\", expected Number or variable of type Number, found:  %s",
            file_tokens[currentToken].keyword);
            raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }

        Variable *var = malloc(sizeof(Variable));
        var -> value.num = total;
        var -> type = _Number;
         

        return var;
    
    }else{
        char *buffer = malloc(52 + MAX_INPUT_SIZE);
        sprintf(buffer, "ArithmeticError: Expected function \"-\", found:  %s",
        file_tokens[currentToken].keyword);
        raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
    }
    return NULL;
}

Variable *mult(){
    if(file_tokens[currentToken].type == _Mult){
        currentToken++;
        num_t total;
        if(file_tokens[currentToken].type == _NumberToken){
            total = numGet(&file_tokens[currentToken]);
            currentToken++;
        }else if(file_tokens[currentToken].type == _VarToken){
            Variable *var = getVarByName(keywordGet(&file_tokens[currentToken]));
            if(var -> type == _Number){
                total = var -> value.num;
                free(var);
                currentToken++;
            }else{
                char *buffer = malloc(65 + MAX_INPUT_SIZE);
                sprintf(buffer, "ArithmeticError: Variable \"%s\" is of type: %s, expected: Number",
                    var -> name, varTypeGet(var));
                raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
            }
        }else if(file_tokens[currentToken].type == _SOL){
            Variable *t_var = sol();
             
            if(t_var -> type == _Number){
                total = t_var -> value.num;
                free(t_var);
            }else{
                char *buffer = malloc(107 + MAX_INPUT_SIZE);
                sprintf(buffer, "ArithmeticError: Unexpected token in function \"*\", expected Number or variable of type Number, found:  %s",
                    file_tokens[currentToken].keyword);
                raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
            }
        }else{
            char *buffer = malloc(107 + MAX_INPUT_SIZE);
            sprintf(buffer, "ArithmeticError: Unexpected token in function \"*\", expected Number or variable of type Number, found:  %s",
            file_tokens[currentToken].keyword);
            raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }

        if(file_tokens[currentToken].type == _NumberToken){
            total *= numGet(&file_tokens[currentToken]);
            currentToken++;
        }else if(file_tokens[currentToken].type == _VarToken){
            Variable *var = getVarByName(keywordGet(&file_tokens[currentToken]));
            if(var -> type == _Number){
                total *= var -> value.num;
                free(var);
                currentToken++;
            }else{
                char *buffer = malloc(65 + MAX_INPUT_SIZE);
                sprintf(buffer, "ArithmeticError: Variable \"%s\" is of type: %s, expected: Number",
                    var -> name, varTypeGet(var));
                raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
            }
        }else if(file_tokens[currentToken].type == _SOL){
            Variable *t_var = sol();
             
            if(t_var -> type == _Number){
                total *= t_var -> value.num;
                free(t_var);
            }else{
                char *buffer = malloc(107 + MAX_INPUT_SIZE);
                sprintf(buffer, "ArithmeticError: Unexpected token in function \"*\", expected Number or variable of type Number, found:  %s",
                    file_tokens[currentToken].keyword);
                raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
            }
        }else{
            char *buffer = malloc(107 + MAX_INPUT_SIZE);
            sprintf(buffer, "ArithmeticError: Unexpected token in function \"*\", expected Number or variable of type Number, found:  %s",
            file_tokens[currentToken].keyword);
            raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }

        Variable *var = malloc(sizeof(Variable));
        var -> value.num = total;
        var -> type = _Number;
         

        return var;

    }else{
        char *buffer = malloc(52 + MAX_INPUT_SIZE);
        sprintf(buffer, "ArithmeticError: Expected function \"*\", found:  %s",
        file_tokens[currentToken].keyword);
        raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
    }
    return NULL;
}

Variable *divs(){
    if(file_tokens[currentToken].type == _Div){
        currentToken++;
        num_t total;
        if(file_tokens[currentToken].type == _NumberToken){
            total = numGet(&file_tokens[currentToken]);
            currentToken++;
        }else if(file_tokens[currentToken].type == _VarToken){
            Variable *var = getVarByName(keywordGet(&file_tokens[currentToken]));
            if(var -> type == _Number){
                total = var -> value.num;
                free(var);
                currentToken++;
            }else{
                char *buffer = malloc(65 + MAX_INPUT_SIZE);
                sprintf(buffer, "ArithmeticError: Variable \"%s\" is of type: %s, expected: Number",
                    var -> name, varTypeGet(var));
                raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
            }
        }else if(file_tokens[currentToken].type == _SOL){
            Variable *t_var = sol();
            if(t_var -> type == _Number){
                total = t_var -> value.num;
                free(t_var);
            }else{
                char *buffer = malloc(107 + MAX_INPUT_SIZE);
                sprintf(buffer, "ArithmeticError: Unexpected token in function \"/\", expected Number or variable of type Number, found:  %s",
                    file_tokens[currentToken].keyword);
                raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
            }
        }else{
            char *buffer = malloc(107 + MAX_INPUT_SIZE);
            sprintf(buffer, "ArithmeticError: Unexpected token in function \"/\", expected Number or variable of type Number, found:  %s",
            file_tokens[currentToken].keyword);
            raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }

        if(file_tokens[currentToken].type == _NumberToken){
            if(numGet(&file_tokens[currentToken]) != 0){
                total /= numGet(&file_tokens[currentToken]);
                currentToken++;
            }else{
                char *buffer = malloc(55 + MAX_INPUT_SIZE);
                sprintf(buffer, "ArithmeticError: Division by zero");
                raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
            }
        }else if(file_tokens[currentToken].type == _VarToken){
            Variable *var = getVarByName(keywordGet(&file_tokens[currentToken]));
            if(var -> type == _Number){
                if(var -> value.num != 0){
                    total /= var -> value.num;
                    free(var);
                    currentToken++;
                }else{
                    char *buffer = malloc(55 + MAX_INPUT_SIZE);
                    sprintf(buffer, "ArithmeticError: Division by zero with variable \"%s\"", var -> name);
                    raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
                }
            }else{
                char *buffer = malloc(65 + MAX_INPUT_SIZE);
                sprintf(buffer, "ArithmeticError: Variable \"%s\" is of type: %s, expected: Number",
                    var -> name, varTypeGet(var));
                raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
            }
        }else if(file_tokens[currentToken].type == _SOL){
            Variable *t_var = sol();
             
            if(t_var -> type == _Number){
                if(t_var -> value.num != 0){
                    total /= t_var -> value.num;
                    free(t_var);
                }else{
                    char *buffer = malloc(55 + MAX_INPUT_SIZE);
                    sprintf(buffer, "ArithmeticError: Division by zero with variable \"%s\"", t_var -> name);
                    raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
                }
            }else{
                char *buffer = malloc(107 + MAX_INPUT_SIZE);
                sprintf(buffer, "ArithmeticError: Unexpected token in function \"/\", expected Number or variable of type Number, found:  %s",
                    file_tokens[currentToken].keyword);
                raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
            }
        }else{
            char *buffer = malloc(107 + MAX_INPUT_SIZE);
            sprintf(buffer, "ArithmeticError: Unexpected token in function \"/\", expected Number or variable of type Number, found:  %s",
            file_tokens[currentToken].keyword);
            raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }

        Variable *var = malloc(sizeof(Variable));
        var -> value.num = total;
        var -> type = _Number;
         

        return var;
        
    }else{
        char *buffer = malloc(52 + MAX_INPUT_SIZE);
        sprintf(buffer, "ArithmeticError: Expected function \"/\", found:  %s",
        file_tokens[currentToken].keyword);
        raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
    }
    return NULL;
}

Variable *mod(){
    if(file_tokens[currentToken].type == _Mod){
        currentToken++;
        num_t total;
        if(file_tokens[currentToken].type == _NumberToken){
            total = numGet(&file_tokens[currentToken]);
            currentToken++;
        }else if(file_tokens[currentToken].type == _VarToken){
            Variable *var = getVarByName(keywordGet(&file_tokens[currentToken]));
            if(var -> type == _Number){
                total = var -> value.num;
                free(var);
                currentToken++;
            }else{
                char *buffer = malloc(65 + MAX_INPUT_SIZE);
                sprintf(buffer, "ArithmeticError: Variable \"%s\" is of type: %s, expected: Number",
                    var -> name, varTypeGet(var));
                raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
            }
        }else if(file_tokens[currentToken].type == _SOL){
            Variable *t_var = sol();
            if(t_var -> type == _Number){
                total = t_var -> value.num;
                free(t_var);
            }else{
                char *buffer = malloc(107 + MAX_INPUT_SIZE);
                sprintf(buffer, "ArithmeticError: Unexpected token in function \"%%\", expected Number or variable of type Number, found:  %s",
                    file_tokens[currentToken].keyword);
                raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
            }
        }else{
            char *buffer = malloc(107 + MAX_INPUT_SIZE);
            sprintf(buffer, "ArithmeticError: Unexpected token in function \"%%\", expected Number or variable of type Number, found:  %s",
            file_tokens[currentToken].keyword);
            raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }

        if(file_tokens[currentToken].type == _NumberToken){
            if(numGet(&file_tokens[currentToken]) != 0){
                total = fmodl(total, numGet(&file_tokens[currentToken]));
                currentToken++;
            }else{
                char *buffer = malloc(55 + MAX_INPUT_SIZE);
                sprintf(buffer, "ArithmeticError: Division by zero");
                raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
            }
        }else if(file_tokens[currentToken].type == _VarToken){
            Variable *var = getVarByName(keywordGet(&file_tokens[currentToken]));
            if(var -> type == _Number){
                if(var -> value.num != 0){
                    total = fmodl(total, var -> value.num);
                    free(var);
                    currentToken++;
                }else{
                    char *buffer = malloc(55 + MAX_INPUT_SIZE);
                    sprintf(buffer, "ArithmeticError: Division by zero with variable \"%s\"", var -> name);
                    raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
                }
            }else{
                char *buffer = malloc(65 + MAX_INPUT_SIZE);
                sprintf(buffer, "ArithmeticError: Variable \"%s\" is of type: %s, expected: Number",
                    var -> name, varTypeGet(var));
                raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
            }
        }else if(file_tokens[currentToken].type == _SOL){
            Variable *t_var = sol();
             
            if(t_var -> type == _Number){
                if(t_var -> value.num != 0){
                    total = fmodl(total, t_var -> value.num);
                    free(t_var);
                }else{
                    char *buffer = malloc(55 + MAX_INPUT_SIZE);
                    sprintf(buffer, "ArithmeticError: Division by zero with variable \"%s\"", t_var -> name);
                    raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
                }
            }else{
                char *buffer = malloc(107 + MAX_INPUT_SIZE);
                sprintf(buffer, "ArithmeticError: Unexpected token in function \"%%\", expected Number or variable of type Number, found:  %s",
                    file_tokens[currentToken].keyword);
                raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
            }
        }else{
            char *buffer = malloc(107 + MAX_INPUT_SIZE);
            sprintf(buffer, "ArithmeticError: Unexpected token in function \"%%\", expected Number or variable of type Number, found:  %s",
            file_tokens[currentToken].keyword);
            raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }

        Variable *var = malloc(sizeof(Variable));
        var -> value.num = total;
        var -> type = _Number;
         

        return var;
        
    }else{
        char *buffer = malloc(52 + MAX_INPUT_SIZE);
        sprintf(buffer, "ArithmeticError: Expected function \"%%\", found:  %s",
        file_tokens[currentToken].keyword);
        raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
    }
    return NULL;
}