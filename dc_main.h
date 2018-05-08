#ifndef dc_main_h
#define dc_main_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define MAX_FUNCTION_ARGS 16
#define MAX_FUNCTION_SIZE 256
#define MAX_INPUT_SIZE 255
#define num_t long double
#define size_inc 2

// VARIABLE TYPES /////////////////////////////////////////////////////////////////

// 0) the none type, global variable "none" defined in dc_memory.c
// 1) boolean type, global variables "True" and "False" defined in dc_memory.c
// 2) number type, 90 bit floating point numbers using "long double" data type
// 3) string type, maximum length == MAX_INPUT_SIZE

// MAIN ///////////////////////////////////////////////////////////////////////////

struct dc_file {
    char *__name__;
    FILE *file;
};

void readfile(char *file_name);
void raise(char *exception, char *filename, int line, int column);


// TOKENS /////////////////////////////////////////////////////////////////////////


/*
WHEN CREATING NEW KEYWORDS:
    IMPORTANT tokens of type:
        -1: keywords, such as builtins, variables, or functions
        -2: number variable type
        -3: string variable type
    *) DO NOT ADD WORDS AS TOKENS, they are read by the parser. They will be declared
        as their own tokens of type -1.
    **) Tokens should be 1-3 character symbols that have as little overlap as possible
        with other tokens, and that have as little letters and/or numbers as possible
    1) Add the keyword, Capitalized, with a leading _underscore, to the end of the 
        token_types enum, but before __TOKEN_SIZE
    2) Add a declaration for the token to the extern declarations in dc_token.h
    3) Add the Token initialization to the end of the Token initializations at the top
        of dc_lexer.c, in UPPERCASE
    4) Add the token's keyword string to the token declaration in step 2
    5) Add the token's type number to the token declaration in step 2 (This is the
        number corresponding to its enum variable in step 1)
    6) Add a pointer to the token to the token_symbols[] array at the top
        of dc_lexer.c in the order of the token_types enum
    7) Make sure you didn't break anything. If you did, repeat all steps, but slower this time

    variables/functions are type -1, numbers are type -2, strings are type -3
*/
typedef struct Token {
    char keyword[256];
    int type;
    int line;
    int column;
} Token;

enum var_tokens {
    _StringToken = -3, _NumberToken = -2, _VarToken = -1
};
enum _token_types {
    _Com, _SOL, _Plus, _Min, _Mult, _Div, _Mod, _Eql, _Not, _If, _Then, _Else,
    _EOL, _EOF, _Str, _LessEql, _GrtrEql, _Less, _Grtr, __TOKENS_SIZE
};

extern int file_size, file_max;

extern Token COM, SOL, PLUS, MIN, MULT, DIV, MOD,
    EQL, NOTEQL, IF, THEN, ELSE, EOL, EOFS, STR,
    LESSEQL, GRTREQL, LESS, GRTR;


// MEMORY /////////////////////////////////////////////////////////////////////////


typedef struct _variable Variable;
typedef struct _function Function;
typedef union __VARIABLE  _VARIABLE;

extern Function *function_table;
extern unsigned long function_table_size;
extern unsigned long function_table_max;
int addFunction(Function *function);

extern Variable *variable_table;
extern unsigned long variable_table_size;
extern unsigned long variable_table_max;
int addVariable(Variable *variable);
Variable *getVarByName(char *name);

int createTables();

union __VARIABLE { // unions share memory space
    char string[MAX_INPUT_SIZE];
    num_t num;
    short boolean;
};

struct _variable {
    char name[MAX_INPUT_SIZE];
    short type;
    _VARIABLE value;
};

struct _function {
    char name[MAX_INPUT_SIZE];
    Variable arguments[MAX_FUNCTION_ARGS];
    Token code[MAX_FUNCTION_SIZE];
};

extern Variable none, True, False;
enum _variable_vypes {
    _none, _Boolean, _Number, _String
};

// PARSER /////////////////////////////////////////////////////////////////////////


int parseFile();
int parse();
void parserError(char *statement, int line, int column);

char *strGet(Token *token);
num_t numGet(Token *token);
char *keywordGet(Token *token);
char *varTypeGet(Variable *var);
int eol(short raiseEx);
Variable *sol();

extern unsigned int currentToken;


// LEXER /////////////////////////////////////////////////////////////////////////


extern Token *file_tokens;
extern char *filename;

void _init_(void);
void printToken();
void lex();
void lexfile();
int matchToken();
void slice_str();
int matchStart();
int addToFile();
void resetFile(void);


// BUILTINS /////////////////////////////////////////////////////////////////////////

Variable *define();
Variable *lambda();
Variable *prints(short newline);
Variable *runs();
Variable *plus();
Variable *min();
Variable *divs();
Variable *mult();
Variable *mod();
Variable *ifs();
Variable *thens(short runs);
Variable *elses(short runs);
Variable *eql();
Variable *nots();
Variable *lessEql();
Variable *grtrEql();
Variable *less();
Variable *grtr();

void exits();

#endif