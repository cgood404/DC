#include "dc_lexer.h"

void createTokens(void){
    char *keywords[] = {"(","+", "-", "*", "/", "\%", "++", "--",
        "=", "==", "!=", "?", ":", "::", "define", "print", ")"};
    PLUS.keyword = "+";
    PLUS.type = _Plus;
    PLUS.destination = plus;

    MIN.keyword = "-";
    MIN.type = _Min;
    MIN.destination = min;
    
}

void plus(char *keyword, int length){

}

void min(char *keyword, int length){

}
