#ifndef SYNTAX_NODE_H
#define SYNTAX_NODE_H

#include "syntax-node-handler.h"
#include "token/token-data.h"

#define SYNTAX_TYPE_ID_INT 0
#define SYNTAX_TYPE_ID_FLOAT 1
#define SYNTAX_TYPE_ID_STRING 2

typedef struct SyntaxNode SyntaxNode;

struct SyntaxNode {
  SyntaxNodeHandler *handler;
  void *data;
};

void syntaxNodePrint(SyntaxNode *self);

#endif
