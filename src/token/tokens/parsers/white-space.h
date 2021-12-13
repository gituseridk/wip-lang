#include <ctype.h>

CheckIf(white_space, token, size) {
  if (isspace(token[size - 1])) {
    return TOKEN_CHECK_RESULT_VALID;
  }
  if (size > 1 && isspace(token[size - 2])) {
    return TOKEN_CHECK_RESULT_ENDED;
  }
  return TOKEN_CHECK_RESULT_INVALID;
}
