#ifndef TOKENS_H
#define TOKENS_H

#include <stdbool.h>

#include "utils/array/array.h"
#include "./token-data.h"

typedef struct {
  int id;
  bool (*testString)(const char *token);
} Token;

Array *getTokens();

#endif
