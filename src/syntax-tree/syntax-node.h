#ifndef SYNTAX_NODE_H
#define SYNTAX_NODE_H

#include "token/token-data.h"

typedef struct {
  int id;
  void *data;
} SyntaxNode;

#endif
