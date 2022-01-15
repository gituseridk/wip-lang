#include "../data.h"
#include "utils/logger/log-src-error.h"
#include "compiler/x86/compile-utils.h"

static void compileSum(
  char *src,
  ExpressionData *self,
  ExpressionData *left,
  ExpressionData *right,
  bool difference,
  FILE *out_stream
) {
  char err[100];
  switch (self->result_type.type_id) {
  case TYPE_ID_INT:
    expressionCompile(left, ARCH_X86, src, false, out_stream);
    expressionCompile(right, ARCH_X86, src, false, out_stream);

    L("    pop     rbx");
    L("    pop     rax");
    L("    %s     rax, rbx", difference ? "sub" : "add");
    L("    push    rax");

    return;
  default:
    sprintf(
      err,
      "%s for %s type is not implemented yet",
      difference ? "diff" : "sum",
      getTypeName(&(self->result_type))
    );
    throwSourceError(src, err, self->token);
  }
}

void compileOperationLRX86(char *src, ExpressionData *self, bool address, FILE *out_stream) {
  FORBID_ADDRESS_AS_RESULT

  ExpressionData *left = (ExpressionData*) arrayAt(self->child_expressions, 0);
  ExpressionData *right = (ExpressionData*) arrayAt(self->child_expressions, 1);

  switch (self->id - EXPRESSION_OPERATIONS) {
  case OPERATION_ID_SUM:
    compileSum(src, self, left, right, false, out_stream);
    return;
  case OPERATION_ID_DIFFERENCE:
    compileSum(src, self, left, right, true, out_stream);
    return;
  
  default:
    throwSourceError(src, "this expression is not supported yet", self->token);
  }
}
