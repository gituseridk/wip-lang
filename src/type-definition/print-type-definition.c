#include <stdio.h>
#include "./type-definition.h"
#include "./pointer/data.h"

void printTypeDefinition(const TypeDefinition *type) {
  printf("{\"type_name\":\"%s\"", getTypeName(type));
  if (type->type_id == TYPE_ID_POINTER) {
    printf(",\"pointer_data\":");
    printPointerData(type->data);
  }
  printf("}");
}
