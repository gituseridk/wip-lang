#ifndef TOKEN_H
#define TOKEN_H

#include "utils/array/array.h"

typedef struct {
  int id;
  char *value;

  int row;
  int col;
  int size;
} TokenData;

Array* tokenize(char *src);

#endif
