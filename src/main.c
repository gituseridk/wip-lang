#include <stdlib.h>

#include "config/config.h"
#include "expression-data/expression-data.h"
#include "token/token-data.h"
#include "syntax-tree/syntax-tree.h"
#include "compiler/compiler.h"
#include "preprocessor/preprocessor.h"

int main(int argc, char **argv) {
  Config config = readConfig(argc, argv);

  List* tokens = preprocessFile(config).first_token;

  if (tokens == NULL) {
    printf("failed to tokenize sources\n");
    return 1;
  }

  #ifdef DEBUG_TOKENS
  printf("==tokens==\n");
  int i = 0;
  for (List *token = tokens; token != NULL; token = listNext(token)) {
    printf("tokens[%d]: ", i++);
    tokenDataPrint(listGetValue(token));
  }
  printf("==TOKENS==\n");
  #endif

  SyntaxTree *tree = createSyntaxTree(tokens);
  if (tree == NULL) {
    printf("failed to parse syntax tree\n");
    return 1;
  }

  #ifdef DEBUG_AST
  printf("===ast===\n");
  printSyntaxTree(tree);
  printf("===AST===\n");
  #endif

  ExpressionData root_expression;
  root_expression.parent_scope = NULL;

  int global_offset = 8;

  tree->root_node.handler->getExpressionData(
    tree->root_node.data,
    tree->root_node.token,
    &root_expression,
    &global_offset,
    tree->root_node.handler->id
  );

  const char *out_file_name = "out.s";
  FILE *out_file = fopen(out_file_name, "w");

  if (out_file == NULL) {
    printf("Failed to open result file '%s'.\n", out_file_name);
    return 1;
  }

  compile(ARCH_X86, root_expression, out_file);

  listFree(tokens);

  return 0;
}
