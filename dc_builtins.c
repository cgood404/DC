#include "dc_main.h"

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

void consumeSOL(){
    if(file_tokens[currentToken].type == _SOL){
        currentToken++;
        while(file_tokens[currentToken].type != _EOL){
            if(file_tokens[currentToken].type == _SOL){
                consumeSOL();
            }else{
                currentToken++;
            }
        }
        eol(1);
    }
}

Variable *ifs(){
    if(file_tokens[currentToken].type == _If){
        currentToken++;
        short runs;
        if(file_tokens[currentToken].type == _VarToken){
            Variable *var = getVarByName(keywordGet(&file_tokens[currentToken]));
            if(var -> type == 0){
                runs = 0;
            }else if(var -> type == 1){
                runs = var -> value.boolean;
            }else{
                runs = 1;
            }
            currentToken++;
        }else if(file_tokens[currentToken].type == _SOL){
            Variable *var = sol();
            if(var -> type == 0){
                runs = 0;
            }else if(var -> type == 1){
                runs = var -> value.boolean;
            }else{
                runs = 1;
            }
        }else if(file_tokens[currentToken].type == _NumberToken ||
                file_tokens[currentToken].type == _StringToken){
            runs = 1;
            currentToken++;
        }else{
            char *buffer = malloc(52 + MAX_INPUT_SIZE);
            sprintf(buffer, "ConditionalError: Expected variable or function, found:  %s",
            file_tokens[currentToken].keyword);
            raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }

        if(runs == 0){
            return thens(0);
        }else if(runs == 1){
            return thens(1);
        }
    }else{
        char *buffer = malloc(52 + MAX_INPUT_SIZE);
        sprintf(buffer, "ConditionalError: Expected function \"If (?)\", found:  %s",
        file_tokens[currentToken].keyword);
        raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
    }
    return &none;
}

Variable *thens(short runs){
    if(file_tokens[currentToken].type == _Then){
        currentToken++;
        if(runs){
            if(file_tokens[currentToken].type == _StringToken){
                Variable *var = malloc(sizeof(Variable));
                var -> type = _String;
                strcpy(var -> value.string, strGet(&file_tokens[currentToken]));
                currentToken++;
                elses(0);
                return var;
            }else if(file_tokens[currentToken].type == _NumberToken){
                Variable *var = malloc(sizeof(Variable));
                var -> type = _Number;
                var -> value.num = numGet(&file_tokens[currentToken]);
                currentToken++;
                elses(0);
                return var;
            }else if(file_tokens[currentToken].type == _VarToken){
                Variable *var = getVarByName(keywordGet(&file_tokens[currentToken]));
                currentToken++;
                elses(0);
                return var;
            }else if(file_tokens[currentToken].type == _SOL){
                Variable *var = sol();
                elses(0);
                return var;
            }else if(file_tokens[currentToken].type == _If){
                Variable *var = ifs();
                elses(0);
                return var;
            }else if(file_tokens[currentToken].type == _Else){
                elses(0);
                return &none;
            }else{
                char *buffer = malloc(52 + MAX_INPUT_SIZE);
                sprintf(buffer, "ConditionalError: Expected variable or expression, found:  %s",
                file_tokens[currentToken].keyword);
                raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
            }
        }else{
            while(file_tokens[currentToken].type != _Else){
                if(file_tokens[currentToken].type == _Then){
                    thens(0);
                }else{
                    currentToken++;
                }
            }
            return elses(1);
        }
    }else{
        char *buffer = malloc(52 + MAX_INPUT_SIZE);
        sprintf(buffer, "ConditionalError: Expected function \"Then (:)\", found:  %s",
        file_tokens[currentToken].keyword);
        raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
    }
    return NULL;
}

Variable *elses(short runs){
    if(file_tokens[currentToken].type == _Else){
        currentToken++;
        if(runs){
            if(file_tokens[currentToken].type == _StringToken){
                Variable *var = malloc(sizeof(Variable));
                var -> type = _String;
                strcpy(var -> value.string, strGet(&file_tokens[currentToken]));
                currentToken++;
                return var;
            }else if(file_tokens[currentToken].type == _NumberToken){
                Variable *var = malloc(sizeof(Variable));
                var -> type = _Number;
                var -> value.num = numGet(&file_tokens[currentToken]);
                currentToken++;
                return var;
            }else if(file_tokens[currentToken].type == _VarToken){
                Variable *var = getVarByName(keywordGet(&file_tokens[currentToken]));
                currentToken++;
                return var;
            }else if(file_tokens[currentToken].type == _SOL){
                Variable *var = sol();
                return var;;
            }else if(file_tokens[currentToken].type == _If){
                Variable *var = ifs();
                return var; 
            }else if(file_tokens[currentToken].type == _EOL ||
                    file_tokens[currentToken].type == _Else){
                return &none;
            }else{
                char *buffer = malloc(52 + MAX_INPUT_SIZE);
                sprintf(buffer, "ConditionalError: Expected variable or expression, found:  %s",
                file_tokens[currentToken].keyword);
                raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
            }
        }else{
            while(!eol(0)){
                if(file_tokens[currentToken].type == _SOL){
                    consumeSOL();
                }else if(file_tokens[currentToken].type == _Else){
                    elses(0);
                }else{
                    currentToken++;
                }
            }
        }
    }else{
        if(runs){
            char *buffer = malloc(52 + MAX_INPUT_SIZE);
            sprintf(buffer, "ConditionalError: Expected function \"Else (::)\", found:  %s",
            file_tokens[currentToken].keyword);
            raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }else{
            while(!eol(0)){
                if(file_tokens[currentToken].type == _SOL){
                    consumeSOL();
                }else if(file_tokens[currentToken].type == _Else){
                    elses(0);
                }else{
                    currentToken++;
                }
            }
        }
    }
    return NULL;
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
             
        }else if(file_tokens[currentToken].type == _SOL){
            var = sol();
             
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
        // if variable is already declared, or is marked to be overwritten, redefine it
        for(int i = 0; i < variable_table_size; i++){
            if(strcmp(variable_table[i].name, name) == 0 || variable_table[i].type == -1){
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
                    var = getVarByName(keywordGet(&file_tokens[currentToken]));
                    currentToken++;
                }else if(file_tokens[currentToken].type == _SOL){
                    var = sol();
                    strcpy(var -> name, name);
                }else{
                    char *buffer = malloc(53 + MAX_INPUT_SIZE);
                    sprintf(buffer, "SyntaxError: Expected String or Number, received \"%s\" of type %d",
                    file_tokens[currentToken].keyword, file_tokens[currentToken].type);
                    raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
                }

                variable_table[i] = *var;

                return &none;
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
            var = getVarByName(keywordGet(&file_tokens[currentToken]));
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
        return &none;
    }else{
        char *buffer = malloc(53 + MAX_INPUT_SIZE);
        sprintf(buffer, "SyntaxError: Expected define function, received \"%s\"",
            file_tokens[currentToken].keyword);
        raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        return &none;
    }
}

// does not delete the variable, but marks it to be overwritten by the next define
Variable *deleteVar(){
    char *name = keywordGet(&file_tokens[currentToken]);

    for(int i = 0; i < variable_table_size; i++){
        if(strcmp(name, variable_table[i].name) == 0){
            variable_table[i].type = -1;
            return &none;
        }
    }

    char *buffer = malloc(46 + MAX_INPUT_SIZE);
    sprintf(buffer, "SyntaxError: no variable of name \"%s\" exists",
        file_tokens[currentToken].keyword);
    raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
    return NULL;
}

Variable *lambda(){
    if(file_tokens[currentToken].type == _VarToken){
        currentToken++;
        char *name = keywordGet(&file_tokens[currentToken]);
        currentToken++;

        int argsize = 0;
        if(file_tokens[currentToken].type == _SOL){
            currentToken++;
            while(!eol(0)){
                if(file_tokens[currentToken].type == _VarToken){
                    argsize++;
                    currentToken++;
                }else{
                    char *buffer = malloc(53 + MAX_INPUT_SIZE);
                    sprintf(buffer, "SyntaxError: Expected function argument as variable name, received \"%s\"",
                        file_tokens[currentToken].keyword);
                    raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
                }
            }
            char **args = NULL;
            args = malloc(argsize * sizeof *args);
            for(int i = 1; i <= argsize; i++){
                args[i-1] = keywordGet(&file_tokens[currentToken - i]);
            }

            eol(1);
            int tokenStart = currentToken;
            while(!eol(0)){
                if(file_tokens[currentToken].type == _SOL){
                    consumeSOL();
                }else{
                    currentToken++;
                }
            }

            return addFunction(allocateFunction(name, args, argsize, tokenStart, currentToken));
        }else{
            char *buffer = malloc(53 + MAX_INPUT_SIZE);
            sprintf(buffer, "SyntaxError: Expected function args as expression, received \"%s\"",
                file_tokens[currentToken].keyword);
            raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
        }
    }
    return &none;
}

Variable *prints(short newline){
    if(file_tokens[currentToken].type == _VarToken){
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
    if(newline){
        printf("\n");
    }
    return &none;
}

void exits(){
    // free all malloc'd memory and exit using given exit status, if any
    if(strcmp(file_tokens[currentToken].keyword, "exit") == 0){
        currentToken++;
        if(file_tokens[currentToken].type == _NumberToken){
            int status = (int) numGet(&file_tokens[currentToken]);
            currentToken++;
            eol(1);

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

Variable *runs(){
    if(file_tokens[currentToken].type == _VarToken){
        currentToken++;
        while(!eol(0)){
            sol();
        }
        return &none;
    }
    return &none;
}


Variable *loop(){
    if(file_tokens[currentToken].type == _VarToken){
        currentToken++;
        unsigned int tokenBackup = currentToken;
        short runs = 1;
        
        do{
            currentToken = tokenBackup;
            if(file_tokens[currentToken].type == _VarToken){
                Variable *var = getVarByName(keywordGet(&file_tokens[currentToken]));
                if(var -> type == 0){
                    runs = 0;
                }else if(var -> type == 1){
                    runs = var -> value.boolean;
                }else{
                    runs = 1;
                }
                currentToken++;
            }else if(file_tokens[currentToken].type == _SOL){
                Variable *var = sol();
                if(var -> type == 0){
                    runs = 0;
                }else if(var -> type == 1){
                    runs = var -> value.boolean;
                }else{
                    runs = 1;
                }
            }else if(file_tokens[currentToken].type == _NumberToken ||
                    file_tokens[currentToken].type == _StringToken){
                runs = 1;
                currentToken++;
            }else{
                char *buffer = malloc(52 + MAX_INPUT_SIZE);
                sprintf(buffer, "ConditionalError: Expected variable or function, found:  %s",
                file_tokens[currentToken].keyword);
                raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
            }

            if(runs){
                sol();
            }else{
                while(file_tokens[currentToken].type != _EOL){
                    if(file_tokens[currentToken].type == _SOL){
                        consumeSOL();
                    }else{
                        currentToken++;
                    }
                }
            }
        }while(runs);
        
    }else{
        char *buffer = malloc(39 + MAX_INPUT_SIZE);
        sprintf(buffer, "Expected loop function, received \"%s\"",
        file_tokens[currentToken].keyword);
        raise(buffer, filename, file_tokens[currentToken].line, file_tokens[currentToken].column);
    }
}