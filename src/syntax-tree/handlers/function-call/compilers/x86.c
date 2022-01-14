#include "utils/logger/log-src-error.h"
#include "compiler/x86/compile-utils.h"
#include "syntax-tree/handlers/function/data.h"
#include "expression-data/expression-data.h"

#include "../data.h"

void compileFunctionCallX86(char *src, ExpressionData *self, FILE *out_stream) {
  for (int i = 0; i != arrayGetLength(self->child_expressions); ++i) {
    expressionCompile(arrayAt(self->child_expressions, i), ARCH_X86, src, out_stream);
  }

  VariableData *function_var = (VariableData*) self->value;

  L("    mov     rax, rbp");
  addIntToRegX86("rax", -function_var->scope_offset, out_stream);
  L("    call    [rax]");

  // !TODO push reslt value to stack
}
