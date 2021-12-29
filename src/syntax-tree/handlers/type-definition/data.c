#include <stdio.h>
#include "./data.h"

// !TODO add type name and structs
void printSyntaxTypeDefinitionData(SyntaxTypeDefinitionData *data) {
  printf("{\"type_id\":%d}", data->type_id);
}
