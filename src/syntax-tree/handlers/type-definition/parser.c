#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

#include "utils/array/array.h"
#include "syntax-tree/syntax-helpers.h"
#include "syntax-tree/handlers/expression/parser.h"

#include "./parser.h"
#include "./data.h"

List* parseTypeDefinition(List *start_token, SyntaxNode *result, char **error) {
  *error = NULL;
  *result = (SyntaxNode) {
    .data = NULL,
    .handler = getSyntaxNodeHandler(SYNTAX_TYPE_DEFINITION), 
  };

  List *current_token = trimTokensLeft(start_token);
  TokenData *token = (TokenData*) listGetValue(current_token);

  if (token->token.id != TOKEN_KEYWORD) {
    *error = "Failed to parse type definition: nexpected token";
    return current_token;
  }

  result->data = malloc(sizeof(SyntaxTypeDefinitionData));
  SyntaxTypeDefinitionData *type_data = (SyntaxTypeDefinitionData*) result->data;
  type_data->data = NULL;

  if (strcmp(token->value, SYNTAX_TYPE_VOID_NAME) == 0) {
    type_data->type_id = SYNTAX_TYPE_ID_VOID;
    return listNext(current_token);
  }
  if (strcmp(token->value, SYNTAX_TYPE_INT_NAME) == 0) {
    type_data->type_id = SYNTAX_TYPE_ID_INT;
    return listNext(current_token);
  }
  if (strcmp(token->value, SYNTAX_TYPE_FLOAT_NAME) == 0) {
    type_data->type_id = SYNTAX_TYPE_ID_FLOAT;
    return listNext(current_token);
  }
  if (strcmp(token->value, SYNTAX_TYPE_CHAR_NAME) == 0) {
    type_data->type_id = SYNTAX_TYPE_ID_CHAR;
    return listNext(current_token);
  }

  *error = "Failed to parse type definition: unexpected keyword";
  free(result->data);
  return current_token;
}
