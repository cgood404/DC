#ifndef token_dc_h
#define token_dc_h

typedef int destination_t(char*, int);
typedef struct {
    char *keyword;
    int type;
    destination_t destination;
} Token;
enum tokens {
    _Plus, _Min, _Mult, _Div, _Mod, _Inc, _Dec,
    _Assn, _Eql, _NotEql, _If, _Then, _Else,
    _Func, _Var, _Print, _EOL, __TOKENS_SIZE
};

Token SOL, PLUS, MIN, MULT, DIV, MOD, INC, DEC, ASSN,
    EQL, NOTEQL, IF, THEN, ELSE, DEFINE, PRINT, EOL;
#endif