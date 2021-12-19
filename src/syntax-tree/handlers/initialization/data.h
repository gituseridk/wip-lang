#ifndef SYNTAX_DATA_INITIALISATION_H
#define SYNTAX_DATA_INITIALISATION_H

#include <stdbool.h>
#include "syntax-tree/syntax-node.h"

typedef struct {
  bool is_constant;
  char *identifier;
} SyntaxInitializationData;

void printSyntaxInitializationData(SyntaxInitializationData *data);

#endif
