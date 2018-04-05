#ifndef token_dc_h
#define token_dc_h

typedef int destination_t(char*, int);
typedef struct _Token {
    char *keyword;
    char *type;
    destination_t destination;
} Token;
enum {
    Plus, Min, Mult, Div, Mod, Inc, Dec,
    Assn, Eql, NotEql, If, Else,
    Func, Main, Var, Print, EOL
};


#endif