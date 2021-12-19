#include <stdlib.h>
#include <stdio.h>

#include "syntax-tree/syntax-helpers.h"
#include "syntax-tree/handlers/expression/parser.h"

#include "./data.h"
#include "./parser.h"

static void printScopeNode(SyntaxNode *self) {
  printf("{scope:");
  printSyntaxScopeData(self->data);
  printf("}");
}

List *parseScope(List *tokens, SyntaxNode *result, char **error) {
  *error = NULL;
  SyntaxScopeData *data = (SyntaxScopeData*) malloc(sizeof(SyntaxScopeData));
  *result = (SyntaxNode) {
    .data = data,
    .handler = getSyntaxNodeHandler(SYNTAX_SCOPE),
  };

  data->nodes = newArray(SyntaxNode);

  List *current_token = tokens;
  while (current_token != NULL) {
    SyntaxNode node;
    current_token = parseExpression(current_token, &node, error, false);
    if (*error != NULL) {
      return current_token;
    }
    current_token = chopExpressionEnd(current_token, error);
    if (*error != NULL) {
      return current_token;
    }
    arrayPush(data->nodes, &node);
    current_token = trimTokensLeftHard(current_token);
  }

  return current_token;
}
