#include "utils/logger/log-src-error.h"
#include "compiler/x86/compile-utils.h"
#include "../data.h"

void compileAssignationX86(char *src, ExpressionData *self, FILE *out_stream) {
  if (
    self->result_type.type_id != TYPE_ID_INT &&
    self->result_type.type_id != TYPE_ID_FUNCTION
  ) {
    char err[100];
    sprintf(err, "assignation is not implemented for %s type", getTypeName(&(self->result_type)));
    throwSourceError(src, err, self->token);
  }

  ExpressionData *left = (ExpressionData*) arrayAt(self->child_expressions, 0);
  ExpressionData *right = (ExpressionData*) arrayAt(self->child_expressions, 1);

  // calc result to rbx
  expressionCompile(right, ARCH_X86, src, out_stream);
  expressionCompile(left, ARCH_X86, src, out_stream);

  L("    pop     rax");
  L("    pop     rbx");

  L("    mov     QWORD [rax], rbx");
}
