#include "../data.h"
#include "utils/logger/log-src-error.h"
#include "compiler/x86/compile-utils.h"

static void compileIncDec(
  ExpressionData *self,
  ExpressionData *target,
  bool dec,
  bool address,
  FILE *out_stream
) {
  char err[100];
  switch (self->result_type.type_id) {
  case TYPE_ID_INT:
    expressionCompile(target, ARCH_X86, true, out_stream);

    L("    pop     rax");
    if (address) {
      L("    push    rax");
    } else {
      L("    push    QWORD [rax]");
    }
    L("    %s     QWORD [rax]", dec ? "dec" : "inc");

    return;
  default:
    sprintf(
      err,
      "%s for %s type is not implemented yet",
      dec ? "dec" : "inc",
      getTypeName(&(self->result_type))
    );
    throwSourceError(err, self->token);
  }
}

void compileOperationPostfixX86(ExpressionData *self, bool address, FILE *out_stream) {
  ExpressionData *target = (ExpressionData*) arrayAt(self->child_expressions, 0);

  switch (self->id - EXPRESSION_OPERATIONS_POSTFIX) {
  case OPERATION_POSTFIX_ID_INC:
    compileIncDec(self, target, false, address, out_stream);
    return;
  case OPERATION_POSTFIX_ID_DEC:
    compileIncDec(self, target, true, address, out_stream);
    return;
  
  default:
    throwSourceError("this postfix expression is not supported yet", self->token);
  }
}
