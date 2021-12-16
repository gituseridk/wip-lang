#ifndef AST_H
#define AST_H

#include "./syntax-node.h"

typedef struct {
  SyntaxNode root_node;
} SyntaxTree;

SyntaxTree* createSyntaxTree(List *tokens, char *src);
void printSyntaxTree(SyntaxTree *tree);

#endif
