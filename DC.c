#include "DC.h"

struct variable VARIABLES[0];
void readfile(char *file_name){
    FILE *file = fopen(file_name, "r");
    if(file == NULL){
        printf("FileNotFound: %s\n", file_name);
        exit(1);
    }
    fclose(file);
}

int main(int argc, char **argv){
    bool read_file = false;
    if(argc > 1 && argv[1]){
        printf("opening file: %s\n", argv[2]);
        read_file = true;
        readfile(argv[1]);
    }
    else{
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