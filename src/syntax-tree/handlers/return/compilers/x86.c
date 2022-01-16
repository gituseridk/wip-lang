#include "../data.h"
#include "utils/logger/log-src-error.h"
#include "compiler/x86/compile-utils.h"

void compileReturnX86(char *src, ExpressionData *self, bool address, FILE *out_stream) {
  FORBID_ADDRESS_AS_RESULT

  ExpressionData *result = (ExpressionData*) arrayAt(self->child_expressions, 0);

  if (
    result->result_type.type_id != TYPE_ID_INT &&
    result->result_type.type_id != TYPE_ID_POINTER &&
    result->result_type.type_id != TYPE_ID_FUNCTION
  ) {
    char err[100];
    sprintf(err, "return for type %s is not implemented yet\n", getTypeName(&(result->result_type)));
    throwSourceError(src, err, result->token);
  }

  expressionCompile(
    result,
    ARCH_X86,
    src,
    false,
    out_stream
  );

  L("    pop     rax");

  L("    mov     rbx, QWORD [rbp]");
  L("    mov     QWORD [rbx + 16], rax");
}
