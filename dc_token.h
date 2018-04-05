#ifndef token_dc_h
#define token_dc_h


/*
WHEN CREATING NEW KEYWORDS:
    1) Add the keyword, Capitalized, with a leading _underscore, to the end of the 
        token_types enum, but before __TOKEN_SIZE
    2) Add the Token declaration to the end of the Token declarations at the top
        of dc_lexer.c, in UPPERCASE
    3) Add the keyword's string to the end of the keywords variable in dc_lexer.c
    4) Add the Token from step 2 to the end of the tokens[] array
    5) Create a function at the end of dc_lexer.c for the keyword
    6) Add a declaration for the function to the end of the list in dc_lexer.h
    7) Add a pointer to the function declared in step 5 to the end of the *destinations[] array
    8) Make sure you didn't break anything. If you did, repeat all steps, but slower this time
*/
typedef void (*destination_t)(char*, int);
typedef struct {
    char keyword[20];
    int type;
    destination_t destination;
} Token;
enum token_types {
    _SOL, _Plus, _Min, _Mult, _Div, _Mod, _Inc, _Dec,
    _Assn, _Eql, _NotEql, _If, _Then, _Else,
    _Define, _Print, _Run,  _EOL, _Exits, __TOKENS_SIZE
};

extern Token SOL, PLUS, MIN, MULT, DIV, MOD, INC, DEC, ASSN,
        EQL, NOTEQL, IF, THEN, ELSE, DEFINE, PRINT, RUN, EOL, EXIT;

#endif