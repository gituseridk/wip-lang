#ifndef TOKENS_H
#define TOKENS_H

#include <stdbool.h>

#include "utils/array/array.h"
#include "./token-data.h"

#define TOKEN_CHECK_RESULT_INVALID 0
#define TOKEN_CHECK_RESULT_VALID 1
#define TOKEN_CHECK_RESULT_ENDED 2

typedef struct {
  int id;
  char *name;
  int (*checkTokenStr)(const char *token, int token_size);
} Token;

Array *getTokens();

#endif
