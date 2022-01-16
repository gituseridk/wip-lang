#include "../data.h"
#include "utils/logger/log-src-error.h"
#include "compiler/x86/compile-utils.h"

void compileInitializationX86(char *src, ExpressionData *self, bool address, FILE *out_stream) {
  if (!address) {
    return;
  }

  if (
    self->result_type.type_id != TYPE_ID_INT &&
    self->result_type.type_id != TYPE_ID_POINTER &&
    self->result_type.type_id != TYPE_ID_FUNCTION
  ) {
    char err[100];
    sprintf(err, "initialization with type %s is not implemented yet\n", getTypeName(&(self->result_type)));
    throwSourceError(src, err, self->token);
  }

  VariableData *var = (VariableData*) self->value;

  L("    mov     rax, rbp");
  addIntToRegX86("rax", -var->scope_offset, out_stream);
  L("    push    rax");
}
