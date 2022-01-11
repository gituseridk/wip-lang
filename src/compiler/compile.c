#include <stdlib.h>

#include "./compiler.h"
#include "./x86/compile.h"

void compile(char *src, Architecture arch, ExpressionData root_expression, FILE *out_stream) {
  if (arch != ARCH_X86) {
    printf("only x86 arch is supported\n");
    exit(1);
  }

  compileX86(src, root_expression, out_stream);
}
