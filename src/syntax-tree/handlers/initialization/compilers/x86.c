#include "../data.h"
#include "utils/logger/log-src-error.h"
#include "compiler/x86/compile-utils.h"

void compileInitializationX86(char *src, ExpressionData *self, FILE *out_stream) {
  if (self->result_type.type_id != TYPE_ID_INT) {
    char err[100];
    sprintf(err, "initialization with type %s is not implemented yet\n", getTypeName(&(self->result_type)));
    throwSourceError(src, err, self->token);
  }

  VariableData *var = (VariableData*) self->value;
  fprintf(out_stream, "\t\tmov\t\trax, QWORD PTR [rdp - %d]\n", var->scope_offset);
}
