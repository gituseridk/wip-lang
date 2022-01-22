#include <stdio.h>
#include <stdlib.h>

#include "expression-data/expression-data.h"
#include "token/token-data.h"
#include "syntax-tree/syntax-tree.h"
#include "compiler/compiler.h"

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("wrong number of args, expected input file name\n");
    exit(1);
  }

  char *file_name = argv[1];
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

  int global_offset = 8;

  tree->root_node.handler->getExpressionData(
    src,
    tree->root_node.data,
    tree->root_node.token,
    &root_expression,
    &global_offset,
    tree->root_node.handler->id
  );


  const char *out_file_name = "out.s";
  FILE *out_file = fopen(out_file_name, "w");

  if (file == NULL) {
    printf("Failed to open result file '%s'.\n", out_file_name);
    return 1;
  }

  compile(src, ARCH_X86, root_expression, out_file);

  listFree(tokens);
  free(src);

  return 0;
}
