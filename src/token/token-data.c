#include <stdio.h>
#include "./token-data.h"

void tokenDataPrint(TokenData *self) {
  printf(
    "{ name: '%s', id: %d, value: '%s', row: %d, col: %d }\n",
    self->token.name,
    self->token.id,
    self->value,
    self->row,
    self->col
  );
}
