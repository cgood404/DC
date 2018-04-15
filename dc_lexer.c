#include "dc_lexer.h"
#define file_inc 2

Token COM = {"#", 0};
Token SOL = {"(", 1};
Token INC = {"++", 2};
Token DEC = {"--", 3};
Token PLUSEQL = {"+=", 4};
Token MINEQL = {"-=", 5};
Token MULTEQL = {"*=", 6};
Token DIVEQL = {"/=", 7};
Token PLUS = {"+", 8};
Token MIN = {"-", 9};
Token MULT = {"*", 10};
Token DIV = {"/", 11};
Token MOD = {"\%", 12};
Token EQL = {"==", 13};
Token NOTEQL = {"!=", 14};
Token IF = {"?", 15};
Token THEN = {":", 16};
Token ELSE = {"::", 17};
Token EOL = {")", 18};
Token EOFS = {(char) EOF, 19};
const Token *token_symbols[] = {&COM, &SOL, &INC, &DEC,
        &PLUSEQL, &MINEQL, &MULTEQL, &DIVEQL, &PLUS, &MIN, &MULT, &DIV,
        &MOD,  &EQL, &NOTEQL, &IF, &ELSE, &THEN, &EOL, &EOFS};

Token *file_tokens;
int file_size = 0;
int file_max = 0;

int addToFile(const Token *token){
    if(file_size >= file_max){
        Token *buffer = malloc((int) (sizeof(file_tokens) * file_inc));
        memcpy(buffer, file_tokens, sizeof(file_tokens)+0);

        free(file_tokens);
        file_max *= file_inc;
        file_tokens = buffer;
    }

    memcpy(&file_tokens[file_size++], token, sizeof(token)+0);
    return 0;
}

void printToken(const Token *token){        
    printf("keyword: %s -- type: %d\n", token -> keyword, token -> type);
}

int matchStart(const char *token, char *input, int token_length, int input_length){
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
int matchToken(const Token *token, char *statement, int length){
    if(matchStart(token -> keyword, statement, strlen(token -> keyword), length)){
        return true;
    }else{
        return false;
    }
}

void slice_str(char *str, char *buffer, int start, int end){
    int j = 0;
    for (int i = start; i <= end; ++i) {
        buffer[j++] = str[i];
    }
    buffer[j] = 0;
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
    char *buffer = malloc(MAX_INPUT_SIZE);
    int not_symbols = 0;
    replace(statement, length, '\n', ' ');
    while(current < length){
        if((statement[current] > 64 && statement[current] < 91) ||
                                    (statement[current] > 96 && statement[current] < 123)){
            while((statement[current] > 47 && statement[current] < 58) ||
                                    (statement[current] > 64 && statement[current] < 91) ||
                                    (statement[current] > 96 && statement[current] < 123)){
                not_symbols++;
                current++;
            }
            slice_str(statement, buffer, current - not_symbols, current-1);

            const Token w_token = {*buffer, -2};
            addToFile(&w_token);
            not_symbols = 0;
        }else if(statement[current] > 47 && statement[current] < 58){
            while(statement[current] > 47 && statement[current] < 58){
                not_symbols++;
                current++;
            }
            slice_str(statement, buffer, current - not_symbols, current-1);

            const Token n_token = {*buffer, -2};
            addToFile(&n_token);
            not_symbols = 0;
        }else{
            for(int i = _Com; i < __TOKENS_SIZE; i++){
                slice_str(statement, buffer, current, length);
                if(matchToken(token_symbols[i], buffer, length - current)){
                    addToFile(token_symbols[i]);
                    current += strlen(token_symbols[i] -> keyword) - 1;
                    break;
                }
            }
            current++;
        }
    }
    for(int i = 0; i < file_size; i++){
        printToken(&file_tokens[i]);
    }
    free(buffer);
    // parse();
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
}

void createTokens(void){
    file_tokens = malloc(0);
}