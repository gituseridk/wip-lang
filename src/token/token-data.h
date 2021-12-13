#ifndef TOKEN_DATA_H
#define TOKEN_DATA_H

#include "utils/array/array.h"
#include "./token.h"

typedef struct {
  Token token;
  char *value;

  int row;
  int col;
  int size;
} TokenData;

Array* tokenize(char *src);

#endif
