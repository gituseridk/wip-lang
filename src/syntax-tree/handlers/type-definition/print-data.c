#include <stdio.h>
#include "./data.h"

// !TODO add type name and structs
void printSyntaxTypeDefinitionData(SyntaxTypeDefinitionData *data) {
  printf("{\"type_name\":\"%s\"}", getTypeName(&(data->value)));
}
