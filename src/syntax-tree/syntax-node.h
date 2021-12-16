#ifndef SYNTAX_NODE_H
#define SYNTAX_NODE_H

#include "token/token-data.h"

#define SYNTAX_PROGRAM 0
#define SYNTAX_ASSIGNATION 1
#define SYNTAX_INITIALIZATION 2
#define SYNTAX_LITERAL 3

#define SYNTAX_TYPE_ID_INT = 0
#define SYNTAX_TYPE_ID_FLOAT = 1
#define SYNTAX_TYPE_ID_STRING = 2

typedef struct {
  int id;
  void *data;
} SyntaxNode;

#endif
