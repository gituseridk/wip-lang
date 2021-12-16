#ifndef SYNTAX_DATA_ASSIGNITION_H
#define SYNTAX_DATA_ASSIGNITION_H

#include "syntax-tree/syntax-node.h"

typedef struct {
  SyntaxNode left;
  SyntaxNode right;
} SyntaxAssignationData;

#endif
