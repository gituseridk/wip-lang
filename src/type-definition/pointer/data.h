#ifndef TYPE_POINTER_DATA
#define TYPE_POINTER_DATA

#include "type-definition/type-definition.h"

typedef struct {
  TypeDefinition type;
  unsigned size;
} TypePointerData;

void printPointerData(const TypePointerData *data);

#endif
