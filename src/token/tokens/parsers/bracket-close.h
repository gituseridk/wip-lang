#include "utils/string/string.h"

ChopToken(bracket_close, token_start, error) {
  if (!stringContainsChar(CLOSE_BRACKETS, *token_start)) {
    return NULL;
  }
  return token_start + 1;
}
