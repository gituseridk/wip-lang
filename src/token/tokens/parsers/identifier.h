#include <stdio.h>

CheckIf(identifier, token, size) {
  if ((token[size-1] < 65 || token[size-1] > 90) && (token[size-1] < 97 || token[size-1] > 122)) {
    return false;
  }
  return true;
}
