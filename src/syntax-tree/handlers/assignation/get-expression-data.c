#include <stdlib.h>

#include "utils/logger/log-src-error.h"
#include "./data.h"

void getAssignationExpressionData(const char *src, void *raw_data, List *token, ExpressionData *result, unsigned *offset) {
  SyntaxAssignationData *data = (SyntaxAssignationData*) raw_data;
  result->id = EXPRESSION_ASSIGNATION;

  ExpressionData left;
  left.parent_scope = result->parent_scope;
  ExpressionData right;
  right.parent_scope = result->parent_scope;

  data->left.handler->getExpressionData(src, data->left.data, data->left.token, &left, offset);
  result->result_type = left.result_type;

  data->right.handler->getExpressionData(src, data->right.data, data->right.token, &right, offset);

  if (left.result_type.type_id != right.result_type.type_id) {
    TokenData *token = (TokenData*)listGetValue(data->left.token);
    printSourceError(src, "", token->row, token->col);
    exit(1);
  }
}
