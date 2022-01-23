#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "utils/array/array.h"
#include "syntax-tree/syntax-helpers.h"
#include "syntax-tree/handlers/expression/parser.h"
#include "syntax-tree/handlers/type-definition/parser.h"

#include "./parser.h"
#include "./data.h"

static List *chopType(List *token, TypeDefinition **type) {
  char *error = NULL;
  List *current_token = chopToken(token, TOKEN_SEPARATOR, ":", &error); 
  if (error != NULL || current_token == NULL) {
    return token;
  }

  current_token = trimTokensLeft(current_token);
  if (current_token == NULL) {
    return token;
  }

  SyntaxNode type_def_node;
  List *end_token = parseTypeDefinition(current_token, &type_def_node, &error);
  if (error != NULL) {
    return token;
  }

  SyntaxTypeDefinitionData *data = (SyntaxTypeDefinitionData*) type_def_node.data;
  *type = malloc(sizeof(TypeDefinition));
  **type = data->value;
  return end_token;
}

List *parseInitialization(List *token, SyntaxNode *result, char **error) {
  *error = NULL;
  *result = (SyntaxNode) {
    .data = NULL,
    .handler = getSyntaxNodeHandler(SYNTAX_INITIALIZATION), 
    .priority = SYNTAX_INITIALIZATION * SYNTAX_PRIORITY_OFFSET,
    .token = token,
  };

  TokenData *initialization_type = (TokenData*) listGetValue(token);
  if (
    initialization_type->token.id != TOKEN_KEYWORD ||
    (strcmp(initialization_type->value, "const") != 0 && strcmp(initialization_type->value, "var") != 0)
  ) {
    *error = "Unexpected token, must be a 'const' or 'var' keyword";
    return token;
  }

  token = trimTokensLeft(listNext(token));
  if (token == NULL) {
    *error = "Failed to parse initialization, end of scope";
    return token;
  }
  TokenData *name_token = (TokenData*) listGetValue(token);

  if (name_token->token.id != TOKEN_IDENTIFIER) {
    *error = "Unexpected token, must be an identifier";
    return token;
  }

  token = trimTokensLeft(listNext(token));
  if (token == NULL) {
    *error = "Failed to parse initialization, end of scope";
    return token;
  }

  TypeDefinition *type = NULL;
  token = chopType(token, &type);

  SyntaxInitializationData *data = malloc(sizeof(SyntaxInitializationData));
  data->identifier = name_token->value;
  data->is_constant = strcmp(initialization_type->value, "const") == 0;
  data->type = type;
  result->data = data;

  return token;
}
