#ifndef SYNTAX_NODE_H
#define SYNTAX_NODE_H

#include "syntax-node-handler.h"
#include "token/token-data.h"

typedef struct SyntaxNode SyntaxNode;

struct SyntaxNode {
  List *token;
  SyntaxNodeHandler *handler;
  int priority;
  void *data;
};

void syntaxNodePrint(SyntaxNode *self);

#endif
