#include "dc_lexer.h"

Token SOL, PLUS, MIN, MULT, DIV, MOD, INC, DEC, ASSN,
        NOTEQL, IF, THEN, ELSE, EOL, EOFS;
Token *tokens[] = {&SOL, &PLUS, &MIN, &MULT, &DIV, &MOD, &INC, &DEC, &ASSN,
        &NOTEQL, &IF, &THEN, &ELSE, &EOL, &EOFS};

Token file_tokens[] = {};
int filesize = 0;
int filemax = 0;

int addToFile(Token token){
    printToken(token);
    return 0;
}

void sol(char *keyword, int length){
    printf("Found a start of line token.\n");
}

void plus(char *keyword, int length){
    printf("Found a plus token.\n");
}

void min(char *keyword, int length){
    printf("Found a minus token.\n");
}

void mult(char *keyword, int length){
    printf("Found a multiply token.\n");
}

void divide(char *keyword, int length){
    printf("Found a divide token.\n");
}

void mod(char *keyword, int length){
    printf("Found a modulus token.\n");
}

void inc(char *keyword, int length){
    printf("Found an increment token.\n");
}

void dec(char *keyword, int length){
    printf("Found a decrement token.\n");
}

void assn(char *keyword, int length){
    printf("Found an assignment token.\n");
}

void eql(char *keyword, int length){
    printf("Found an equals token.\n");
}

void noteql(char *keyword, int length){
    printf("Found a not equals token.\n");
}

void ifs(char *keyword, int length){
    printf("Found an if token.\n");
}

void thens(char *keyword, int length){
    printf("Found a then token.\n");
}

void elses(char *keyword, int length){
    printf("Found an else token.\n");
}

void eol(char *keyword, int length){
    printf("Found an end of line token.\n");
}

void eof(char* keyword, int length){
    printf("Found an end of file token.\n");
}

void printToken(Token token){        
    printf("%s %d\n", token.keyword, token.type);
    token.destination("", 0);
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

int lex(char *statement, int length){
    int j = 0;
    char *buffer;
    while(j < length){
        for(int i = _SOL; i < __TOKENS_SIZE; i++){
            slice_str(statement, buffer, j, length);
            if(matchToken(*tokens[i], buffer, length - j)){
                addToFile(*tokens[i]);
                j += strlen(tokens[i] -> keyword) - 1;
            }
        }
        j++;
    }
    return 0;
}

void createTokens(void){
    char end_of_file = EOF;
    char *symbols[] = {"(", // Start of Line
                        "+", // Plus
                        "-", // Minus
                        "*", // Multiply
                        "/", // Divide
                        "\%", // Modulus
                        "++", // Increment
                        "--", // Decrement
                        "==", // Is Equal To
                        "!=", // Is Not Equal To
                        "?", // If
                        ":", // Then
                        "::", // Else
                        ")", // End of Line
                        &end_of_file}; // End of File
        
    destination_t destinations[] = {&sol, &plus, &min, &mult, &divide, &mod,
        &inc, &dec, &assn, &noteql, &ifs, &thens, &elses, &eol, &eof};

    for(int i = _SOL; i < __TOKENS_SIZE; i++){
        strcpy(tokens[i] -> keyword, symbols[i]);
        tokens[i] -> type = i;
        tokens[i] -> destination = destinations[i];
    }
}