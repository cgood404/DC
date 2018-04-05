#include "dc.h"


void readfile(char *file_name){
    FILE *file = fopen(file_name, "r");
    if(file == NULL || file <= 0){
        printf("FileNotFoundError: %s\n", file_name);
        exit(1);
    }
    fclose(file);
}

int main(int argc, char **argv){
    if(argc > 1 && argv[1]){ // if user specifies a file to open
        readfile(argv[1]);
    }
    else{ // if user wants a command line
        printf("DC v0.0.1\nNo copyright, no money back, no nothin\'\n\n");
        while(true){
            char inputstr[100];
            printf(">> ");
            scanf("%s", inputstr);
            if(strncmp(inputstr, "exit", 100) == 0){
                return 0;
            }
        }
        
    }
}