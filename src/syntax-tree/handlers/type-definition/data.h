#ifndef SYNTAX_DATA_TYPE_DEFINITION_H
#define SYNTAX_DATA_TYPE_DEFINITION_H

#include "type-definition/type-definition.h"

typedef struct {
  TypeDefinition value;
} SyntaxTypeDefinitionData;

void printSyntaxTypeDefinitionData(SyntaxTypeDefinitionData *data);

#endif
