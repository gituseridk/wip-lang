#include "compile-utils.h"

void addIntToRegX86(char *reg, int value, FILE *out_stream) {
  if (value > 0) {
    L("    add     %s, %d", reg, value);
  } else if(value < 0) {
    L("    sub     %s, %d", reg, -value);
  }
}
