#include "../data.h"
#include "utils/logger/log-src-error.h"
#include "compiler/x86/compile-utils.h"

static void compileSum(char *src, ExpressionData *self, ExpressionData *left, ExpressionData *right, FILE *out_stream) {
  char err[100];
  switch (self->result_type.type_id) {
  case TYPE_ID_INT:
    expressionCompile(left, ARCH_X86, src, out_stream);
    expressionCompile(right, ARCH_X86, src, out_stream);

    L("    pop     rax");
    L("    pop     rbx");
    L("    add     rax, rbx");
    L("    push    rax");

    return;
  default:
    sprintf(err, "sum for %s type is not implemented yet", getTypeName(&(self->result_type)));
    throwSourceError(src, err, self->token);
  }
}

void compileOperationLRX86(char *src, ExpressionData *self, FILE *out_stream) {
  ExpressionData *left = (ExpressionData*) arrayAt(self->child_expressions, 0);
  ExpressionData *right = (ExpressionData*) arrayAt(self->child_expressions, 1);

  switch (self->id - EXPRESSION_OPERATIONS) {
  case OPERATION_ID_SUM:
    compileSum(src, self, left, right, out_stream);
    return;
  
  default:
    throwSourceError(src, "this expression is not supported yet", self->token);
  }
}
