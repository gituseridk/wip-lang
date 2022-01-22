#include "../data.h"
#include "utils/logger/log-src-error.h"
#include "compiler/x86/compile-utils.h"

void compileReturnX86(char *src, ExpressionData *self, bool address, FILE *out_stream) {
  FORBID_ADDRESS_AS_RESULT

  ExpressionData *result = (ExpressionData*) arrayAt(self->child_expressions, 0);

  switch (result->result_type.type_id)
  {
  case TYPE_ID_INT:
  case TYPE_ID_POINTER: {
    expressionCompile(
      result,
      ARCH_X86,
      src,
      false,
      out_stream
    );

    L("    pop     rax");

    ReturnExpressionData *return_data = (ReturnExpressionData*) self->value;
    unsigned fucntion_scope_level = return_data->scope_level;
    while (fucntion_scope_level--) {
      L("    mov     rbp, QWORD [rbp]");
    }

    L("    mov     QWORD [rbp + 16], rax");

    L("    mov     rsp, rbp");
    L("    pop     rbp");
    L("    ret");
    break;
  }
  case TYPE_ID_FUNCTION: {
    char err[100];
    sprintf(err, "closure is not supported yet\n");
    throwSourceError(src, err, result->token);
    break;
  }
  default: {
    char err[100];
    sprintf(err, "return for type %s is not implemented yet\n", getTypeName(&(result->result_type)));
    throwSourceError(src, err, result->token);
  }
  }

}
