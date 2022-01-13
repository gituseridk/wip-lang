#include <stdlib.h>
#include "./compile-utils.h"

void copyNBytes(char *to_register, unsigned size, FILE *out_stream) {
  if (size != 8) {
    printf("pop with size other then 8 is not implemented yet\n");
    exit(1);
  }
  L("    pop     QWORD [%s]", to_register);
}
