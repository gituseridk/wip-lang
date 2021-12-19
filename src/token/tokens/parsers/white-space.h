#include <ctype.h>
#include "utils/string/string.h"

ChopToken(white_space, token_start, error) {
  if (!isspace(*token_start) && *token_start != 24) {
    return NULL;
  }

  char *token_end = token_start;
  while (isspace(*++token_end));

  return token_end;
}
