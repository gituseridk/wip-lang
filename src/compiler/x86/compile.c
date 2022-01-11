#include "compile.h"

void compileX86(char *src, ExpressionData root_expression, FILE *out_stream) {
  fprintf(out_stream,
    "section .text\n"
    "global _start\n\n"
    "_start:\n"
  );

  expressionCompile(&root_expression, ARCH_X86, src, out_stream);
}
