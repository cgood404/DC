#include "dc_lexer.h"
#define file_inc 2

Token COM = {.keyword = "#", .type = 0};
Token SOL = {.keyword = "(", .type = 1};
Token INC = {.keyword = "++", .type = 2};
Token DEC = {.keyword = "--", .type = 3};
Token PLUSEQL = {.keyword = "+=", .type = 4};
Token MINEQL = {.keyword = "-=", .type = 5};
Token MULTEQL = {.keyword = "*=", .type = 6};
Token DIVEQL = {.keyword = "/=", .type = 7};
Token PLUS = {.keyword = "+", .type = 8};
Token MIN = {.keyword = "-", .type = 9};
Token MULT = {.keyword = "*", .type = 10};
Token DIV = {.keyword = "/", .type = 11};
Token MOD = {.keyword = "\%", .type = 12};
Token EQL = {.keyword = "==", .type = 13};
Token NOTEQL = {.keyword = "!=", .type = 14};
Token IF = {.keyword = "?", .type = 15};
Token THEN = {.keyword = ":", .type = 16};
Token ELSE = {.keyword = "::", .type = 17};
Token EOL = {.keyword = ")", .type = 18};
Token EOFS = {.keyword = (char) EOF, .type = 19};

Token *token_symbols[] = {&COM, &SOL, &INC, &DEC,
        &PLUSEQL, &MINEQL, &MULTEQL, &DIVEQL, &PLUS, &MIN, &MULT, &DIV,
        &MOD,  &EQL, &NOTEQL, &IF, &ELSE, &THEN, &EOL, &EOFS};

Token *file_tokens;
int file_size = 1;
int file_max = 1;

int addToFile(Token *token){
    if(file_size >= file_max){
        Token *buffer = malloc((int) (sizeof(Token) * file_size * file_inc));
        memmove(buffer, file_tokens, (sizeof(Token) * file_size) + 0);

        free(file_tokens);
        file_max *= file_inc;
        file_tokens = buffer;
    }

    memmove(&file_tokens[file_size], token, sizeof(*token));
    file_size++;
    return 0;
}

void resetFile(){
    free(file_tokens);
    file_size = file_max = 1;
    file_tokens = malloc(0);
}

void printToken(Token *token){        
    printf("keyword: %s -- type: %d\n", token -> keyword, token -> type);
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
    replace(statement, length, '\n', ' ');
    while(current < length){
        if(statement[current] == ' '){
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
            memmove(&w_token, buffer, not_symbols+1);
            w_token.type = -2;

            addToFile(&w_token);
            not_symbols = 0;
        }else if(statement[current] > 47 && statement[current] < 58){
            while(statement[current] > 47 && statement[current] < 58){
                not_symbols++;
                current++;
            }
            slice_str(statement, buffer, current - not_symbols, current);

            Token n_token;
            memmove(&n_token, buffer, not_symbols+1);
            n_token.type = -1;

            addToFile(&n_token);
            not_symbols = 0;
        }else{
            int error = 1;
            for(int i = _Com; i < __TOKENS_SIZE; i++){
                slice_str(statement, buffer, current, length);
                if(matchToken(token_symbols[i], buffer, length - current)){
                    addToFile(token_symbols[i]);
                    current += strlen(token_symbols[i] -> keyword) - 1;
                    error = 0;
                    break;
                }
            }
            if(error){
                char* error_statement = (char *)malloc(MAX_INPUT_SIZE);
                sprintf(error_statement, "Invalid token in statement: %s, at character: %d",
                                        statement, current);
                lexerError(error_statement);
            }
            current++;
        }
    }
    free(buffer);
}

void lexfile(char *file_name){
    FILE *file = fopen(file_name, "r");
    if(file == NULL || file <= 0){
        printf("FileNotFoundError: %s\n", file_name);
        exit(1);
    }
    char *inputstr = (char *) malloc(MAX_INPUT_SIZE);
    while(fgets(inputstr, MAX_INPUT_SIZE, file) != NULL){
        printf(">> %s\n", inputstr);
        lex(inputstr, strlen(inputstr));
    }
    addToFile(&EOFS);
}

void lexerError(char *error_statement){
    printf("%s\n", error_statement);
    exit(0);
}

void createTokens(void){
    file_tokens = malloc(0);
}
