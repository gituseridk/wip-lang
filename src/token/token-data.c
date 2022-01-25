#include <stdio.h>
#include "./token-data.h"

void tokenDataPrint(TokenData *self) {
  printf(
    "{ name: '%s', id: %d, value: '%s', path: \"%s:%d:%d\" }\n",
    self->token.name,
    self->token.id,
    self->value,
    self->src->path,
    self->row,
    self->col
  );
}
