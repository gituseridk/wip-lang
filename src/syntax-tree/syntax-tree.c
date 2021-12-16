#include <stdio.h>
#include <stdlib.h>

#include "utils/logger/log-src-error.h"

#include "./syntax-tree.h"
#include "./handlers/program/parser.h"
#include "./syntax-node.h"

SyntaxTree* createSyntaxTree(List *tokens, char *src) {
  char *error = NULL;
  SyntaxNode node;
  List *last_loken = parseProgram(tokens, &node, &error);

  if (error != NULL) {
    TokenData *token_data = (TokenData*) listGetValue(last_loken);
    printSourceError(src, error, token_data->row, token_data->col);
    return NULL;
  }

  SyntaxTree *result = malloc(sizeof(SyntaxTree));
  result->root_node = node;

  return result;
}

void printSyntaxTree(SyntaxTree *tree) {
  tree->root_node.print(&(tree->root_node));
  printf("\n");
}
