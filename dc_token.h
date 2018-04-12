#ifndef token_dc_h
#define token_dc_h


/*
WHEN CREATING NEW KEYWORDS:
    *) DO NOT ADD WORDS AS TOKENS, they are read by the parser. They will be declared
        as their own tokens.
    1) Add the keyword, Capitalized, with a leading _underscore, to the end of the 
        token_types enum, but before __TOKEN_SIZE
    2) Add the Token declaration to the end of the Token declarations at the top
        of dc_lexer.c, in UPPERCASE
    3) Add the keyword's string to the end of the keywords variable in dc_lexer.c
    4) Add the Token from step 2 to the end of the token_symbols[] array in dc_lexer.c ORDER MATTERS
    5) Create a function at the end of dc_lexer.c for the keyword
    6) Add a declaration for the function to the end of the list in dc_lexer.h
    7) Add a pointer to the function declared in step 5 to the end of the *destinations[] array
    8) Make sure you didn't break anything. If you did, repeat all steps, but slower this time
*/
typedef struct {
    char keyword[20];
    int type;
} Token;
enum token_types {
    _Com, _SOL, _Plus, _Min, _Mult, _Div, _PlusEql, _MinEql, _MultEql, _DivEql,
    _Mod, _Inc, _Dec, _Assn, _NotEql, _If, _Then, _Else,
    _EOL, _EOF, __TOKENS_SIZE
};

extern Token COM, SOL, PLUS, MIN, MULT, DIV, PLUSEQL, MINEQL, MULTEQL, DIVEQL,
        MOD, INC, DEC, ASSN, NOTEQL, IF, THEN, ELSE, EOL, EOFS;

#endif