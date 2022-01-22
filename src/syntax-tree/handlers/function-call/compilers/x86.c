#include "utils/logger/log-src-error.h"
#include "compiler/x86/compile-utils.h"
#include "syntax-tree/handlers/function/data.h"
#include "expression-data/expression-data.h"

#include "../data.h"

// !TODO handle return to not scope functions

void compileFunctionCallX86(char *src, ExpressionData *self, bool address, FILE *out_stream) {
  FORBID_ADDRESS_AS_RESULT

  ExpressionData *target = (ExpressionData*) self->value;

  L("    push    rbp");

  unsigned args_size = 0;

  for (int i = arrayGetLength(self->child_expressions) - 1; i != -1; --i) {
    ExpressionData *arg = (ExpressionData*) arrayAt(self->child_expressions, i);
    expressionCompile(arg, ARCH_X86, src, false, out_stream);
    args_size += getTypeSize(&(arg->result_type));
  }

  if (self->result_type.type_id != TYPE_ID_VOID) {
    unsigned size = getTypeSize(&(self->result_type));
    if (size % TYPE_SIZE_POINTER) {
      size += TYPE_SIZE_POINTER - size % TYPE_SIZE_POINTER;
    }
    L("    sub     rsp, %d", size);
  }

  expressionCompile(target, ARCH_X86, src, false, out_stream);

  L("    pop     rax");
  L("    pop     rbx");

  L("    mov     rbp, rbx");

  L("    call    rax");

  switch (self->result_type.type_id)
  {
  case TYPE_ID_VOID:
    L("    add     rsp, %d", args_size);
    L("    pop     rbp");
    break;

  case TYPE_ID_INT:
  case TYPE_ID_POINTER:
    L("    pop     rax");
    L("    add     rsp, %d", args_size);
    L("    pop     rbp");
    L("    push    rax");
    break;
  
  default: {
    char err[100];
    sprintf(err, "function call with result type \"%s\" is not implemented yet", getTypeName(&(self->result_type)));
    throwSourceError(src, err, self->token);
    break;
  }
  }
}
