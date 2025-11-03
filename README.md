# LexerLuthor 

A simple lexical analysis for a custom programming language , written in C.

## How to use it 

Need to compile it and use it.

### Step 1: 
```bash
git clone https://github.com/Sanji0987/lexerluthor.git
cd lexerluthor
```
### Step 2:
```bash
    gcc -o lexer main.c -std=99
```

### Step 3:
```bash
    ./lexer test.ll
```
### Example
```
-> cat main.ll
int my_var = 10;
if (my_var > 5) {
        print("hello");
}
```
```
-> ./main main.ll
Found 19 tokens:
Token 1: int (Type: TOKEN_KEYWORD, Subtype: INT_KEYWORD, Line: 1)
Token 2: my_var (Type: TOKEN_IDENTIFIER, Subtype: IDENTIFIER, Line: 1)
Token 3: = (Type: TOKEN_OPERATOR, Subtype: EQUALS_OP, Line: 1)
Token 4: 10 (Type: TOKEN_LITERAL, Subtype: INT_LITERAL, Line: 1)
Token 5: ; (Type: TOKEN_SEPARATOR, Subtype: SEMICOLON, Line: 1)
Token 6: if (Type: TOKEN_KEYWORD, Subtype: IF_KEYWORD, Line: 2)
Token 7: ( (Type: TOKEN_SEPARATOR, Subtype: OPEN_PAREN, Line: 2)
Token 8: my_var (Type: TOKEN_IDENTIFIER, Subtype: IDENTIFIER, Line: 2)
Token 9: > (Type: UNKNOWN, Subtype: UNKNOWN, Line: 2)
Token 10: 5 (Type: TOKEN_LITERAL, Subtype: INT_LITERAL, Line: 2)
Token 11: ) (Type: TOKEN_SEPARATOR, Subtype: CLOSE_PAREN, Line: 2)
Token 12: { (Type: TOKEN_SEPARATOR, Subtype: OPEN_BRACES, Line: 2)
Token 13: print (Type: TOKEN_KEYWORD, Subtype: PRINT_KEYWORD, Line: 3)
Token 14: ( (Type: TOKEN_SEPARATOR, Subtype: OPEN_PAREN, Line: 3)
Token 15: "hello" (Type: TOKEN_LITERAL, Subtype: STRING_LITERAL, Line: 3)
Token 16: ) (Type: TOKEN_SEPARATOR, Subtype: CLOSE_PAREN, Line: 3)
Token 17: ; (Type: TOKEN_SEPARATOR, Subtype: SEMICOLON, Line: 3)
Token 18: } (Type: TOKEN_SEPARATOR, Subtype: CLOSED_BRACES, Line: 4)
Token 19: EOF (Type: TOKEN_EOF, Subtype: EOF_TOKEN, Line: 4)
```
## What I Learned

This was a project to build a core component of a compiler from scratch. It was a deep dive into:

* Finite Automata: Implementing the logic of a state machine to identify different tokens.

* C Programming: Heavy use of file I/O (fopen, fgetc), string manipulation, and memory management.

* Data Structures: Using [List any data structures you used, like enums for tokens, etc.].

* Compiler Theory: Understanding the difference between a lexer, parser, and interprete
