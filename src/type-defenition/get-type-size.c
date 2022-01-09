#include "./type-defenition.h"

unsigned getTypeSize(const TypeDefinition *type, char **error) {
  switch (type->type_id)
  {
  case TYPE_ID_VOID:
    return TYPE_SIZE_VOID;
  case TYPE_ID_INT:
    return TYPE_SIZE_INT;
  case TYPE_ID_FLOAT:
    return TYPE_SIZE_FLOAT;
  case TYPE_ID_POINTER:
    return TYPE_SIZE_POINTER;
  case TYPE_ID_CHAR:
    return TYPE_SIZE_CHAR;
  case TYPE_ID_FUNCTION:
    return TYPE_SIZE_FUNCTION;

  case TYPE_ID_STRUCT:
    *error = "struct type size is not fully implemented yet";
    return 0;

  default:
    *error = "unknown type";
    return 0;
  }
}
