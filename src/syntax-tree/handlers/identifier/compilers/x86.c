#include "../data.h"
#include "utils/logger/log-src-error.h"
#include "compiler/x86/compile-utils.h"

void compileIdentifierX86(char *src, ExpressionData *self, FILE *out_stream) {
  if (
    self->result_type.type_id != TYPE_ID_INT &&
    self->result_type.type_id != TYPE_ID_FUNCTION
  ) {
    char err[100];
    sprintf(err, "variables with type %s is not implemented yet\n", getTypeName(&(self->result_type)));
    throwSourceError(src, err, self->token);
  }

  ExpressionIdentifierValue *identifier = (ExpressionIdentifierValue*) self->value;

  L("    mov     rax, rbp");
  for (unsigned i = 0; i != identifier->scope_diff; ++i) {
    L("    mov     rax, [rax]");
  }

  int offset = identifier->var->scope_offset;
  if (offset < 0) {
    L("    push    QWORD [rax + %d]", -offset);
  } else {
    L("    push    QWORD [rax - %d]", offset);
  }
}
