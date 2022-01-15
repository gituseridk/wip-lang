#include "../data.h"
#include "utils/logger/log-src-error.h"
#include "compiler/x86/compile-utils.h"

static void compileIncDec(
  char *src,
  ExpressionData *self,
  ExpressionData *target,
  bool dec,
  FILE *out_stream
) {
  char err[100];
  switch (self->result_type.type_id) {
  case TYPE_ID_INT:
    expressionCompile(target, ARCH_X86, src, true, out_stream);

    L("    pop     rax");
    L("    push    QWORD [rax]");
    L("    %s     QWORD [rax]", dec ? "dec" : "inc");

    return;
  default:
    sprintf(
      err,
      "%s for %s type is not implemented yet",
      dec ? "dec" : "inc",
      getTypeName(&(self->result_type))
    );
    throwSourceError(src, err, self->token);
  }
}

void compileOperationPostfixX86(char *src, ExpressionData *self, bool address, FILE *out_stream) {
  FORBID_ADDRESS_AS_RESULT

  ExpressionData *target = (ExpressionData*) arrayAt(self->child_expressions, 0);

  switch (self->id - EXPRESSION_OPERATIONS_POSTFIX) {
  case OPERATION_POSTFIX_ID_INC:
    compileIncDec(src, self, target, false, out_stream);
    return;
  case OPERATION_POSTFIX_ID_DEC:
    compileIncDec(src, self, target, true, out_stream);
    return;
  
  default:
    throwSourceError(src, "this expression is not supported yet", self->token);
  }
}
