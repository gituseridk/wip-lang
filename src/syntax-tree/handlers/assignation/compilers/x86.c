#include "../data.h"
#include "utils/logger/log-src-error.h"

void compileAssignationX86(char *src, ExpressionData *self, FILE *out_stream) {
  if (self->result_type.type_id != TYPE_ID_INT) {
    char err[100];
    sprintf(err, "assignation is not implemented for %s type", getTypeName(&(self->result_type)));
    throwSourceError(src, err, self->token);
  }

  fprintf(out_stream, "\t\tpush\t\trax\n");
  fprintf(out_stream, "\t\tpush\t\trbx\n");
  ExpressionData *left = (ExpressionData*) arrayAt(self->child_expressions, 0);
  ExpressionData *right = (ExpressionData*) arrayAt(self->child_expressions, 1);

  // calc result to rbx
  expressionCompile(right, ARCH_X86, src, out_stream);
  fprintf(out_stream, "\t\tmov\t\trbx, rax\n");

  // set variable address to rax
  expressionCompile(left, ARCH_X86, src, out_stream);

  fprintf(out_stream, "\t\tmov\t\tQWORD [rax], rbx\n");

  fprintf(out_stream, "\t\tpop\t\trbx\n");
  fprintf(out_stream, "\t\tpop\t\trax\n");
}
