#ifndef AST_H
#define AST_H

#include "./syntax-node.h"

typedef struct {
  SyntaxNode *nodes;
} SyntaxTree;

SyntaxTree *createSyntaxTree(TokenData *tokens);

#endif
