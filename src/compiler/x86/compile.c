#include "compile.h"

static void defineExit(FILE *out_stream) {
  fprintf(out_stream, "\n\nexit:\n");
  fprintf(out_stream, "\t\tmov\t\trbx, rax\n");
  fprintf(out_stream, "\t\tmov\t\trax, 1\n");
  fprintf(out_stream, "\t\tint\t\t80h\n\n");
}

void compileX86(char *src, ExpressionData root_expression, FILE *out_stream) {
  fprintf(out_stream, "section .text\n");
  fprintf(out_stream, "global _start\n\n");
  fprintf(out_stream, "_start:\n");

  expressionCompile(&root_expression, ARCH_X86, src, out_stream);

  defineExit(out_stream);
}
