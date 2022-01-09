#include <stdlib.h>

#include "./type-definition.h"

void setVoidType(TypeDefinition *type) {
  type->type_id = TYPE_ID_VOID;
  type->data = NULL;
}
