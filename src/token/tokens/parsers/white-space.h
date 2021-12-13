#include <ctype.h>
#include "utils/string/string.h"

ChopToken(white_space, token_start) {
  if (!isspace(*token_start)) {
    return NULL;
  }

  char *token_end = token_start;
  while (isspace(*++token_end));

  return token_end;
}
