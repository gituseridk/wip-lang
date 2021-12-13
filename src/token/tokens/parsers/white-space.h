#include <ctype.h>

CheckIf(white_space, token, size) {
  if (!isspace(token[size-1])) {
    return false;
  }
  return true;
}
