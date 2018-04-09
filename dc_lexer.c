#include "dc_lexer.h"

Token SOL, PLUS, MIN, MULT, DIV, MOD, INC, DEC, ASSN,
        NOTEQL, IF, THEN, ELSE, DEFINE, PRINT, RUN, EOL, EOFS, EXIT, VARIABLE;
Token *tokens[] = {&SOL, &PLUS, &MIN, &MULT, &DIV, &MOD, &INC, &DEC, &ASSN,
        &NOTEQL, &IF, &THEN, &ELSE, &DEFINE, &PRINT, &RUN, &EOL, &EOFS, &EXIT, &VARIABLE};

Token file_tokens[] = {};
int filesize = 0;
int filemax = 0;

int addToFile(Token token){

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

void define(char *keyword, int length){
    printf("Found a define token.\n");
}

void print(char *keyword, int length){
    printf("Found a print token.\n");
}

void run(char *keyword, int length){
    printf("Found a run token.\n");
}

void eol(char *keyword, int length){
    printf("Found an end of line token.\n");
}

void eof(char* keyword, int length){
    printf("Found an end of file token.\n");
}

void exits(char* keyword, int length){
    exit(0);
}

void variable(char* keyword, int length){
    printf("Found a variable token.\n");
}

void printToken(Token token){        
    printf("%s %d\n", token.keyword, token.type);
    token.destination("", 0);
}

int matchStart(char *first, char *second, int first_length, int second_length){
    int bool_matches = true;
    if(first_length < second_length){
        for(int i = 0; i < first_length; i++){
            if(first[i] != second[i]){
                bool_matches = false;
            }
        }
    }else{
        for(int i = 0; i < second_length; i++){
            if(first[i] != second[i]){
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

int lex(char *statement, int length){
    for(int i = _SOL; i < __TOKENS_SIZE; i++){
        if(matchToken(*tokens[i], statement, length)){
            addToFile(*tokens[i]);
        }
    }
    return 0;
}

void createTokens(void){
    char *keywords[] = {"(", // Start of Line
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
                        "define", // Define
                        "print", // Print
                        "run", // Run
                        ")", // End of Line
                        "\0", // End of File
                        "exit", // Exit
                        ""}; // Variables (matches everything else)
        
    destination_t destinations[] = {&sol, &plus, &min, &mult, &divide, &mod,
        &inc, &dec, &assn, &noteql, &ifs, &thens, &elses, &define, &print,
        &run, &eol, &eof, &exits, &variable};

    for(int i = _SOL; i < __TOKENS_SIZE; i++){
        strcpy(tokens[i] -> keyword, keywords[i]);
        tokens[i] -> type = i;
        tokens[i] -> destination = destinations[i];
    }
}