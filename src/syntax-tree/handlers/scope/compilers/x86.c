#include "utils/logger/log-src-error.h"
#include "compiler/x86/compile-utils.h"
#include "../data.h"

void compileScopeX86(char *src, ExpressionData *self, FILE *out_stream) {
  unsigned size = expressionGetSize(self);

  if (self->scope_label == NULL) {
    throwSourceError(src, "internal error: scope_label is not set", self->token);
  }

  L("\n%s:", self->scope_label);
  L("    push    rbp");
  L("    mov     rbp, rsp");
  L("    sub     rsp, %d", size);

  for (int i = 0; i != arrayGetLength(self->child_expressions); ++i) {
    ExpressionData *child_expression = arrayAt(self->child_expressions, i);
    expressionCompile(child_expression, ARCH_X86, src, out_stream);
  }

  L("    add     rsp, %d", size);
  L("    pop     rbp");
}
