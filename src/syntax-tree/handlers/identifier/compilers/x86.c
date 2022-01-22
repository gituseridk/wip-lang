#include "../data.h"
#include "utils/logger/log-src-error.h"
#include "compiler/x86/compile-utils.h"

void compileIdentifierX86(char *src, ExpressionData *self, bool address, FILE *out_stream) {
  ExpressionIdentifierValue *identifier = (ExpressionIdentifierValue*) self->value;

  L("    mov     rax, rbp");
  for (unsigned i = 0; i != identifier->scope_diff; ++i) {
    L("    mov     rax, [rax]");
  }

  if (address) {
    int offset = identifier->var->scope_offset;
    addIntToRegX86("rax", -offset, out_stream);
    L("    push    rax");
    return;
  }
  int offset = identifier->var->scope_offset;

  switch (self->result_type.type_id)
  {
  case TYPE_ID_INT:
  case TYPE_ID_POINTER: {
    if (offset < 0) {
      L("    push    QWORD [rax + %d]", -offset);
    } else {
      L("    push    QWORD [rax - %d]", offset);
    }

    break;
  }
  case TYPE_ID_FUNCTION: {
    if (offset < 0) {
      L("    push    QWORD [rax + %d]", -offset + TYPE_SIZE_POINTER);
      L("    push    QWORD [rax + %d]", -offset);
    } else {
      L("    push    QWORD [rax - %d]", offset);
      L("    push    QWORD [rax - %d]", offset + TYPE_SIZE_POINTER);
    }

    break;
  }
  
  default: {
    char err[100];
    sprintf(err, "variables with type %s is not implemented yet\n", getTypeName(&(self->result_type)));
    throwSourceError(src, err, self->token);
  }
  }
}
