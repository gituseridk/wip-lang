#ifndef TOKEN_H
#define TOKEN_H

typedef struct {
  int id;
  char *name;
  int (*checkTokenStr)(const char *token, int token_size);
} Token;

#endif
