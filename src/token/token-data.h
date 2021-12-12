#ifndef TOKEN_H
#define TOKEN_H

#include "utils/array/array.h"

typedef struct {
  int id;
  char *value;

  // ?? maybe the wrong place
  unsigned row;
  unsigned col;
} TokenData;

Array* tokenize(char *src);

#endif
