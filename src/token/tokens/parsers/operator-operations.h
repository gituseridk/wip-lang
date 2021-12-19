#include "utils/string/string.h"

ChopToken(operator_operations, token_start, error) {
  if (!stringContainsChar(OPERATIONS, *token_start)) {
    return NULL;
  }
  return token_start + 1;
}
