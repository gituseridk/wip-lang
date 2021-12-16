#include <stdlib.h>
#include <stdio.h>

#include "utils/array/array.h"
#include "syntax-tree/handlers/expression/parser.h"
#include "syntax-tree/handlers/initialization/parser.h"
#include "syntax-tree/handlers/literal/parser.h"
#include "syntax-tree/syntax-helpers.h"
#include "./parser.h"
#include "./data.h"

Array *left_expression;
static Array *getLeftExpressions() {
  if (left_expression == NULL) {
    left_expression = newArray(
      ChopExpression,
      &parseInitialization,
      // !TODO add identifire
    );
  }
  return left_expression;
}

void printAssignationNode(SyntaxNode *self) {
  printf("{assignation:");
  printSyntaxAssignationData(self->data);
  printf("}");
}

List *parseAssignation(List *tokens, SyntaxNode *result, char **error) {
  *error = NULL;
  *result = (SyntaxNode) {
    .id = SYNTAX_ASSIGNATION,
    .data = NULL,
    .print = printAssignationNode,
  };

  List *start_token = trimTokensLeft(tokens);

  SyntaxNode left_syntax_node;
  Array *left_expression = getLeftExpressions();
  for (int i = 0; i != arrayGetLength(left_expression); ++i) {
    ChopExpression chopExpression = *(ChopExpression*) arrayAt(left_expression, i);
    List *token_end = chopExpression(start_token, &left_syntax_node, error);
    if (*error == NULL) {
      start_token = token_end;
      break;
    }
  }
  if (*error != NULL) {
    return start_token;
  }

  start_token = trimTokensLeft(start_token);

  TokenData *middle_token = (TokenData*) listGetValue(start_token);

  if (middle_token->token.id != TOKEN_OPERATOR || middle_token->value[0] != '=') {
    *error = "Failed to parse assignation, missing '=' sign";
    return start_token;
  }
  start_token = trimTokensLeft(listNext(start_token));
  
  SyntaxNode right_syntax_node;
  start_token = parseExpression(start_token, &right_syntax_node, error);
  if (*error != NULL) {
    return start_token;
  }

  SyntaxAssignationData *data = malloc(sizeof(SyntaxAssignationData));
  data->left = left_syntax_node;
  data->right = right_syntax_node;
  result->data = data;

  return start_token;
}
