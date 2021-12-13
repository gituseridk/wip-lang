#ifndef TOKEN_H
#define TOKEN_H

typedef struct {
  int id;
  char *name;
  char* (*chopToken)(char *token_start, char **error);
} Token;

#endif
