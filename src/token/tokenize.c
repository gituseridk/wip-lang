#include <stdio.h>
#include <stdlib.h>
#include "utils/string/string.h"
#include "./token-data.h"
#include "./tokens.h"

typedef struct {
  const char *token_str;
  int size;
} TokenCheckProps;

typedef struct {
  int id;
  int result;
} TokenCheckResult;

static void checkToken(void *_self, void *result, const void *_token, int index, const Array *array) {
  TokenCheckProps *self = (TokenCheckProps*) _self;
  Token *token = (Token*)_token;
  ((TokenCheckResult*)result)->result = token->checkTokenStr(self->token_str, self->size);
  ((TokenCheckResult*)result)->id = token->id;

  // printf("[%s]: %d\n", token->name, ((TokenCheckResult*)result)->result);
}

static bool isTokenValid(void *self, const void *token_check_result, int index, const Array *array) {
  return ((TokenCheckResult*)token_check_result)->result == TOKEN_CHECK_RESULT_VALID;
}

static bool isTokenEnded(void *self, const void *token_check_result, int index, const Array *array) {
  return ((TokenCheckResult*)token_check_result)->result == TOKEN_CHECK_RESULT_ENDED;
}

static void getTokenByCheckResult(
  void *_self,
  void *result,
  const void *_token_check_result,
  int index,
  const Array *array
) {
  TokenCheckResult *token_check_result = (TokenCheckResult*) _token_check_result;
  *(Token*) result = *(Token*) arrayGetElementAt(getTokens(), token_check_result->id);
}

Array* tokenize(char *src) {
  Array *result = createEmptyArray(1, sizeof(TokenData));

  int iterations_limit = 100;

  char *token_start = src;
  char *token_end = src;

  int start_col = 1;
  int start_row = 1;

  int col = 0;
  int row = 1;

  // !TODO free last_tokens after reassigning
  Array *last_tokens = getTokens();

  while (*token_end != '\0') {
    if (--iterations_limit == 0) {
      break;
    }

    ++col;
    if (*token_end == '\n') {
      ++row;
      col = 1;
    }
    int token_size = token_end - token_start + 1;
    char *token_str = stringGetSubstring(token_start, 0, token_size - 1);
    // printf("%d token: '%s'\n", iterations_limit, token_str);

    TokenCheckProps props = (TokenCheckProps) {
      .token_str = token_str,
      .size = token_size,
    };
    Array *token_checks = arrayMap(last_tokens, sizeof(TokenCheckResult), checkToken, &props);

    Array *valid_tokens_results = arrayFilter(token_checks, isTokenValid, NULL);
    Array *valid_tokens = arrayMap(valid_tokens_results, sizeof(Token), getTokenByCheckResult, NULL);
    arrayFree(valid_tokens_results);
    Array *ended_tokens_results = arrayFilter(token_checks, isTokenEnded, NULL);
    Array *ended_tokens = arrayMap(ended_tokens_results, sizeof(Token), getTokenByCheckResult, NULL);
    arrayFree(ended_tokens_results);

    arrayFree(token_checks);

    if (arrayGetLength(valid_tokens) == 0 && arrayGetLength(ended_tokens) == 0) {
      printf("Unexpected token '%*.*s' at %d:%d\n", token_size, token_size, token_start, start_row, start_col);
      arrayFree(result);
      arrayFree(valid_tokens);
      arrayFree(ended_tokens);
      free(token_str);
      return NULL;
    }

    if (arrayGetLength(ended_tokens) != 0) {
      Token token = *(Token*) arrayGetElementAt(ended_tokens, 0);
      token_str[token_size - 1] = '\0';
      TokenData data = (TokenData) {
        .id = token.id,
        .value = token_str,
        .col = start_col,
        .row = start_row,
        .size = token_size - 1,
      };
      printf("Token '%s' (size: %d) parsed at %d:%d\n", token_str, data.size, data.row, data.col);
      start_row = row;
      start_col = col;
      token_start = token_end;
      arrayPush(result, &data);
      arrayFree(valid_tokens);
      arrayFree(ended_tokens);
      last_tokens = getTokens();
      continue;
    }

    last_tokens = valid_tokens;
    ++token_end;

    arrayFree(ended_tokens);
    free(token_str);
  }

  return result;
}
