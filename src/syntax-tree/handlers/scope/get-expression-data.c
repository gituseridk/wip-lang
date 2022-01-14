#include <stdlib.h>
#include <stdio.h>

#include "expression-data/expression-data.h"
#include "utils/logger/log-src-error.h"
#include "syntax-tree/syntax-node.h"
#include "./data.h"

unsigned last_scope_id = 0;

static Array *parseChildExpressions(
  const char *src,
  ExpressionData* self,
  SyntaxScopeData *data,
  Map *variables,
  TypeDefinition *result_type,
  unsigned *offset
) {

  Array *result = createEmptyArray(1u, sizeof(ExpressionData));

  for (int i = 0; i != arrayGetLength(data->nodes); ++i) {
    SyntaxNode *node = (SyntaxNode*) arrayAt(data->nodes, i);
    ExpressionData child_expression;
    child_expression.result_type.type_id = TYPE_ID_VOID;
    child_expression.result_type.data = NULL;
    child_expression.parent_scope = self;

    node->handler->getExpressionData(
      src,
      node->data,
      node->token,
      &child_expression,
      offset,
      node->handler->id
    );

    arrayPush(result, &child_expression);
  }
  
  return result;
}

void getScopeExpressionData(
  const char *src,
  void *raw_data,
  List *token,
  ExpressionData *result,
  unsigned *offset,
  int handler_id
) {
  *offset = 0;

  SyntaxScopeData *data = (SyntaxScopeData*) raw_data;
  expressionInit(result, EXPRESSION_SCOPE, "scope", token, true);
  if (result->parent_scope == NULL) {
    free(result->variables);
    result->variables = getGlobalVariables();
    for (MapItterator *i = mapBegin(result->variables); !mapItteratorIsEnded(i); mapItteratorNext(i)) {
      *offset += getTypeSize(mapItteratorGet(i).value);
    }
  }
  result->compileX86 = compileScopeX86;

  // !TODO better scope id
  asprintf(&(result->scope_label), "scope_%d", last_scope_id++);

  result->child_expressions = parseChildExpressions(
    src,
    result,
    data,
    result->variables,
    &(result->result_type),
    offset
  );
}
