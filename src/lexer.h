#ifndef LEXER_H_

#define LEXER_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define char_buff 51
// only used for segregation into strings

typedef enum {
        UNKNOWN = 0,
        WORD = 1,
        NUMBER = 2,
        SYMBOL = 3,
        STRING = 4,
} BasicTokenType;


// need type, actual string , line no , value if any else null 
typedef enum{
        TOKEN_LITERAL = 100,
        TOKEN_IDENTIFIER = 200, 
        TOKEN_KEYWORD = 300,
        TOKEN_OPERATOR = 400,
        TOKEN_SEPARATOR = 500,
        TOKEN_EOF = 600,
}TMainType;

typedef enum{
        //placeholder enum 
        PLACEHOLDER = 0 ,

        IDENTIFIER = TOKEN_IDENTIFIER + 1,

        INT_LITERAL = TOKEN_LITERAL + 1,
        STRING_LITERAL = TOKEN_LITERAL + 2,

        EXIT_KEYWORD = TOKEN_KEYWORD + 1,
        BREAK_KEYWORD = TOKEN_KEYWORD + 2,
        IF_KEYWORD = TOKEN_KEYWORD + 3,
        ELSE_KEYWORD = TOKEN_KEYWORD + 4,
        WHILE_KEYWORD = TOKEN_KEYWORD + 5,
        PRINT_KEYWORD = TOKEN_KEYWORD + 6,
        INT_KEYWORD = TOKEN_KEYWORD + 7,
        RETURN_KEYWORD = TOKEN_KEYWORD + 8,

        OPEN_PAREN = TOKEN_SEPARATOR + 1,    
        CLOSE_PAREN = TOKEN_SEPARATOR + 2,   
        SEMICOLON = TOKEN_SEPARATOR + 3,     
        COLON = TOKEN_SEPARATOR + 4,
        OPEN_BRACES = TOKEN_SEPARATOR +5,
        CLOSE_BRACES = TOKEN_SEPARATOR+6,

        EOF_TOKEN = TOKEN_EOF + 1,

        PLUS_OP = TOKEN_OPERATOR + 1,
        MINUS_OP = TOKEN_OPERATOR + 2,
        EQUALS_OP = TOKEN_OPERATOR +3,
        AND_OP      = TOKEN_OPERATOR+ 4,
        OR_OP     = TOKEN_OPERATOR+ 5,
        NOT_OP      = TOKEN_OPERATOR+ 6,
}TSubType;

typedef union{
        int ival;
        char *sval;
}Value;

typedef struct{
        TMainType type;
        TSubType subtype;  
        char *lexeme;
        int line_no;
        Value _value;
}Token;



//FUNCTIONS

const char* get_main_type_name(TMainType type);
const char* get_sub_type_name(TSubType subtype);

void cleanup_lexer(Token *lexer_objects, int token_count);
TSubType type_finder(char *token_buffer , BasicTokenType basicType);
int lexer(FILE *file,Token *lexer_objects);
void create_token(Token *Tokens, int token_count , char *token_buffer, int nettype, int current_line);


#endif //FOO_H_
