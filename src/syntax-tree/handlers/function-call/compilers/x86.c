#include "../data.h"
#include "utils/logger/log-src-error.h"

void compileFunctionCallX86(char *src, ExpressionData *self, FILE *out_stream) {
  throwSourceError(src, "function calls is not implemented yet", self->token);
}
