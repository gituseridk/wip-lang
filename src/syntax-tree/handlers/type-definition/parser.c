#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "type-definition/pointer/data.h"
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
    .priority = SYNTAX_TYPE_DEFINITION * SYNTAX_PRIORITY_OFFSET,
  };

  List *current_token = trimTokensLeft(start_token);
  result->token = current_token;
  TokenData *token = (TokenData*) listGetValue(current_token);

  if (token->token.id == TOKEN_OPERATOR_PRODUCT) {
    SyntaxNode point_type;
    current_token = trimTokensLeft(listNext(current_token));
    current_token = parseTypeDefinition(current_token, &point_type, error);

    if (*error != NULL) {
      printf("%s\n", *error);
      return current_token;
    }

    SyntaxTypeDefinitionData *inner_type = (SyntaxTypeDefinitionData*) point_type.data;

    result->data = malloc(sizeof(SyntaxTypeDefinitionData));
    SyntaxTypeDefinitionData *result_type = (SyntaxTypeDefinitionData*) result->data;

    result_type->value.type_id = TYPE_ID_POINTER;
    result_type->value.data = malloc(sizeof(TypePointerData));
    *(TypePointerData*) result_type->value.data = (TypePointerData) {
      .size = 1,
      .type = inner_type->value,
    };

    return current_token;
  }

  if (token->token.id != TOKEN_KEYWORD) {
    *error = "Failed to parse type definition: expected token";
    return current_token;
  }

  result->data = malloc(sizeof(SyntaxTypeDefinitionData));
  SyntaxTypeDefinitionData *type_data = (SyntaxTypeDefinitionData*) result->data;
  type_data->value.data = NULL;

  if (strcmp(token->value, TYPE_NAME_VOID) == 0) {
    type_data->value.type_id = TYPE_ID_VOID;
    return listNext(current_token);
  }
  if (strcmp(token->value, TYPE_NAME_INT) == 0) {
    type_data->value.type_id = TYPE_ID_INT;
    return listNext(current_token);
  }
  if (strcmp(token->value, TYPE_NAME_FLOAT) == 0) {
    type_data->value.type_id = TYPE_ID_FLOAT;
    return listNext(current_token);
  }
  if (strcmp(token->value, TYPE_NAME_CHAR) == 0) {
    type_data->value.type_id = TYPE_ID_CHAR;
    return listNext(current_token);
  }

  *error = "Failed to parse type definition: unexpected keyword";
  free(result->data);
  return current_token;
}
