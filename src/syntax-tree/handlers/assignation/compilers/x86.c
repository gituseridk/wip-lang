#include "utils/logger/log-src-error.h"
#include "compiler/x86/compile-utils.h"
#include "../data.h"

void compileAssignationX86(char *src, ExpressionData *self, bool address, FILE *out_stream) {
  FORBID_ADDRESS_AS_RESULT

  ExpressionData *left = (ExpressionData*) arrayAt(self->child_expressions, 0);
  ExpressionData *right = (ExpressionData*) arrayAt(self->child_expressions, 1);

  // calc result to rbx
  expressionCompile(right, ARCH_X86, src, false, out_stream);
  expressionCompile(left, ARCH_X86, src, true, out_stream);

  switch (self->result_type.type_id)
  {
  case TYPE_ID_INT:
  case TYPE_ID_POINTER:
  case TYPE_ID_VOID:{
    L("    pop     rax");
    L("    pop     rbx");

    L("    mov     QWORD [rax], rbx");
    break;
  }
  case TYPE_ID_FUNCTION: {
    L("    pop    rax");
    L("    pop    rbx");
    L("    pop    rcx");

    L("    mov    QWORD [rax], rcx");
    L("    mov    QWORD [rax - %d], rbx", TYPE_SIZE_POINTER);

    break;
  }
  default: {
    char err[100];
    sprintf(err, "assignation is not implemented for %s type", getTypeName(&(self->result_type)));
    throwSourceError(src, err, self->token);
  }
  }
}
