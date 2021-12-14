#ifndef TOKEN_DATA_H
#define TOKEN_DATA_H

#include "utils/list/list.h"

#include "./token.h"

typedef struct {
  Token token;
  char *value;

  int row;
  int col;
  int size;
} TokenData;

List* tokenize(char *src);

#endif
