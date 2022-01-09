#include <stdio.h>
#include "./data.h"

// !TODO add type name and structs
void printSyntaxTypeDefinitionData(SyntaxTypeDefinitionData *data) {
  printTypeDefinition(&(data->value));
}
