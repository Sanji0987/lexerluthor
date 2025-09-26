#include "lexer.h"

// next step is to make a struct which holds
// union of what token_type
// value of the token , so string for example "name of a gorilla " or int 1123
// line no (no clue why)
//
const char* get_main_type_name(TMainType type) {
    switch(type) {
        case TOKEN_LITERAL: return "TOKEN_LITERAL";
        case TOKEN_IDENTIFIER: return "TOKEN_IDENTIFIER";
        case TOKEN_KEYWORD: return "TOKEN_KEYWORD";
        case TOKEN_OPERATOR: return "TOKEN_OPERATOR";
        case TOKEN_SEPARATOR: return "TOKEN_SEPARATOR";
        case TOKEN_EOF: return "TOKEN_EOF";
        default: return "UNKNOWN";
    }
}

const char* get_sub_type_name(TSubType subtype) {
  switch(subtype) {
    case INT_LITERAL: return "INT_LITERAL";
    case STRING_LITERAL: return "STRING_LITERAL";
    case EXIT_KEYWORD: return "EXIT_KEYWORD";
    case IF_KEYWORD: return "IF_KEYWORD";
    case OPEN_PAREN: return "OPEN_PAREN";
    case CLOSE_PAREN: return "CLOSE_PAREN";
    case AND_OP: return "AND_OP";
    case OR_OP: return "OR_OP";
    case NOT_OP:return "NOT_OP";
    case PRINT_KEYWORD: return "PRINT_KEYWORD";
    // ... all the other keywords
    case SEMICOLON: return "SEMICOLON";
    case COLON: return "COLON";
    case EQUALS_OP: return "EQUALS_OP";

    case   INT_KEYWORD: return "INT_KEYWORD";
    case  IDENTIFIER: return "IDENTIFIER";
    case  PLUS_OP: return "PLUS_OP";
    case RETURN_KEYWORD: return "RETURN_KEYWORD";
    case OPEN_BRACES: return "OPEN_BRACES";
    case CLOSE_BRACES: return "CLOSED_BRACES";
    case EOF_TOKEN: return "EOF_TOKEN";
    // add more cases as needed
    default: return "UNKNOWN";
  }
}
// remember to free lexeme


void cleanup_lexer(Token *lexer_objects, int token_count){
  for (int i=0 ;i < token_count; i++){
    free(lexer_objects[i].lexeme);
  }

}

TSubType type_finder(char *token_buffer , BasicTokenType basicType){
  char keywords[][10] = {"exit",  "break", "if", "else", "while", "print", "int", "return"};
  int keyword_count = 11;
  bool flag = false;
  if (basicType == NUMBER)return INT_LITERAL;
 
  else if (basicType == STRING) return STRING_LITERAL;
  
  else if (basicType == WORD){
    for (int i= 0 ; i < keyword_count ; i ++ ){
      if (!strcmp(token_buffer, keywords[i])){
        return (TOKEN_KEYWORD + i+1);
        flag = true;
      }
    }
    if (flag != true) return IDENTIFIER;  

  }
  
  else if (basicType == SYMBOL){
    if (token_buffer[0] == '(') return OPEN_PAREN;
    if (token_buffer[0] == ')') return CLOSE_PAREN; 
    if (token_buffer[0] == ';') return SEMICOLON;
    if (token_buffer[0] == ':') return COLON;
    if (token_buffer[0] == '=') return EQUALS_OP;
    if (token_buffer[0] == '+') return PLUS_OP;
    if (token_buffer[0] == '{') return OPEN_BRACES;
    if (token_buffer[0] == '}') return CLOSE_BRACES;
    if (token_buffer[0] == '&') return AND_OP;
    if (token_buffer[0] == '|') return OR_OP;
    if (token_buffer[0] == '~') return NOT_OP;
  }
  return PLACEHOLDER;
}


void create_token(Token *Tokens, int token_count , char *token_buffer, int nettype, int current_line){
  Tokens[token_count].lexeme = strdup(token_buffer);  // or malloc and copy
  Tokens[token_count].type    = (nettype/ 100) * 100 ;
  Tokens[token_count].subtype = nettype;
  Tokens[token_count].line_no = current_line;
}

//create_token(lexer_objects,  token_count , token_buffer , ,  );
int lexer(FILE *file, Token *lexer_objects){
  char *token_buffer = (char*)malloc(sizeof(char)*char_buff);
  int line_no = 1 ;
 
  char current = '\0';
  int i = 0;
  
  int token_count = 0;
  BasicTokenType token_type = UNKNOWN;     
  
  // initially stored all the strings that i seperated from the .ll file here
  //char string_arr[100][50]; 
  memset(token_buffer, '\0', 50); 

  current = fgetc(file);
  bool string_flag = false;

  while (current != EOF) {
    // handles starting and ending of strings
    if (current == '"') {
      if (string_flag == false){
        string_flag = true;
        token_type = STRING;
        token_buffer[i++] = current;
      }
      else if(string_flag == true){
        string_flag = false;
        token_type = UNKNOWN;
        token_buffer[i] = '"';
        token_buffer[i+1] = '\0';
        //strcpy(string_arr[token_count], token_buffer);
        create_token(lexer_objects,  token_count , token_buffer , (TSubType) STRING_LITERAL,  line_no );
        token_count++;
        i = 0;

      }
    }

    // handling the middle of strings
    else if (string_flag == true){
      token_buffer[i++] = current;
    }


    else if ((isalpha(current) || current == '_') && (token_type == WORD || token_type == UNKNOWN)) {
      if (token_type == UNKNOWN) token_type = WORD;
      token_buffer[i++] = current;
    }
    else if (isdigit(current) && (token_type== WORD || token_type == NUMBER || token_type == UNKNOWN)) {
      if (token_type == UNKNOWN) token_type = NUMBER; 
      token_buffer[i++] = current;
    }

    else if (isspace(current)) {
      if (current == '\n')line_no++;
      else if (token_type != UNKNOWN && i > 0) {
        token_buffer[i] = '\0';
        TSubType subtype = type_finder(token_buffer, token_type);
        create_token(lexer_objects, token_count, token_buffer, subtype, line_no);
        token_count++;

        memset(token_buffer, '\0', 50);
        i = 0;
        token_type = UNKNOWN;
      }
    }

    
    
    else {
      if (token_type != UNKNOWN && i > 0) {
        token_buffer[i] = '\0';
        TSubType subtype = type_finder(token_buffer, token_type);
        create_token(lexer_objects, token_count, token_buffer, subtype, line_no);
        token_count++;
      }

      token_buffer[0] = current;
      token_buffer[1] = '\0';
      TSubType subtype = type_finder(token_buffer, SYMBOL);
      create_token(lexer_objects, token_count, token_buffer, subtype, line_no);
      token_count++;

      memset(token_buffer, '\0', 50);
      i = 0;
      token_type = UNKNOWN;
    }


    current = fgetc(file);  
  }

  if (((token_type != UNKNOWN) & (token_type != STRING))&& i > 0) {
    token_buffer[i] = '\0';
    TSubType subtype = type_finder(token_buffer, token_type);
    create_token(lexer_objects, token_count, token_buffer, subtype, line_no);
    token_count++;
  }

  if (current == EOF){
    create_token(lexer_objects, token_count, "EOF", EOF_TOKEN, line_no-1);
    token_count++;
  }
  line_no--;

 /* printf("Found %d tokens:\n", token_count);
  for (int j = 0; j < token_count; j++) {
    printf("Token %d: %s\n", j + 1, string_arr[j]);
  } 
  printf("\n");

  // check string_arr to tokenize the seperated
  for (int i= 0 ; i < token_count ; i ++){
    for (int j = 0 ; j < sizeofkeywords; j++){
      if (!strcmp(string_arr[i], keywords[j])){
        printf("found a keyword:%s\n", keywords[j]);
      }
    }
  } */
 

  // now we have all the tokens in as strings in an array string_arr
  
 
  printf("Found %d tokens:\n", token_count);
  for (int i = 0; i < token_count; i++) {
    printf("Token %d: %s (Type: %s, Subtype: %s, Line: %d)\n", 
           i + 1, 
           lexer_objects[i].lexeme, 
           get_main_type_name(lexer_objects[i].type),
           get_sub_type_name(lexer_objects[i].subtype),
           lexer_objects[i].line_no);
  }
  printf("%d\n", line_no);
  free(token_buffer);
  return token_count;


}
