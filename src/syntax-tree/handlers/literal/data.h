#ifndef SYNTAX_DATA_ASSIGNITION_H
#define SYNTAX_DATA_ASSIGNITION_H

#include <stdbool.h>
#include "syntax-tree/syntax-node.h"

typedef struct {
  int type_id;
  void *value;
} SyntaxLiteralData;

#endif
