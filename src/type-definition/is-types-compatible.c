#include "./type-definition.h"
#include "./pointer/data.h"

bool isTypesCompatible(const TypeDefinition *left, const TypeDefinition *right) {
  int left_id = left->type_id;
  int right_id = right->type_id;

  // !TODO make better types convertation system
  // check if pair of types is int and pointer
  if (left_id + right_id - TYPE_ID_INT - TYPE_ID_POINTER == 0) {
    return true;
  }

  if (left_id != right_id) {
    return false;
  }
  if (left_id < COMPLEX_TYPES_START_ID) {
    return true;
  }

  if (left_id == TYPE_ID_POINTER && right_id == TYPE_ID_POINTER) {
    TypePointerData *left_ptr_data = (TypePointerData*) left->data;
    TypePointerData *right_ptr_data = (TypePointerData*) right->data;
    return
      right_ptr_data->type.type_id == TYPE_ID_VOID ||
      left_ptr_data->type.type_id == TYPE_ID_VOID ||
      isTypesCompatible(&(left_ptr_data->type), &(right_ptr_data->type));
  }

  return left->data == right->data;
}
