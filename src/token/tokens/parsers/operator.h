#include "utils/string/string.h"

ChopToken(operator, token_start) {
  if (!stringContainsChar(OPERATORS, *token_start)) {
    return NULL;
  }
  return token_start + 1;
}
