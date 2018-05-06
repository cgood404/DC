#include "dc_main.h"

Variable *plus(){
    if(file_tokens[currentToken].type == _Plus){
        currentToken++;
        num_t total;
        if(file_tokens[currentToken].type == _NumberToken){
            total = numGet(&file_tokens[currentToken]);
        }else if(file_tokens[currentToken].type == _VarToken){
            Variable *var = getVarByName(keywordGet(&file_tokens[currentToken]));
            if(var -> type == _Number){
                total = var -> value.num;
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
            }else{
                char *buffer = malloc(107 + MAX_INPUT_SIZE);
                sprintf(buffer, "ArithmeticError: Unexpected token in function \"+\", expected Number or variable of type Number, found:  %s",
                    file_tokens[currentToken].keyword);
                raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
            }
        }else{
            char *buffer = malloc(107 + MAX_INPUT_SIZE);
            sprintf(buffer, "ArithmeticError: Unexpected token in function \"+\", expected Number or variable of type Number, found:  %s",
                file_tokens[currentToken].keyword);
            raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }

        currentToken++;
        if(file_tokens[currentToken].type == _NumberToken){
            total += numGet(&file_tokens[currentToken]);
        }else if(file_tokens[currentToken].type == _VarToken){
            Variable *var = getVarByName(keywordGet(&file_tokens[currentToken]));
            if(var -> type == _Number){
                total += var -> value.num;
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
            }else{
                char *buffer = malloc(107 + MAX_INPUT_SIZE);
                sprintf(buffer, "ArithmeticError: Unexpected token in function \"+\", expected Number or variable of type Number, found:  %s",
                file_tokens[currentToken].keyword);
                raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
            }
        }else{
            char *buffer = malloc(107 + MAX_INPUT_SIZE);
            sprintf(buffer, "ArithmeticError: Unexpected token in function \"+\", expected Number or variable of type Number, found:  %s",
            file_tokens[currentToken].keyword);
            raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }
        currentToken++;

        Variable *var = malloc(sizeof(Variable));
        var -> value.num = total;
        var -> type = _Number;
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
    if(file_tokens[currentToken].type == _Min){
        currentToken++;
        num_t total;
        if(file_tokens[currentToken].type == _NumberToken){
            total = numGet(&file_tokens[currentToken]);
        }else if(file_tokens[currentToken].type == _VarToken){
            Variable *var = getVarByName(keywordGet(&file_tokens[currentToken]));
            if(var -> type == _Number){
                total = var -> value.num;
            }else{
                char *buffer = malloc(65 + MAX_INPUT_SIZE);
                sprintf(buffer, "ArithmeticError: Variable \"%s\" is of type: %s, expected: Number",
                    var -> name, varTypeGet(var));
                raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
            }
        }else{
            char *buffer = malloc(107 + MAX_INPUT_SIZE);
            sprintf(buffer, "ArithmeticError: Unexpected token in function \"-\", expected Number or variable of type Number, found:  %s",
            file_tokens[currentToken].keyword);
            raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }

        currentToken++;
        if(file_tokens[currentToken].type == _VarToken || file_tokens[currentToken].type == _NumberToken){
            if(file_tokens[currentToken].type == _NumberToken){
                total -= numGet(&file_tokens[currentToken]);
            }else if(file_tokens[currentToken].type == _VarToken){
                Variable *var = getVarByName(keywordGet(&file_tokens[currentToken]));
                if(var -> type == _Number){
                    total -= var -> value.num;
                }else{
                    char *buffer = malloc(65 + MAX_INPUT_SIZE);
                    sprintf(buffer, "ArithmeticError: Variable \"%s\" is of type: %s, expected: Number",
                        var -> name, varTypeGet(var));
                    raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
                }
            }else{
                char *buffer = malloc(107 + MAX_INPUT_SIZE);
                sprintf(buffer, "ArithmeticError: Unexpected token in function \"-\", expected Number or variable of type Number, found:  %s",
                file_tokens[currentToken].keyword);
                raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
            }
            currentToken++;

            Variable *var = malloc(sizeof(Variable));
            var -> value.num = total;
            var -> type = _Number;
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
    if(file_tokens[currentToken].type == _Div){
        currentToken++;
        num_t total;
        if(file_tokens[currentToken].type == _NumberToken){
            total = numGet(&file_tokens[currentToken]);
        }else if(file_tokens[currentToken].type == _VarToken){
            Variable *var = getVarByName(keywordGet(&file_tokens[currentToken]));
            if(var -> type == _Number){
                total = var -> value.num;
            }else{
                char *buffer = malloc(65 + MAX_INPUT_SIZE);
                sprintf(buffer, "ArithmeticError: Variable \"%s\" is of type: %s, expected: Number",
                    var -> name, varTypeGet(var));
                raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
            }
        }else{
            char *buffer = malloc(107 + MAX_INPUT_SIZE);
            sprintf(buffer, "ArithmeticError: Unexpected token in function \"/\", expected Number or variable of type Number, found:  %s",
            file_tokens[currentToken].keyword);
            raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }

        currentToken++;
        if(file_tokens[currentToken].type == _VarToken || file_tokens[currentToken].type == _NumberToken){
            if(file_tokens[currentToken].type == _NumberToken){
                total /= numGet(&file_tokens[currentToken]);
            }else if(file_tokens[currentToken].type == _VarToken){
                Variable *var = getVarByName(keywordGet(&file_tokens[currentToken]));
                if(var -> type == _Number){
                    if(var -> value.num == 0){
                        char *buffer = malloc(55 + MAX_INPUT_SIZE);
                        sprintf(buffer, "ArithmeticError: Division by zero with variable \"%s\"", var -> name);
                        raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
                    }
                    total /= var -> value.num;
                }else{
                    char *buffer = malloc(65 + MAX_INPUT_SIZE);
                    sprintf(buffer, "ArithmeticError: Variable \"%s\" is of type: %s, expected: Number",
                        var -> name, varTypeGet(var));
                    raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
                }
            }else{
                char *buffer = malloc(107 + MAX_INPUT_SIZE);
                sprintf(buffer, "ArithmeticError: Unexpected token in function \"/\", expected Number or variable of type Number, found:  %s",
                file_tokens[currentToken].keyword);
                raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
            }
            currentToken++;

            Variable *var = malloc(sizeof(Variable));
            var -> value.num = total;
            var -> type = _Number;
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
    if(file_tokens[currentToken].type == _Mult){
        currentToken++;
        num_t total;
        if(file_tokens[currentToken].type == _NumberToken){
            total = numGet(&file_tokens[currentToken]);
        }else if(file_tokens[currentToken].type == _VarToken){
            Variable *var = getVarByName(keywordGet(&file_tokens[currentToken]));
            if(var -> type == _Number){
                total = var -> value.num;
            }else{
                char *buffer = malloc(65 + MAX_INPUT_SIZE);
                sprintf(buffer, "ArithmeticError: Variable \"%s\" is of type: %s, expected: Number",
                    var -> name, varTypeGet(var));
                raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
            }
        }else{
            char *buffer = malloc(107 + MAX_INPUT_SIZE);
            sprintf(buffer, "ArithmeticError: Unexpected token in function \"*\", expected Number or variable of type Number, found:  %s",
            file_tokens[currentToken].keyword);
            raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }

        currentToken++;
        if(file_tokens[currentToken].type == _VarToken || file_tokens[currentToken].type == _NumberToken){
            if(file_tokens[currentToken].type == _NumberToken){
                total *= numGet(&file_tokens[currentToken]);
            }else if(file_tokens[currentToken].type == _VarToken){
                Variable *var = getVarByName(keywordGet(&file_tokens[currentToken]));
                if(var -> type == _Number){
                    total *= var -> value.num;
                }else{
                    char *buffer = malloc(65 + MAX_INPUT_SIZE);
                    sprintf(buffer, "ArithmeticError: Variable \"%s\" is of type: %s, expected: Number",
                        var -> name, varTypeGet(var));
                    raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
                }
            }else{
                char *buffer = malloc(107 + MAX_INPUT_SIZE);
                sprintf(buffer, "ArithmeticError: Unexpected token in function \"*\", expected Number or variable of type Number, found:  %s",
                file_tokens[currentToken].keyword);
                raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
            }
            currentToken++;

            Variable *var = malloc(sizeof(Variable));
            var -> value.num = total;
            var -> type = _Number;
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
    if(file_tokens[currentToken].type == _Eql){
        currentToken++;
        Variable *var1 = malloc(sizeof(Variable)),
                 *var2 = malloc(sizeof(Variable));
        if(file_tokens[currentToken].type == _SOL){
            var1 = sol();
        }else if(file_tokens[currentToken].type == _VarToken){
            var1 = getVarByName(keywordGet(&file_tokens[currentToken]));
            currentToken++;
        }else if(file_tokens[currentToken].type == _NumberToken){
            var1 -> value.num = numGet(&file_tokens[currentToken]);
            var1 -> type = _Number;
            currentToken++;
        }else if(file_tokens[currentToken].type == _StringToken){
            strcpy(var1 -> value.string, strGet(&file_tokens[currentToken]));
            var1 -> type = _String;
            currentToken++;
        }else{
            char *buffer = malloc(72 + MAX_INPUT_SIZE);
            sprintf(buffer, "SyntaxError: Expected expression evaluating to variable, received \"%s\"",
            file_tokens[currentToken].keyword);
            raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }

        if(file_tokens[currentToken].type == _SOL){
            var2 = sol();
        }else if(file_tokens[currentToken].type == _VarToken){
            var2 = getVarByName(keywordGet(&file_tokens[currentToken]));
            currentToken++;
        }else if(file_tokens[currentToken].type == _NumberToken){
            var2 -> value.num = numGet(&file_tokens[currentToken]);
            var2 -> type = _Number;
            currentToken++;
        }else if(file_tokens[currentToken].type == _StringToken){
            strcpy(var1 -> value.string, strGet(&file_tokens[currentToken]));
            var2 -> type = _String;
            currentToken++;
        }else{
            char *buffer = malloc(72 + MAX_INPUT_SIZE);
            sprintf(buffer, "SyntaxError: Expected expression evaluating to variable, received \"%s\"",
            file_tokens[currentToken].keyword);
            raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }

        eol(1);
        if(var1 -> type == var2 -> type){
            if(var1 -> type == _none){
                return &True;
            }else if(var1 -> type == _Boolean){
                if(var1 -> value.boolean == var2 -> value.boolean){
                    return &True;
                }else{
                    return &False;
                }
            }else if(var1 -> type == _Number){
                if(var1 -> value.num == var2 -> value.num){
                    return &True;
                }else{
                    return &False;
                }
            }else if(var1 -> type == _String){
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

    return NULL;
}

Variable *nots(){
    if(file_tokens[currentToken].type == _Not){
        currentToken++;
        Variable *var;
        if(file_tokens[currentToken].type == -_SOL){
            var = getVarByName(keywordGet(&file_tokens[currentToken]));
            currentToken++;
            eol(1);
        }else if(file_tokens[currentToken].type == _SOL){
            var = sol();
            eol(1);
        }else if(file_tokens[currentToken].type == _Eql){
            var = eql();
        }else if(file_tokens[currentToken].type == _Not){
            var = nots();
        }else if(file_tokens[currentToken].type == _LessEql){
            var = lessEql();
        }else if(file_tokens[currentToken].type == _GrtrEql){
            var = grtrEql();
        }else if(file_tokens[currentToken].type == _Less){
            var = less();
        }else if(file_tokens[currentToken].type == _Grtr){
            var = grtr();
        }

        if(var -> type == _none){
            return &True;
        }else if(var -> type == _Boolean){
            if(var -> value.boolean == 1){
                return &False;
            }else if(var -> value.boolean == 0){
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

    return NULL;
}

Variable *lessEql(){
    if(file_tokens[currentToken].type == _LessEql){
        currentToken++;
        Variable *var1 = malloc(sizeof(Variable)),
                 *var2 = malloc(sizeof(Variable));
        if(file_tokens[currentToken].type == _SOL){
            var1 = sol();
        }else if(file_tokens[currentToken].type == _VarToken){
            var1 = getVarByName(keywordGet(&file_tokens[currentToken]));
            currentToken++;
        }else if(file_tokens[currentToken].type == _NumberToken){
            var1 -> value.num = numGet(&file_tokens[currentToken]);
            var1 -> type = _Number;
            currentToken++;
        }else if(file_tokens[currentToken].type == _StringToken){
            strcpy(var1 -> value.string, strGet(&file_tokens[currentToken]));
            var1 -> type = _String;
            currentToken++;
        }else{
            char *buffer = malloc(72 + MAX_INPUT_SIZE);
            sprintf(buffer, "SyntaxError: Expected expression evaluating to variable, received \"%s\"",
            file_tokens[currentToken].keyword);
            raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }

        if(file_tokens[currentToken].type == _SOL){
            var2 = sol();
        }else if(file_tokens[currentToken].type == _VarToken){
            var2 = getVarByName(keywordGet(&file_tokens[currentToken]));
            currentToken++;
        }else if(file_tokens[currentToken].type == _NumberToken){
            var2 -> value.num = numGet(&file_tokens[currentToken]);
            var2 -> type = _Number;
            currentToken++;
        }else if(file_tokens[currentToken].type == _StringToken){
            strcpy(var2 -> value.string, strGet(&file_tokens[currentToken]));
            var2 -> type = _String;
            currentToken++;
        }else{
            char *buffer = malloc(72 + MAX_INPUT_SIZE);
            sprintf(buffer, "SyntaxError: Expected expression evaluating to variable, received \"%s\"",
            file_tokens[currentToken].keyword);
            raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }

        eol(1);
        if(var1 -> type == _none && var2 -> type != _none){
            return &True;
        }else if(var1 -> type != _none && var2 -> type == _none){
            return &False;
        }else if(var1 -> type == var2 -> type){
            if(var1 -> type == _none){
                return &True;
            }else if(var1 -> type == _Boolean){
                if(var1 -> value.boolean == var2 -> value.boolean){
                    return &True;
                }else{
                    return &False;
                }
            }else if(var1 -> type == _Number){
                if(var1 -> value.num <= var2 -> value.num){
                    return &True;
                }else{
                    return &False;
                }
            }else if(var1 -> type == _String){
                if(strlen(var1 -> value.string) <= strlen(var2 -> value.string)){
                    return &True;
                }else{
                    return &False;
                }
            }
        }else{
            char *buffer = malloc(54 + MAX_INPUT_SIZE);
            sprintf(buffer, "TypeError: Cannot compare variables of types %s and %s",
                varTypeGet(var1), varTypeGet(var2));
            raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }
        
    }
    char *buffer = malloc(54 + MAX_INPUT_SIZE);
    sprintf(buffer, "SyntaxError: Expected LessEquals Function, received \"%s\"",
    file_tokens[currentToken].keyword);
    raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);

    return NULL;
}

Variable *grtrEql(){
    if(file_tokens[currentToken].type == _GrtrEql){
        currentToken++;
        Variable *var1 = malloc(sizeof(Variable)),
                 *var2 = malloc(sizeof(Variable));
        if(file_tokens[currentToken].type == _SOL){
            var1 = sol();
        }else if(file_tokens[currentToken].type == _VarToken){
            var1 = getVarByName(keywordGet(&file_tokens[currentToken]));
            currentToken++;
        }else if(file_tokens[currentToken].type == _NumberToken){
            var1 -> value.num = numGet(&file_tokens[currentToken]);
            var1 -> type = _Number;
            currentToken++;
        }else if(file_tokens[currentToken].type == _StringToken){
            strcpy(var1 -> value.string, strGet(&file_tokens[currentToken]));
            var1 -> type = _String;
            currentToken++;
        }else{
            char *buffer = malloc(72 + MAX_INPUT_SIZE);
            sprintf(buffer, "SyntaxError: Expected expression evaluating to variable, received \"%s\"",
            file_tokens[currentToken].keyword);
            raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }

        if(file_tokens[currentToken].type == _SOL){
            var2 = sol();
        }else if(file_tokens[currentToken].type == _VarToken){
            var2 = getVarByName(keywordGet(&file_tokens[currentToken]));
            currentToken++;
        }else if(file_tokens[currentToken].type == _NumberToken){
            var2 -> value.num = numGet(&file_tokens[currentToken]);
            var2 -> type = _Number;
            currentToken++;
        }else if(file_tokens[currentToken].type == _StringToken){
            strcpy(var2 -> value.string, strGet(&file_tokens[currentToken]));
            var2 -> type = _String;
            currentToken++;
        }else{
            char *buffer = malloc(72 + MAX_INPUT_SIZE);
            sprintf(buffer, "SyntaxError: Expected expression evaluating to variable, received \"%s\"",
            file_tokens[currentToken].keyword);
            raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }

        eol(1);
        if(var1 -> type != _none && var2 -> type == _none){
            return &True;
        }else if(var1 -> type == _none && var2 -> type != _none){
            return &False;
        }else if(var1 -> type == var2 -> type){
            if(var1 -> type == _none){
                return &True;
            }else if(var1 -> type == _Boolean){
                if(var1 -> value.boolean == var2 -> value.boolean){
                    return &True;
                }else{
                    return &False;
                }
            }else if(var1 -> type == _Number){
                if(var1 -> value.num >= var2 -> value.num){
                    return &True;
                }else{
                    return &False;
                }
            }else if(var1 -> type == _String){
                if(strlen(var1 -> value.string) >= strlen(var2 -> value.string)){
                    return &True;
                }else{
                    return &False;
                }
            }
        }else{
            char *buffer = malloc(54 + MAX_INPUT_SIZE);
            sprintf(buffer, "TypeError: Cannot compare variables of types %s and %s",
                varTypeGet(var1), varTypeGet(var2));
            raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }
        
    }
    char *buffer = malloc(54 + MAX_INPUT_SIZE);
    sprintf(buffer, "SyntaxError: Expected GrtrEquals Function, received \"%s\"",
    file_tokens[currentToken].keyword);
    raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);

    return NULL;
}

Variable *less(){
    if(file_tokens[currentToken].type == _Less){
        currentToken++;
        Variable *var1 = malloc(sizeof(Variable)),
                 *var2 = malloc(sizeof(Variable));
        if(file_tokens[currentToken].type == _SOL){
            var1 = sol();
        }else if(file_tokens[currentToken].type == _VarToken){
            var1 = getVarByName(keywordGet(&file_tokens[currentToken]));
            currentToken++;
        }else if(file_tokens[currentToken].type == _NumberToken){
            var1 -> value.num = numGet(&file_tokens[currentToken]);
            var1 -> type = _Number;
            currentToken++;
        }else if(file_tokens[currentToken].type == _StringToken){
            strcpy(var1 -> value.string, strGet(&file_tokens[currentToken]));
            var1 -> type = _String;
            currentToken++;
        }else{
            char *buffer = malloc(72 + MAX_INPUT_SIZE);
            sprintf(buffer, "SyntaxError: Expected expression evaluating to variable, received \"%s\"",
            file_tokens[currentToken].keyword);
            raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }

        if(file_tokens[currentToken].type == _SOL){
            var2 = sol();
        }else if(file_tokens[currentToken].type == _VarToken){
            var2 = getVarByName(keywordGet(&file_tokens[currentToken]));
            currentToken++;
        }else if(file_tokens[currentToken].type == _NumberToken){
            var2 -> value.num = numGet(&file_tokens[currentToken]);
            var2 -> type = _Number;
            currentToken++;
        }else if(file_tokens[currentToken].type == _StringToken){
            strcpy(var2 -> value.string, strGet(&file_tokens[currentToken]));
            var2 -> type = _String;
            currentToken++;
        }else{
            char *buffer = malloc(72 + MAX_INPUT_SIZE);
            sprintf(buffer, "SyntaxError: Expected expression evaluating to variable, received \"%s\"",
            file_tokens[currentToken].keyword);
            raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }

        eol(1);
        if(var1 -> type != _none && var2 -> type == _none){
            return &False;
        }else if(var1 -> type == _none && var2 -> type != _none){
            return &True;
        }else if(var1 -> type == var2 -> type){
            if(var1 -> type == _none){
                return &False;
            }else if(var1 -> type == _Boolean){
                if(var1 -> value.boolean == var2 -> value.boolean){
                    return &True;
                }else{
                    return &False;
                }
            }else if(var1 -> type == _Number){
                if(var1 -> value.num < var2 -> value.num){
                    return &True;
                }else{
                    return &False;
                }
            }else if(var1 -> type == _String){
                if(strlen(var1 -> value.string) < strlen(var2 -> value.string)){
                    return &True;
                }else{
                    return &False;
                }
            }
        }else{
            char *buffer = malloc(54 + MAX_INPUT_SIZE);
            sprintf(buffer, "TypeError: Cannot compare variables of types %s and %s",
                varTypeGet(var1), varTypeGet(var2));
            raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }
        
    }
    char *buffer = malloc(54 + MAX_INPUT_SIZE);
    sprintf(buffer, "SyntaxError: Expected Less Than Function, received \"%s\"",
    file_tokens[currentToken].keyword);
    raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);

    return NULL;
}

Variable *grtr(){
    if(file_tokens[currentToken].type == _Grtr){
        currentToken++;
        Variable *var1 = malloc(sizeof(Variable)),
                 *var2 = malloc(sizeof(Variable));
        if(file_tokens[currentToken].type == _SOL){
            var1 = sol();
        }else if(file_tokens[currentToken].type == _VarToken){
            var1 = getVarByName(keywordGet(&file_tokens[currentToken]));
            currentToken++;
        }else if(file_tokens[currentToken].type == _NumberToken){
            var1 -> value.num = numGet(&file_tokens[currentToken]);
            var1 -> type = _Number;
            currentToken++;
        }else if(file_tokens[currentToken].type == _StringToken){
            strcpy(var1 -> value.string, strGet(&file_tokens[currentToken]));
            var1 -> type = _String;
            currentToken++;
        }else{
            char *buffer = malloc(72 + MAX_INPUT_SIZE);
            sprintf(buffer, "SyntaxError: Expected expression evaluating to variable, received \"%s\"",
            file_tokens[currentToken].keyword);
            raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }

        if(file_tokens[currentToken].type == _SOL){
            var2 = sol();
        }else if(file_tokens[currentToken].type == _VarToken){
            var2 = getVarByName(keywordGet(&file_tokens[currentToken]));
            currentToken++;
        }else if(file_tokens[currentToken].type == _NumberToken){
            var2 -> value.num = numGet(&file_tokens[currentToken]);
            var2 -> type = _Number;
            currentToken++;
        }else if(file_tokens[currentToken].type == _StringToken){
            strcpy(var2 -> value.string, strGet(&file_tokens[currentToken]));
            var2 -> type = _String;
            currentToken++;
        }else{
            char *buffer = malloc(72 + MAX_INPUT_SIZE);
            sprintf(buffer, "SyntaxError: Expected expression evaluating to variable, received \"%s\"",
            file_tokens[currentToken].keyword);
            raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }

        eol(1);
        if(var1 -> type != _none && var2 -> type == _none){
            return &True;
        }else if(var1 -> type == _none && var2 -> type != _none){
            return &False;
        }else if(var1 -> type == var2 -> type){
            if(var1 -> type == _none){
                return &False;
            }else if(var1 -> type == _Boolean){
                if(var1 -> value.boolean == var2 -> value.boolean){
                    return &True;
                }else{
                    return &False;
                }
            }else if(var1 -> type == _Number){
                if(var1 -> value.num > var2 -> value.num){
                    return &True;
                }else{
                    return &False;
                }
            }else if(var1 -> type == _String){
                if(strlen(var1 -> value.string) > strlen(var2 -> value.string)){
                    return &True;
                }else{
                    return &False;
                }
            }
        }else{
            char *buffer = malloc(54 + MAX_INPUT_SIZE);
            sprintf(buffer, "TypeError: Cannot compare variables of types %s and %s",
                varTypeGet(var1), varTypeGet(var2));
            raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }
        
    }
    char *buffer = malloc(54 + MAX_INPUT_SIZE);
    sprintf(buffer, "SyntaxError: Expected Greater Than Function, received \"%s\"",
    file_tokens[currentToken].keyword);
    raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);

    return NULL;
}

Variable *define(){
    if(file_tokens[currentToken].type == _VarToken){
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
                if(file_tokens[currentToken].type == _StringToken){
                    var -> type = _String;
                    strcpy(var -> value.string, strGet(&file_tokens[currentToken]));
                    currentToken++;
                }else if(file_tokens[currentToken].type == _NumberToken){
                    var -> type = _Number;
                    var -> value.num = numGet(&file_tokens[currentToken]);
                    currentToken++;
                }else if(file_tokens[currentToken].type == _VarToken){
                    Variable *cpyvar = getVarByName(keywordGet(&file_tokens[currentToken]));
                    var -> type = cpyvar -> type;
                    memcpy(&(var -> value), &(cpyvar -> value), sizeof(_VARIABLE));
                    currentToken++;
                }else if(file_tokens[currentToken].type == _SOL){
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

        if(file_tokens[currentToken].type == _StringToken){
            var -> type = _String;
            strcpy(var -> value.string, strGet(&file_tokens[currentToken]));
            currentToken++;
        }else if(file_tokens[currentToken].type == _NumberToken){
            var -> type = _Number;
            var -> value.num = numGet(&file_tokens[currentToken]);
            currentToken++;
        }else if(file_tokens[currentToken].type == _VarToken){
            Variable *cpyvar = getVarByName(keywordGet(&file_tokens[currentToken]));
            var -> type = cpyvar -> type;
            memcpy(&(var -> value), &(cpyvar -> value), sizeof(_VARIABLE));
            currentToken++;
        }else if(file_tokens[currentToken].type == _SOL){
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
    if(file_tokens[currentToken].type == _VarToken){
        raise("NotImplementedError", filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
    }
    return &none;
}

void printsVar(Variable *var){
    if(var -> type == _none){
        printf("none");
    }else if(var -> type == _Boolean){
        if(var -> value.boolean == 0){
            printf("False");
        }else if(var -> value.boolean == 1){
            printf("True");
        }
    }else if(var -> type == _Number){
        printf("%Lg", var->value.num);
    }else if(var -> type == _String){
        printf("%s", var->value.string);
    }
}

Variable *prints(){
    if(file_tokens[currentToken].type == _VarToken && strcmp(file_tokens[currentToken].keyword, "print") == 0){
        currentToken++;
        while(!eol(0)){
            if(file_tokens[currentToken].type == _SOL){
                printsVar(sol());
            }else if(file_tokens[currentToken].type == _VarToken){
                printsVar(getVarByName(keywordGet(&file_tokens[currentToken])));
                currentToken++;
            }else if(file_tokens[currentToken].type == _NumberToken){
                printf("%Lg", numGet(&file_tokens[currentToken]));
                currentToken++;
            }else if(file_tokens[currentToken].type == _StringToken){
                printf("%s", strGet(&file_tokens[currentToken]));
                currentToken++;
            }else{
                char *buffer = malloc(58 + MAX_INPUT_SIZE);
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
    if(file_tokens[currentToken].type == _VarToken){
        
    }
    return &none;
}

void exits(){
    // free all malloc'd memory and exit using given exit status, if any
    if(strcmp(file_tokens[currentToken].keyword, "exit") == 0){
        currentToken++;
        if(file_tokens[currentToken].type == _NumberToken){
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
