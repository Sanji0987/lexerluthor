#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "lexer.h"

#define token_buff 100

void cleanup(FILE *file ,Token *lexer_objects, int token_count){
  cleanup_lexer(lexer_objects, token_count);
  free(lexer_objects);
  fclose(file);
}

int main(){

  Token *lexer_objects = (Token*)malloc(sizeof(Token)*token_buff);

  FILE *file = fopen("test.ll","r");
  int token_count = lexer(file, lexer_objects);

  cleanup(file , lexer_objects, token_count) ; 

  return 0;
}
