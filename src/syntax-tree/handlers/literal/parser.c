#include <stdlib.h>
#include <stdio.h>

#include "utils/array/array.h"
#include "syntax-tree/handlers/expression/parser.h"

#include "./parser.h"
#include "./data.h"

static void printLiteralNode(SyntaxNode *self) {
  printf("{literal:");
  printSyntaxLiteralData(self->data);
  printf("}");
}

List* parseLiteral(List *token, SyntaxNode *result, char **error) {
  *error = NULL;
  *result = (SyntaxNode) {
    .id = SYNTAX_LITERAL,
    .data = NULL,
    .print = printLiteralNode,
  };

  TokenData *token_data = listGetValue(token);
  SyntaxLiteralData *data = malloc(sizeof(SyntaxLiteralData));
  if (token_data->token.id == TOKEN_LITERAL_FLOAT) {
    data->type_id = SYNTAX_TYPE_ID_FLOAT;
    data->value = malloc(sizeof(float));
    (*(float*) data->value) = atof(token_data->value);
    result->data = data;
    return listNext(token);
  }
  if (token_data->token.id == TOKEN_LITERAL_INT) {
    data->type_id = SYNTAX_TYPE_ID_INT;
    data->value = malloc(sizeof(int));
    (*(int*) data->value) = atoi(token_data->value);
    result->data = data;
    return listNext(token);
  }
  if (token_data->token.id == TOKEN_LITERAL_STRING) {
    *error = "Strings is not supported yet";
    return token;
  }

  *error = "Token is not a literal";

  return token;
}
