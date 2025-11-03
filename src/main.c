#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"


#define token_buff 100

void cleanup(FILE *file ,Token *lexer_objects, int token_count){
        cleanup_lexer(lexer_objects, token_count);
        free(lexer_objects);
        fclose(file);
}

int main(int argc ,char *argv[]){
        if (argc < 2) {
                printf("Usage:%s <Path to file/filename>" , argv[0]);
                return -1;
        }
        else {

                Token *lexer_objects = (Token*)malloc(sizeof(Token)*token_buff);
                
                char *path = argv[1];
                FILE *file = fopen(path,"r");

                int token_count = lexer(file, lexer_objects);   // called the lexer
                parser();                                       // called the parser

                cleanup(file , lexer_objects, token_count) ; 

                return 0;
        }
}
