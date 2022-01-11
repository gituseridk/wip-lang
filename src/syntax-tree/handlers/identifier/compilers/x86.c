#include "../data.h"
#include "utils/logger/log-src-error.h"
#include "compiler/x86/compile-utils.h"

void compileIdentifierX86(char *src, ExpressionData *self, FILE *out_stream) {
  if (self->result_type.type_id != TYPE_ID_INT) {
    char err[100];
    sprintf(err, "variables with type %s is not implemented yet\n", getTypeName(&(self->result_type)));
    throwSourceError(src, err, self->token);
  }

  VariableData *var = (VariableData*) self->value;
  // !TODO implement closures
  if (var->scope != self->parent_scope) {
    throwSourceError(src, "can not use variables from upper scope\n", self->token);
  }

  fprintf(out_stream, "\t\tmov\t\trax, QWORD [rbp - %d]\n", var->scope_offset);
}
