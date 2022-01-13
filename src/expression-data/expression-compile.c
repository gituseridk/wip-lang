#include <stdio.h>
#include <stdlib.h>

#include "token/token-data.h"
#include "utils/logger/log-src-error.h"
#include "compiler/x86/compile-utils.h"
#include "./expression-data.h"

void expressionCompile(ExpressionData *self, Architecture arch, char *src, FILE *out_stream) {
  if (arch != ARCH_X86) {
    printf("only x86 arch is supported\n");
    exit(1);
  }

  if (self->compileX86 == NULL) {
    printf("\n");
    char err[100];
    sprintf(err, "expression \"%s\" (id %d) is not implemmented for x86 arch\n", self->name, self->id);
    throwSourceError(src, err, self->token);
  }

  TokenData *token = (TokenData*) listGetValue(self->token);
  L("; expression \"%s\" (id: %d) at %d:%d (", self->name, self->id, token->row, token->col);

  self->compileX86(src, self, out_stream);

  L("; )");
}
