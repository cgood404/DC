#include "dc_main.h"

Token COM = {.keyword = "#", .type = 0};
Token SOL = {.keyword = "(", .type = 1};
Token PLUS = {.keyword = "+", .type = 2};
Token MIN = {.keyword = "-", .type = 3};
Token MULT = {.keyword = "*", .type = 4};
Token DIV = {.keyword = "/", .type = 5};
Token MOD = {.keyword = "\%", .type = 6};
Token EQL = {.keyword = "==", .type = 7};
Token NOT = {.keyword = "!", .type = 8};
Token IF = {.keyword = "?", .type = 9};
Token THEN = {.keyword = ":", .type = 10};
Token ELSE = {.keyword = "::", .type = 11};
Token EOL = {.keyword = ")", .type = 12};
Token EOFS = {.keyword = (char) EOF, .type = 13};
Token STR = {.keyword = "\"", .type = 14};
Token LESSEQL = {.keyword = "<=", .type = 15};
Token GRTREQL = {.keyword = ">=", .type = 16};
Token LESS = {.keyword = "<", .type = 17};
Token GRTR = {.keyword = ">", .type = 18};

Token *token_symbols[] = {&COM, &SOL, &PLUS, &MIN, &MULT, &DIV,
        &MOD,  &EQL, &NOT, &IF, &ELSE, &THEN, &EOL, &EOFS, &STR,
        &LESSEQL, &GRTREQL, &LESS, &GRTR};

Token *file_tokens;
int file_size = 1;
int file_max = 1;

char *filename;
int line = 0;

int addToFile(Token *token, int line, int column){
    if(file_size >= file_max){
        Token *buffer = malloc((int) (sizeof(Token) * file_size * size_inc));
        memmove(buffer, file_tokens, (sizeof(Token) * file_size) + 0);

        free(file_tokens);
        file_max *= size_inc;
        file_tokens = buffer;
    }

    memmove(&file_tokens[file_size], token, sizeof(*token));
    file_tokens[file_size].line = line;
    file_tokens[file_size].column = column;
    file_size++;
    return 0;
}

void resetFile(){
    free(file_tokens);
    file_size = file_max = 1;
    file_tokens = malloc(0);
}

void printToken(Token *token){        
    printf("keyword: %s -- type: %d\n\tline: %d, column: %d\n",
                    token -> keyword, token -> type, token -> line, token -> column);
}

int matchStart(char *token, char *input, int token_length, int input_length){
    int bool_matches = true;
    if(token_length == 0 && input != '\0'){
        return bool_matches;
    }else if(token_length > input_length){
        bool_matches = false;
    }else{
        for(int i = 0; i < token_length; i++){
            if(token[i] != input[i]){
                bool_matches = false;
            }
        }
    }
    return bool_matches;
}

// Just a high level wrapper for the matchStart function
int matchToken(Token *token, char *statement, int length){
    if(matchStart(token -> keyword, statement, strlen(token -> keyword), length)){
        return true;
    }else{
        return false;
    }
}

void slice_str(char *str, char *buffer, int start, int end){
    memmove(buffer, str + start, end - start);
    buffer[end-start] = '\0';
}


void replace(char* src, int src_length, char oldchar, char newchar){
    for(int i = 0; i < src_length; i++){
        if(src[i] == oldchar){
            src[i] = newchar;
        }
    }
}

void lex(char *statement, int length){
    int current = 0;
    char *buffer = malloc(MAX_INPUT_SIZE + 1);
    int not_symbols = 0;
    while(current < length){
        if(statement[current] == ' ' || statement[current] == '\n'){
            current++;
        }else if((statement[current] > 64 && statement[current] < 91) ||
                                    (statement[current] > 96 && statement[current] < 123)){
            while((statement[current] > 47 && statement[current] < 58) ||
                                    (statement[current] > 64 && statement[current] < 91) ||
                                    (statement[current] > 96 && statement[current] < 123)){
                not_symbols++;
                current++;
            }
            slice_str(statement, buffer, current - not_symbols, current);

            Token w_token;
            memmove(&w_token.keyword, buffer, not_symbols+1);
            w_token.type = -1;

            addToFile(&w_token, line, current - not_symbols);
            not_symbols = 0;
        }else if((statement[current] > 47 && statement[current] < 58) ||
                statement[current] == 46 || statement[current] == 45){
            if(matchToken(&MIN, &statement[current], strlen(MIN.keyword)) &&
                    file_tokens[file_size - 1].type == _SOL){
                addToFile(&MIN, line, current);
                current += strlen(MIN.keyword);
            }else{
                not_symbols++;
                current++;
                while((statement[current] > 47 && statement[current] < 58) || statement[current] == 46){
                    not_symbols++;
                    current++;
                }
                slice_str(statement, buffer, current - not_symbols, current);

                Token n_token;
                memmove(&n_token.keyword, buffer, not_symbols+1);
                n_token.type = -2;

                addToFile(&n_token, line, current - not_symbols);
                not_symbols = 0;
            }
        }else{
            int error = 1;
            for(int i = _Com; i < __TOKENS_SIZE; i++){
                slice_str(statement, buffer, current, length);
                if(matchToken(token_symbols[i], buffer, length - current)){
                    // if token is comment, ignore the rest of the line
                    if(i == _Com){
                        while(statement[current] != '\n'){
                            current++;
                        }
                        error = 0;
                    // if token is a string, save everything up to the next " as a type -3
                    }else if(i == _Str){
                        char *returnStr = malloc(MAX_INPUT_SIZE * sizeof(char));
                        current++;
                        slice_str(statement, buffer, current, length);
                        int str_len = 0;
                        while(!matchToken(&STR, buffer, length - current)){
                            if(current == length){
                                sprintf(buffer, "StringError: Unclosed string in statement: \"%s\"", statement);
                                raise(buffer, filename, line, current);
                            }else if(statement[current] == '\\'){
                                current++;
                                if(statement[current] == 'n'){
                                    returnStr[str_len] = '\n';
                                    str_len++;
                                    current++;
                                }else if(statement[current] == 't'){
                                    returnStr[str_len] = '\t';
                                    str_len++;
                                    current++;
                                }else if(statement[current] == 'r'){
                                    returnStr[str_len] = '\r';
                                    str_len++;
                                    current++;
                                }else if(statement[current] == 'v'){
                                    returnStr[str_len] = '\v';
                                    str_len++;
                                    current++;
                                }else if(statement[current] == '\\'){
                                    returnStr[str_len] = '\\';
                                    str_len++;
                                    current++;
                                }else if(statement[current] == '\''){
                                    returnStr[str_len] = '\'';
                                    str_len++;
                                    current++;
                                }else if(statement[current] == '\"'){
                                    returnStr[str_len] = '\"';
                                    str_len++;
                                    current++;
                                }
                            }else{
                                returnStr[str_len] = statement[current];
                                current++;
                                str_len++;
                            }
                            slice_str(statement, buffer, current, length);
                        }
                        
                        if(str_len == 0){
                            Token str_token = {.keyword = "", .type = -3};
                            addToFile(&str_token, line, current);
                            error = 0;
                        }else{
                            returnStr[str_len] = '\0';
                            Token *str_token = malloc(sizeof(Token));
                            str_token -> type = -3;

                            strcpy(str_token -> keyword, returnStr);
                            
                            addToFile(str_token, line, current - str_len);
                            error = 0;
                        }
                    }else{
                        addToFile(token_symbols[i], line, current);
                        current += strlen(token_symbols[i] -> keyword) - 1;
                        error = 0;
                    }
                    break;
                }
            }
            if(error){
                char* error_statement = (char *)malloc(MAX_INPUT_SIZE);
                sprintf(error_statement, "TokenError: Unknown token in statement: \"%s\"",
                                        statement);
                raise(error_statement, filename, line, current);
            }
            current++;
        }
    }
    free(buffer);
}

void lexfile(char *file_name){
    filename = file_name;
    FILE *file = fopen(file_name, "r");
    if(file == NULL || file <= 0){
        printf("FileNotFoundError: \"%s\"\n", file_name);
        exit(1);
    }
    char *inputstr = (char *) malloc(MAX_INPUT_SIZE);
    while(fgets(inputstr, MAX_INPUT_SIZE, file) != NULL){
        line++;
        lex(inputstr, strlen(inputstr));
    }
    addToFile(&EOFS, line, -1);
}

void _init_(void){
    file_tokens = malloc(0);
    createTables();
    addVariable(&none);
    addVariable(&True);
    addVariable(&False);
}
