#ifndef SYNTAX_DATA_SCOPE_H
#define SYNTAX_DATA_SCOPE_H

#include "utils/array/array.h"

typedef struct {
  Array *nodes;
} SyntaxScopeData;

void printSyntaxScopeData(SyntaxScopeData *data);

#endif
