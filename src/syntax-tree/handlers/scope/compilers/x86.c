#include "utils/logger/log-src-error.h"
#include "compiler/x86/compile-utils.h"
#include "syntax-tree/handlers/function/data.h"
#include "../data.h"

void compileScopeX86(char *src, ExpressionData *self, bool address, FILE *out_stream) {
  FORBID_ADDRESS_AS_RESULT

  unsigned size = expressionGetSize(self);

  if (self->scope_label == NULL) {
    throwSourceError(src, "internal error: scope_label is not set", self->token);
  }

  L("\n%s:", self->scope_label);
  L("    push    rbp");
  L("    mov     rbp, rsp");
  L("    sub     rsp, %d", size);

  for (MapItterator *i = mapBegin(self->variables); !mapItteratorIsEnded(i); mapItteratorNext(i)) {
    VariableData *var = (VariableData*) mapItteratorGet(i).value;
    if (var->type.type_id == TYPE_ID_FUNCTION) {
      FunctionTypeData *func_data = (FunctionTypeData*) var->type.data;
      L("    mov     rax, rbp");
      addIntToRegX86("rax", -var->scope_offset, out_stream);
      L("    mov     QWORD [rax], %s", func_data->label);
    }
  }

  for (int i = 0; i != arrayGetLength(self->child_expressions); ++i) {
    ExpressionData *child_expression = arrayAt(self->child_expressions, i);
    expressionCompile(child_expression, ARCH_X86, src, false, out_stream);
  }

  L("    mov     rsp, rbp");
  L("    pop     rbp");
}
