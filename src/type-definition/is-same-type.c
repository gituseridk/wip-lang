#include "./type-definition.h"

bool isSameType(const TypeDefinition *left, const TypeDefinition *right) {
  if (left->type_id < COMPLEX_TYPES_START_ID) {
    return left->type_id == right->type_id;
  }

  return left->type_id == right->type_id && left->data == right->data;
}
