#ifndef token_dc_h
#define token_dc_h

#include "dc.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

/*
WHEN CREATING NEW KEYWORDS:
    *) DO NOT ADD WORDS AS TOKENS, they are read by the parser. They will be declared
        as their own tokens.
    **) Tokens should be 1-3 character symbols that have as little overlap as possible
        with other tokens, and that have as little letters and/or numbers as possible
    1) Add the keyword, Capitalized, with a leading _underscore, to the end of the 
        token_types enum, but before __TOKEN_SIZE
    2) Add the Token declaration to the end of the Token declarations at the top
        of dc_lexer.c, in UPPERCASE
    3) Add the token's keyword string to the token declaration in step 2
    4) Add the token's type number to the token declaration in step 2 (This is the
        number corresponding to its enum variable in step 1)
    5) Add a pointer to the token to the token_symbols[] array at the top
        of dc_lexer.c in the order of the token_types enum
    8) Make sure you didn't break anything. If you did, repeat all steps, but slower this time

    variables/functions are type -1, numbers are type -2, strings are type -3
*/
typedef struct {
    char keyword[256];
    int type;
} Token;

enum token_types {
    _Com, _SOL, _Plus, _Min, _Mult, _Div, _PlusEql, _MinEql, _MultEql, _DivEql,
    _Mod, _Inc, _Dec, _Assn, _NotEql, _If, _Then, _Else,
    _EOL, _EOF, _Str, __TOKENS_SIZE
};

extern int file_size, file_max;
extern Token *file_tokens;

extern Token COM, SOL, PLUS, MIN, MULT, DIV, PLUSEQL, MINEQL, MULTEQL, DIVEQL,
        MOD, INC, DEC, EQL, NOTEQL, IF, THEN, ELSE, EOL, EOFS, STR;

#endif