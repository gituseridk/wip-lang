#include "./type-defenition.h"

bool isBool(const TypeDefinition *type) {
  return type->type_id == TYPE_ID_INT ||
         type->type_id == TYPE_ID_FLOAT ||
         type->type_id == TYPE_ID_POINTER ||
         type->type_id == TYPE_ID_CHAR;
}
