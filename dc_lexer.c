#include "dc_lexer.h"

Token COM, SOL, INC, DEC, PLUSEQL, MINEQL, MULTEQL, DIVEQL, PLUS, MIN, MULT, DIV,
        MOD, ASSN, NOTEQL, IF, THEN, ELSE, EOL, EOFS;
Token *token_symbols[] = {&COM, &SOL, &INC, &DEC,
        &PLUSEQL, &MINEQL, &MULTEQL, &DIVEQL, &PLUS, &MIN, &MULT, &DIV,
        &MOD,  &ASSN, &NOTEQL, &IF, &ELSE, &THEN, &EOL, &EOFS};

Token file_tokens[] = {};
int filesize = 0;
int filemax = 0;

int addToFile(Token token){
    printToken(token);
    return 0;
}

void printToken(Token token){        
    printf("%s %d\n", token.keyword, token.type);
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
int matchToken(Token token, char *statement, int length){
    if(matchStart(token.keyword, statement, strlen(token.keyword), length)){
        return true;
    }else{
        return false;
    }
}

void slice_str(const char *str, char *buffer, size_t start, size_t end){
    size_t j = 0;
    for ( size_t i = start; i <= end; ++i ) {
        buffer[j++] = str[i];
    }
    buffer[j] = 0;
}

void lex(char *statement, int length){
    int current = 0;
    char *buffer = malloc(MAX_INPUT_SIZE);
    int not_symbols = 0;
    while(current < length){
        if((statement[current] > 64 && statement[current] < 91) ||
                                    (statement[current] > 96 && statement[current] < 123)){
            while((statement[current] > 47 && statement[current] < 58) ||
                                    (statement[current] > 64 && statement[current] < 91) ||
                                    (statement[current] > 96 && statement[current] < 123)){
                not_symbols++;
                current++;
            }
            Token token;
            slice_str(statement, token.keyword, current - not_symbols, not_symbols);
            token.type = -2;

            addToFile(token);
            not_symbols = 0;
        }

        if(statement[current] > 47 && statement[current] < 58){
            while(statement[current] > 47 && statement[current] < 58){
                not_symbols++;
                current++;
            }
            Token token;
            slice_str(statement, token.keyword, current - not_symbols, not_symbols);
            token.type = -1;

            addToFile(token);
            not_symbols = 0;
        }
        for(int i = _Com; i < __TOKENS_SIZE; i++){
            slice_str(statement, buffer, current, length);
            if(matchToken(*token_symbols[i], buffer, length - current)){
                addToFile(*token_symbols[i]);
                current += strlen(token_symbols[i] -> keyword) - 1;
                break;
            }
        }
        
        current++;
    }
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
    char end_of_file = EOF;
    char *symbols[] = {"#", // Comment
                        "(", // Start of Line
                        "++", // Increment
                        "--", // Decrement
                        "+=", // Plus Equals
                        "-=", // Minus Equals
                        "*=", // Multiply Equals
                        "/=", // Divide Equals
                        "+", // Plus
                        "-", // Minus
                        "*", // Multiply
                        "/", // Divide
                        "\%", // Modulus
                        "==", // Is Equal To
                        "!=", // Is Not Equal To
                        "?", // If
                        "::", // Else
                        ":", // Then
                        ")", // End of Line
                        &end_of_file}; // End of File

    for(int i = _Com; i < __TOKENS_SIZE; i++){
        strcpy(token_symbols[i] -> keyword, symbols[i]);
        token_symbols[i] -> type = i;
    }
}