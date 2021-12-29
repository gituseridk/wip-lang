#include <stdlib.h>
#include <stdio.h>

#include "utils/array/array.h"
#include "syntax-tree/handlers/expression/parser.h"
#include "syntax-tree/handlers/initialization/parser.h"
#include "syntax-tree/handlers/identifier/parser.h"
#include "syntax-tree/handlers/literal/parser.h"
#include "syntax-tree/syntax-helpers.h"
#include "./parser.h"
#include "./data.h"

List *parseReturn(List *start_token, SyntaxNode *result, char **error) {
  *error = NULL;
  *result = (SyntaxNode) {
    .data = NULL,
    .handler = getSyntaxNodeHandler(SYNTAX_RETURN),
  };

  List *current_token = trimTokensLeft(start_token);
  current_token = chopToken(current_token, TOKEN_KEYWORD, "return", error);
  if (*error != NULL) {
    return current_token;
  }

  current_token = trimTokensLeft(current_token);
  
  SyntaxNode expression;
  current_token = parseExpression(current_token, &expression, error, parseReturn);
  if (*error != NULL) {
    return current_token;
  }
  result->data = malloc(sizeof(SyntaxReturnData));
  ((SyntaxReturnData*) result->data)->expression = expression;

  return current_token;
}
