#include "./type-defenition.h"

char *getTypeName(const TypeDefinition *type) {
  switch (type->type_id)
  {
  case TYPE_ID_VOID:
    return TYPE_NAME_VOID;
  case TYPE_ID_INT:
    return TYPE_NAME_INT;
  case TYPE_ID_FLOAT:
    return TYPE_NAME_FLOAT;
  case TYPE_ID_CHAR:
    return TYPE_NAME_CHAR;
  case TYPE_ID_FUNCTION:
    return TYPE_NAME_FUNCTION;
  case TYPE_ID_STRUCT:
    return TYPE_NAME_STRUCT;
  case TYPE_ID_POINTER:
    return TYPE_NAME_POINTER;
  
  default:
    return "unnown";
  }
}
