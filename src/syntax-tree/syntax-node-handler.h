#ifndef SYNTAX_NODE_HANDLER_H
#define SYNTAX_NODE_HANDLER_H

#include "expression-data/expression-data.h"
#include "utils/array/array.h"
#include "utils/list/list.h"

#define SYNTAX_PRIORITY_OFFSET 100

enum SyntaxId {
  SYNTAX_SCOPE,

  SYNTAX_ASSIGNATION,
  SYNTAX_RETURN,
  SYNTAX_OPERATION_LR,

  SYNTAX_OPERATION_PREFIX,
  SYNTAX_OPERATION_POSTFIX,

  SYNTAX_INITIALIZATION,
  SYNTAX_LITERAL,
  SYNTAX_FUNCTION_CALL,
  SYNTAX_IDENTIFIER,
  SYNTAX_FUNCTION,
  SYNTAX_TYPE_DEFINITION,

  SYNTAX_IF,
  SYNTAX_WHILE,

  SYNTAX_ID_SIZE,
};

typedef void (*PrintData)(void *data);
typedef void (*GetExpressionData)(
  const char *src,
  void *data,
  List *token,
  ExpressionData *result,
  int *offset,
  int handler_id
);

typedef struct {
  int id;
  char *name;
  bool is_void_expression;
  PrintData printData;
  GetExpressionData getExpressionData;
} SyntaxNodeHandler;

SyntaxNodeHandler *getSyntaxNodeHandler(int id);

#endif
