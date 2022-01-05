#include <stdlib.h>
#include <stdio.h>

#include "utils/logger/log-src-error.h"
#include "syntax-tree/syntax-node.h"
#include "syntax-tree/syntax-helpers.h"
#include "./data.h"


void getInitializationExpressionData(
  const char *src,
  void *raw_data,
  List *token,
  ExpressionData *result
) {
  SyntaxInitializationData *data = (SyntaxInitializationData*)raw_data;

  result->id = EXPRESSION_INITIALIZATION;

  if (mapGet(result->parent_scope->variables, data->identifier) != NULL) {
    TokenData *identifier_token = (TokenData*) trimTokensLeft(listNext(token));
    char msg[100];
    sprintf(msg, "name \"%s\" is already used", data->identifier);
    printSourceError(src, msg, identifier_token->row, identifier_token->col);
  }

  mapSet(result->parent_scope->variables, data->identifier, &(result->result_type));
}
