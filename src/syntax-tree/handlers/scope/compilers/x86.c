#include "../data.h"
#include "utils/logger/log-src-error.h"

void compileScopeX86(char *src, ExpressionData *self, FILE *out_stream) {
  unsigned size = expressionGetSize(self);

  fprintf(out_stream, "\t\tpush\t\trbp\n");
  fprintf(out_stream, "\t\tmov\t\trbp, rsp\n");
  fprintf(out_stream, "\t\tsub\t\trsp, %d\n", size);

  for (int i = 0; i != arrayGetLength(self->child_expressions); ++i) {
    ExpressionData *child_expression = arrayAt(self->child_expressions, i);
    expressionCompile(child_expression, ARCH_X86, src, out_stream);
  }

  fprintf(out_stream, "\t\tadd\t\trsp, %d\n", size);
  fprintf(out_stream, "\t\tpop\t\trbp\n");
}
