#ifndef TOKENS_H
#define TOKENS_H

#include <stdbool.h>

#include "utils/array/array.h"
#include "./token.h"
#include "./token-data.h"

#define TOKEN_CHECK_RESULT_INVALID 0
#define TOKEN_CHECK_RESULT_VALID 1
#define TOKEN_CHECK_RESULT_ENDED 2

Array *getTokens();

#endif
