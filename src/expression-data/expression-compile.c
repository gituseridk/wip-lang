#include <stdio.h>
#include <stdlib.h>

#include "utils/logger/log-src-error.h"
#include "./expression-data.h"

void expressionCompile(ExpressionData *self, Architecture arch, char *src, FILE *out_stream) {
  if (arch != ARCH_X86) {
    printf("only x86 arch is supported\n");
    exit(1);
  }

  if (self->compileX86 == NULL) {
    printf("\n");
    char err[100];
    sprintf(err, "expression with id %d is not implemmented for x86 arch\n", self->id);
    throwSourceError(src, err, self->token);
  }
  self->compileX86(src, self, out_stream);
}
