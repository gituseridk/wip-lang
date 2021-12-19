#include "utils/string/string.h"

ChopToken(operator_assignation, token_start, error) {
  if (*token_start != '=') {
    return NULL;
  }
  return token_start + 1;
}
