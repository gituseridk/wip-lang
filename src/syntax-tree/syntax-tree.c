#include <stdio.h>

#include "./syntax-tree.h"
#include "./handlers/program/parser.h"
#include "./syntax-node.h"

SyntaxTree createSyntaxTree(List *tokens) {
  char *error;
  SyntaxNode node;
  parseProgram(tokens, &node, &error);

  return (SyntaxTree) {
    .root_node = node,
  };
}

void printSyntaxTree(SyntaxTree *tree) {
  tree->root_node.print(&(tree->root_node));
  printf("\n");
}
