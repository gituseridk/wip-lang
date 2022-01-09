#include <stdio.h>
#include "./type-defenition.h"

void printTypeDefinition(const TypeDefinition *type) {
  printf("{\"type_name\":\"%s\"}", getTypeName(type));
}
