#include <stdlib.h>
#include <stdio.h>

#include "utils/array/array.h"
#include "syntax-tree/handlers/expression/parser.h"

#include "./parser.h"
#include "./data.h"

List* parseIdentifier(List *token, SyntaxNode *result, char **error) {
  *error = NULL;
  *result = (SyntaxNode) {
    .data = NULL,
    .handler = getSyntaxNodeHandler(SYNTAX_IDENTIFIER), 
    .token = token,
    .priority = SYNTAX_IDENTIFIER * SYNTAX_PRIORITY_OFFSET,
  };

  TokenData *token_data = listGetValue(token);
  if (token_data->token.id == TOKEN_IDENTIFIER) {
    SyntaxIdentifierData *data = malloc(sizeof(SyntaxIdentifierData));
    data->name = token_data->value;
    result->data = data;
    return listNext(token);
  }

  *error = "Token is not an identifier";

  return token;
}
