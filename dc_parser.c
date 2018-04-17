#include "dc_parser.h"

//define, lambda, print, run, exit
unsigned int current = 0;
int parseFile(){
    while(!eof(&file_tokens[++current])){
        sol(&file_tokens[++current]);
    };
    return 2;
}

void parserError(char *statement){
    printf("%s\n", statement);
    exit(EXIT_FAILURE);
}

int com(Token *token){
    if(token -> type == 0){
        printf("Found Comment\n");
        
        return 1;
    }

    return 0;
}



int sol(Token *token){
    if(token -> type == 1){
        printf("Found start of line\n");
        
        return 1;
    }

    return 0;
}

int inc(Token *token){
    if(token -> type == 2){
        printf("Found Increment\n");
        
        return 1;
    }

    return 0;
}

int dec(Token *token){
    if(token -> type == 3){
        printf("Found Decrement\n");
        
        return 1;
    }

    return 0;
}

int pluseql(Token *token){
    if(token -> type == 4){
        printf("Found plus equals\n");
        
        return 1;
    }

    return 0;
}

int mineql(Token *token){
    if(token -> type == 5){
        printf("Found minus equals\n");
        
        return 1;
    }

    return 0;
}

int multeql(Token *token){
    if(token -> type == 6){
        printf("Found mult equals\n");
        
        return 1;
    }

    return 0;
}

int diveql(Token *token){
    if(token -> type == 7){
        printf("Found divide equals\n");
        
        return 1;
    }

    return 0;
}

int plus(Token *token){
    if(token -> type == 8){
        printf("Found plus sign\n");
        
        return 1;
    }

    return 0;
}

int min(Token *token){
    if(token -> type == 9){
        printf("Found muinus\n");
        
        return 1;
    }

    return 0;
}

int mult(Token *token){
    if(token -> type == 10){
        printf("Found multiply\n");
        
        return 1;
    }

    return 0;
}

int div(Token *token){
    if(token -> type == 11){
        printf("Found division\n");
        
        return 1;
    }

    return 0;
}

int mod(Token *token){
    if(token -> type == 12){
        printf("Found modulus\n");
        
        return 1;
    }

    return 0;
}

int eql(Token *token){
    if(token -> type == 13){
        printf("Found equals\n");
        
        return 1;
    }

    return 0;
}

int noteql(Token *token){
    if(token -> type == 14){
        printf("Found not equal to\n");
        
        return 1;
    }

    return 0;
}

int ifs(Token *token){
    if(token -> type == 15){
        printf("Found an if\n");
        
        return 1;
    }

    return 0;
}

int then(Token *token){
    if(token -> type == 16){
        printf("Found then\n");
        
        return 1;
    }

    return 0;
}

int elses(Token *token){
    if(token -> type == 17){
        printf("Found else\n");
        
        return 1;
    }

    return 0;
}

int eol(Token *token){
    if(token -> type == 18){
        printf("Found end of line\n");
        
        return 1;
    }

    return 0;
}

int eof(Token *token){
    if(token -> type == 19){
        printf("Found end of file\n");
        return 1;
    }
    return 0;
}

