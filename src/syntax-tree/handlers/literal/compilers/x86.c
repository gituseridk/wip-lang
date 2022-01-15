#include "../data.h"
#include "utils/logger/log-src-error.h"
#include "compiler/x86/compile-utils.h"

void compileLiteralX86(char *src, ExpressionData *self, bool address, FILE *out_stream) {
  FORBID_ADDRESS_AS_RESULT

  if (self->result_type.type_id != TYPE_ID_INT) {
    char err[100];
    sprintf(err, "literals with type %s is not implemented yet\n", getTypeName(&(self->result_type)));
    throwSourceError(src, err, self->token);
  }

  L("    push    %d", *(int*) self->value);
}
