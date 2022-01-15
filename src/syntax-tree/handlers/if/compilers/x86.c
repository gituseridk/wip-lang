#include "../data.h"
#include "utils/logger/log-src-error.h"
#include "compiler/x86/compile-utils.h"

int ifs_counter = 0;

void compileIfX86(char *src, ExpressionData *self, FILE *out_stream) {
  ExpressionData *condition = (ExpressionData*) arrayAt(self->child_expressions, 0);

  ExpressionData *body = (ExpressionData*) arrayAt(self->child_expressions, 1);

  expressionCompile(condition, ARCH_X86, src, out_stream);

  L("    pop     rax");
  L("    cmp     rax, 0");
  L("    jz      if_end_%d", ifs_counter);

  expressionCompile(body, ARCH_X86, src, out_stream);
  
  L("if_end_%d:\n", ifs_counter++);
}
