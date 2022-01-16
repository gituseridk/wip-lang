#include "./type-definition.h"
#include "./pointer/data.h"

bool isSameType(const TypeDefinition *left, const TypeDefinition *right) {
  if (left->type_id != right->type_id) {
    return false;
  }
  if (left->type_id < COMPLEX_TYPES_START_ID) {
    return true;
  }

  if (left->type_id == TYPE_ID_POINTER) {
    TypePointerData *left_ptr_data = (TypePointerData*) left->data;
    TypePointerData *right_ptr_data = (TypePointerData*) right->data;
    return isSameType(&(left_ptr_data->type), &(right_ptr_data->type));
  }

  return left->type_id == right->type_id && left->data == right->data;
}
