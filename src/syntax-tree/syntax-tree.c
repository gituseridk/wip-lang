#include <stdio.h>
#include <stdlib.h>

#include "utils/logger/log-src-error.h"

#include "./syntax-tree.h"
#include "./handlers/scope/parser.h"
#include "./syntax-node.h"

SyntaxTree* createSyntaxTree(List *tokens) {
  char *error = NULL;
  SyntaxNode node;
  List *last_loken = parseScopeGlobal(tokens, &node, &error);

  if (error != NULL) {
    if (last_loken == NULL) {
      return NULL;
    }
    throwSourceError(error, last_loken);
    return NULL;
  }

  SyntaxTree *result = malloc(sizeof(SyntaxTree));
  result->root_node = node;

  return result;
}

void printSyntaxTree(SyntaxTree *tree) {
  syntaxNodePrint(&(tree->root_node));
  printf("\n");
}
