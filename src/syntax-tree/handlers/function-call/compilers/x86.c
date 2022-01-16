#include "utils/logger/log-src-error.h"
#include "compiler/x86/compile-utils.h"
#include "syntax-tree/handlers/function/data.h"
#include "expression-data/expression-data.h"

#include "../data.h"

void compileFunctionCallX86(char *src, ExpressionData *self, bool address, FILE *out_stream) {
  FORBID_ADDRESS_AS_RESULT

  ExpressionData *target = (ExpressionData*) self->value;

  for (int i = arrayGetLength(self->child_expressions) - 1; i != -1; --i) {
    expressionCompile(arrayAt(self->child_expressions, i), ARCH_X86, src, false, out_stream);
  } 

  if (self->result_type.type_id != TYPE_ID_VOID) {
    unsigned size = getTypeSize(&(self->result_type));
    size = size / TYPE_SIZE_POINTER * TYPE_SIZE_POINTER + (TYPE_SIZE_POINTER - size % TYPE_SIZE_POINTER);
    L("    sub     rsp, %d", size);
  }

  expressionCompile(target, ARCH_X86, src, false, out_stream);

  L("    pop     rax");
  L("    call    rax");

  // !TODO push reslt value to stack
}
