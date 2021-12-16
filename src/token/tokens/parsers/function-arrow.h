#include <stdio.h>
#include "utils/string/string.h"

ChopToken(function_arrow, token_start, error) {
  if (strncmp(token_start, "=>", 2) != 0) {
    return NULL;
  }
  return token_start + 2;
}
