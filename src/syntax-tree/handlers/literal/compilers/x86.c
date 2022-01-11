#include "../data.h"
#include "utils/logger/log-src-error.h"
#include "compiler/x86/compile-utils.h"

void compileLiteralX86(char *src, ExpressionData *self, FILE *out_stream) {
  if (self->result_type.type_id != TYPE_ID_INT) {
    char err[100];
    sprintf(err, "literals with type %s is not implemented yet\n", getTypeName(&(self->result_type)));
    throwSourceError(src, err, self->token);
  }

  fprintf(out_stream, "\t\tmov\t\trax, %d\n", *(int*) self->value);
}
