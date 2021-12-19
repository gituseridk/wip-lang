#include <stdlib.h>
#include <stdbool.h>
#include "token/token-data.h"
#include "./syntax-helpers.h"

List *trimTokensLeft(List *start_token) {
  while (start_token != NULL && ((TokenData*)listGetValue(start_token))->token.id == TOKEN_WHITE_SPACE) {
    start_token = listNext(start_token);
  }
  return start_token;
}

List *chopExpressionEnd(List *start_token, char **error) {
  *error = NULL;

  List *token = trimTokensLeft(start_token);
  if (token == NULL) {
    return NULL;
  }
  TokenData *token_data = (TokenData*) listGetValue(token);
  if (token_data->token.id != TOKEN_SEPARATOR_EXPRESSION) {
    *error = "Unexpected token, ';' expected";
    return token;
  }

  return listNext(token);
}

static bool isTrmableHard(TokenData *token) {
  return token != NULL && (
    token->token.id == TOKEN_WHITE_SPACE || token->token.id == TOKEN_SEPARATOR_EXPRESSION
  );
}

List *trimTokensLeftHard(List *start_token) {
  while (start_token != NULL && isTrmableHard(listGetValue(start_token))) {
    start_token = listNext(start_token);
  }
  return start_token;
}
