#include "utils/string/string.h"

ChopToken(bracket_open, token_start, error) {
  if (!stringContainsChar(OPEN_BRACKETS, *token_start)) {
    return NULL;
  }
  return token_start + 1;
}
