#include "../data.h"
#include "utils/logger/log-src-error.h"
#include "compiler/x86/compile-utils.h"

void compileAssignationX86(char *src, ExpressionData *self, FILE *out_stream) {
  fprintf(out_stream, "\t\tpush\t\trax\n");
  fprintf(out_stream, "\t\tpush\t\trbx\n");
  ExpressionData *left = (ExpressionData*) arrayAt(self->child_expressions, 0);
  ExpressionData *right = (ExpressionData*) arrayAt(self->child_expressions, 1);

  expressionCompile(right, ARCH_X86, src, out_stream); // pushs result to stack
  expressionCompile(left, ARCH_X86, src, out_stream);  // set variable address to rax

  char *size_error = NULL;
  unsigned size = getTypeSize(&(left->result_type), &size_error);
  if (size_error != NULL) {
    throwSourceError(src, size_error, left->token);
  }

  popNBytes("rax", size, out_stream);

  fprintf(out_stream, "\t\tpop\t\trbx\n");
  fprintf(out_stream, "\t\tpop\t\trax\n");
}
