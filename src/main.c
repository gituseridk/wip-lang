#include <stdio.h>
#include <stdlib.h>

#include "expression-data/expression-data.h"
#include "token/token-data.h"
#include "syntax-tree/syntax-tree.h"

int main() {
  char *file_name = "./src.wip";
  FILE *file = fopen(file_name, "r"); // read mode

  if (file == NULL) {
    printf("Failed to open file '%s'.\n", file_name);
    return 1;
  }

  fseek(file, 0, SEEK_END);
  long length = ftell(file);
  fseek(file, 0, SEEK_SET);
  char *src = malloc(length+1);
  if (src) {
    fread(src, 1, length, file);
  }
  fclose(file);
  src[length] = 0;

  List *tokens = tokenize(src);

  if (tokens == NULL) {
    printf("failed to tokenize sources\n");
    return 1;
  }

  printf("==tokens==\n");
  int i = 0;
  for (List *token = tokens; token != NULL; token = listNext(token)) {
    printf("tokens[%d]: ", i++);
    tokenDataPrint(listGetValue(token));
  }
  printf("==TOKENS==\n");

  SyntaxTree *tree = createSyntaxTree(tokens, src);
  if (tree == NULL) {
    printf("failed to parse syntax tree\n");
    return 1;
  }
  printf("===ast===\n");
  printSyntaxTree(tree);
  printf("===AST===\n");

  ExpressionData root_expression;
  root_expression.parent_scope = NULL;

  unsigned global_size = 0;

  tree->root_node.handler->getExpressionData(
    src,
    tree->root_node.data,
    tree->root_node.token,
    &root_expression,
    &global_size,
    tree->root_node.handler->id
  );

  listFree(tokens);
  free(src);

  return 0;
}
