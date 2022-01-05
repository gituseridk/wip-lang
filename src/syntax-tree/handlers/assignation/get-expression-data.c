#include <stdlib.h>

#include "utils/logger/log-src-error.h"
#include "../initialization/data.h"
#include "./data.h"

void getAssignationExpressionData(const char *src, void *raw_data, List *token, ExpressionData *result, unsigned *offset) {
  SyntaxAssignationData *data = (SyntaxAssignationData*) raw_data;
  result->id = EXPRESSION_ASSIGNATION;

  ExpressionData left;
  left.parent_scope = result->parent_scope;
  ExpressionData right;
  right.parent_scope = result->parent_scope;

  data->right.handler->getExpressionData(src, data->right.data, data->right.token, &right, offset);
  result->result_type = right.result_type;

  if (data->left.handler->getExpressionData == getInitializationExpressionData) {
    left.result_type = right.result_type;
  }

  data->left.handler->getExpressionData(src, data->left.data, data->left.token, &left, offset);

  if (
    left.result_type.type_id != right.result_type.type_id ||
    left.result_type.data != right.result_type.data
  ) {
    TokenData *token = (TokenData*)listGetValue(data->left.token);
    printSourceError(src, "type mismatch", token->row, token->col);
    exit(1);
  }
}
