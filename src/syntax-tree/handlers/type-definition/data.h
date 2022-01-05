#ifndef SYNTAX_DATA_TYPE_DEFINITION_H
#define SYNTAX_DATA_TYPE_DEFINITION_H

#include <stdbool.h>

typedef struct {
  int type_id;
  void *data;
} SyntaxTypeDefinitionData;

void printSyntaxTypeDefinitionData(SyntaxTypeDefinitionData *data);

#endif
