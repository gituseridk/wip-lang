#ifndef SYNTAX_DATA_ASSIGNITION_H
#define SYNTAX_DATA_ASSIGNITION_H

#include <stdbool.h>
#include "syntax-tree/syntax-node.h"

typedef struct {
  bool is_constant;
  char *identifier;
} SyntaxInitializationData;

#endif
