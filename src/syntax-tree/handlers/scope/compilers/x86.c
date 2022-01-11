#include "../data.h"
#include "utils/logger/log-src-error.h"

void compileScopeX86(char *src, ExpressionData *self, FILE *out_stream) {
  unsigned size = expressionGetSize(self);

  fprintf(out_stream, "push    rbp\n");
  fprintf(out_stream, "mov     rbp, rsp\n");
  fprintf(out_stream, "sub     rsp, %d\n", size);

  for (int i = 0; i != arrayGetLength(self->child_expressions); ++i) {
    ExpressionData *child_expression = arrayAt(self->child_expressions, i);
    expressionCompile(child_expression, ARCH_X86, src, out_stream);
  }

  fprintf(out_stream, "add     rsp, %d\n", size);
  fprintf(out_stream, "pop     rbp\n");
}
