#include <stdlib.h>
#include "token/token-data.h"
#include "./syntax-helpers.h"

List *trimTokensLeft(List *start_token) {
  while (start_token != NULL && ((TokenData*)listGetValue(start_token))->token.id == TOKEN_WHITE_SPACE) {
    start_token = listNext(start_token);
  }
  return start_token;
}
