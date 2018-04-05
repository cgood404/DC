#include "dc_lexer.h"
#include "dc_token.h"

// I HATE "IF" STATEMENTS >:(

void createTokens(void){
    Token SOL, PLUS, MIN, MULT, DIV, MOD, INC, DEC, ASSN,
        EQL, NOTEQL, IF, THEN, ELSE, DEFINE, PRINT, RUN, EOL, EXIT;

    Token tokens[] = {SOL, PLUS, MIN, MULT, DIV, MOD, INC, DEC, ASSN,
        EQL, NOTEQL, IF, THEN, ELSE, DEFINE, PRINT, RUN, EOL, EXIT};

    char *keywords[] = {"(","+", "-", "*", "/", "\%", "++", "--",
        "=", "==", "!=", "?", ":", "::", "define", "print", "run", ")", "\0", "exit"};
        
    destination_t destinations[] = {*sol, *plus, *min, *mult, *divide, *mod,
        *inc, *dec, *assn, *eql, *noteql, *ifs, *thens, *elses, *define, *print, *run, *eol, *eof, *exits};

    for(int i = _SOL; i < __TOKENS_SIZE; i++){
        tokens[i].type = i;
        tokens[i].keyword = keywords[i];
        tokens[i].destination = destinations[i];
    }
    // for(int i = _SOL; i < __TOKENS_SIZE; i++){
    //     printf("TOKEN: %s %d\n", tokens[i].keyword, tokens[i].type);
    //     tokens[i].destination("", 0);
    // }
}

void lex(char *line, int length){
    for(int i = 0; i < length; i++){

    }
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

void exits(char*keyword, int length){
    exit(0);
}