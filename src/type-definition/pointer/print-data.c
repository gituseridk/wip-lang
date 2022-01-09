#include <stdio.h>
#include <stdlib.h>

#include "./data.h"

void printPointerData(const TypePointerData *data) {
  printf("{\"size\":%d,\"type\":", data->size);
  printTypeDefinition(&(data->type));
  printf("}");
}
