#include <stdlib.h>
#include <stdio.h>

#include "syntax-tree/handlers/expression/parser.h"

#include "./data.h"
#include "./parser.h"

static void printProgramNode(SyntaxNode *self) {
  printf("{program:");
  printSyntaxProgramData(self->data);
  printf("}");
}

List *parseProgram(List *tokens, SyntaxNode *result, char **error) {
  *error = NULL;
  SyntaxProgramData *data = (SyntaxProgramData*) malloc(sizeof(SyntaxProgramData));
  result->data = data;
  result->id = SYNTAX_PROGRAM;
  result->print = printProgramNode;

  data->nodes = newArray(SyntaxNode);

  List *start_token = tokens;
  while (start_token != NULL) {
    SyntaxNode node;
    start_token = parseExpression(start_token, &node, error);
    if (*error != NULL) {
      return start_token;
    }
    arrayPush(data->nodes, &node);
  }

  return start_token;
}
