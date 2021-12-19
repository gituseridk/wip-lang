#ifndef TOKEN_H
#define TOKEN_H

#define TOKEN_LITERAL_STRING 0
#define TOKEN_LITERAL_FLOAT 1
#define TOKEN_LITERAL_INT 2
#define TOKEN_FUNCTION_ARROW 3
#define TOKEN_BRACKET_OPEN 4
#define TOKEN_BRACKET_CLOSE 5
#define TOKEN_KEYWORD 6
#define TOKEN_IDENTIFIER 7
#define TOKEN_SEPARATOR_EXPRESSION 8
#define TOKEN_WHITE_SPACE 9
#define TOKEN_SEPARATOR 10
#define TOKEN_OPERATOR 11
#define TOKEN_COMMENT 12

typedef struct {
  int id;
  char *name;
  char* (*chopToken)(char *token_start, char **error);
} Token;

#endif
