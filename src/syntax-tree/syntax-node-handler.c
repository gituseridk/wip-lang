#include <stdio.h>

#include "utils/logger/log-src-error.h"

#include "./handlers/scope/data.h"
#include "./handlers/if/data.h"
#include "./handlers/while/data.h"
#include "./handlers/assignation/data.h"
#include "./handlers/operation-prefix/data.h"
#include "./handlers/operation-postfix/data.h"
#include "./handlers/operation-lr/data.h"
#include "./handlers/initialization/data.h"
#include "./handlers/literal/data.h"
#include "./handlers/identifier/data.h"
#include "./handlers/function/data.h"
#include "./handlers/function-call/data.h"
#include "./handlers/return/data.h"
#include "./handlers/function-call/data.h"
#include "./handlers/type-definition/data.h"
#include "./syntax-node-handler.h"

Array *handlers;

void getNotImplementedExpressionData(
  void *raw_data,
  List *token,
  ExpressionData *result,
  int *offset,
  int handler_id
) {
  char err[100];
  sprintf(err, "\"%s\" syntax node is not implemented yet", getSyntaxNodeHandler(handler_id)->name);
  throwSourceError(err, token);
}

static Array *getSyntaxNodeHandlers() {
  if (handlers != NULL) {
    return handlers;
  }

  handlers = createArray(
    SYNTAX_ID_SIZE,
    sizeof(SyntaxNodeHandler),
    NULL
  );


  arraySetElementAt(
    handlers,
    SYNTAX_SCOPE,
    &((SyntaxNodeHandler) {
      .id = SYNTAX_SCOPE,
      .name = "scope",
      .is_void_expression = true,
      .printData = (PrintData) printSyntaxScopeData,
      .getExpressionData = (GetExpressionData) getScopeExpressionData,
    })
  );
  arraySetElementAt(
    handlers,
    SYNTAX_IF,
    &((SyntaxNodeHandler) {
      .id = SYNTAX_IF,
      .name = "if",
      .is_void_expression = true,
      .printData = (PrintData) printSyntaxIfData,
      .getExpressionData = (GetExpressionData) getIfExpressionData,
    })
  );
  arraySetElementAt(
    handlers,
    SYNTAX_WHILE,
    &((SyntaxNodeHandler) {
      .id = SYNTAX_WHILE,
      .name = "while",
      .is_void_expression = true,
      .printData = (PrintData) printSyntaxWhileData,
      .getExpressionData = (GetExpressionData) getWhileExpressionData,
    })
  );
  arraySetElementAt(
    handlers,
    SYNTAX_FUNCTION_CALL,
    &((SyntaxNodeHandler) {
      .id = SYNTAX_FUNCTION_CALL,
      .name = "function-call",
      .is_void_expression = false,
      .printData = (PrintData) printSyntaxFunctionCallData,
      .getExpressionData = (GetExpressionData) getFunctionCallExpressionData,
    })
  );
  arraySetElementAt(
    handlers,
    SYNTAX_ASSIGNATION,
    &((SyntaxNodeHandler) {
      .id = SYNTAX_ASSIGNATION,
      .name = "assignation",
      .is_void_expression = true,
      .printData = (PrintData) printSyntaxAssignationData,
      .getExpressionData = (GetExpressionData) getAssignationExpressionData,
    })
  );
  arraySetElementAt(
    handlers,
    SYNTAX_OPERATION_PREFIX,
    &((SyntaxNodeHandler) {
      .id = SYNTAX_OPERATION_PREFIX,
      .name = "operation-prefix",
      .is_void_expression = false,
      .printData = (PrintData) printSyntaxOperationPrefixData,
      .getExpressionData = (GetExpressionData) getOperationPrefixExpressionData,
    })
  );
  arraySetElementAt(
    handlers,
    SYNTAX_OPERATION_POSTFIX,
    &((SyntaxNodeHandler) {
      .id = SYNTAX_OPERATION_POSTFIX,
      .name = "operation-postfix",
      .is_void_expression = false,
      .printData = (PrintData) printSyntaxOperationPostfixData,
      .getExpressionData = (GetExpressionData) getOperationPostfixExpressionData,
    })
  );
  arraySetElementAt(
    handlers,
    SYNTAX_OPERATION_LR,
    &((SyntaxNodeHandler) {
      .id = SYNTAX_OPERATION_LR,
      .name = "operation-lr",
      .is_void_expression = false,
      .printData = (PrintData) printSyntaxOperationLRData,
      .getExpressionData = (GetExpressionData) getOperationLRExpressionData,
    })
  );
  arraySetElementAt(
    handlers,
    SYNTAX_INITIALIZATION,
    &((SyntaxNodeHandler) {
      .id = SYNTAX_INITIALIZATION,
      .name = "initialization",
      .is_void_expression = false,
      .printData = (PrintData) printSyntaxInitializationData,
      .getExpressionData = (GetExpressionData) getInitializationExpressionData,
    })
  );
  arraySetElementAt(
    handlers,
    SYNTAX_LITERAL,
    &((SyntaxNodeHandler) {
      .id = SYNTAX_LITERAL,
      .name = "literal",
      .is_void_expression = false,
      .printData = (PrintData) printSyntaxLiteralData,
      .getExpressionData = (GetExpressionData) getLiteralExpressionData,
    })
  );
  arraySetElementAt(
    handlers,
    SYNTAX_IDENTIFIER,
    &((SyntaxNodeHandler) {
      .id = SYNTAX_IDENTIFIER,
      .name = "identifier",
      .is_void_expression = false,
      .printData = (PrintData) printSyntaxIdentifierData,
      .getExpressionData = (GetExpressionData) getIdentifierExpressionData,
    })
  );
  arraySetElementAt(
    handlers,
    SYNTAX_FUNCTION,
    &((SyntaxNodeHandler) {
      .id = SYNTAX_FUNCTION,
      .name = "function",
      .is_void_expression = false,
      .printData = (PrintData) printSyntaxFunctionData,
      .getExpressionData = (GetExpressionData) getFunctionExpressionData,
    })
  );
  arraySetElementAt(
    handlers,
    SYNTAX_RETURN,
    &((SyntaxNodeHandler) {
      .id = SYNTAX_RETURN,
      .name = "return",
      .is_void_expression = true,
      .printData = (PrintData) printSyntaxReturnData,
      .getExpressionData = (GetExpressionData) getReturnExpressionData,
    })
  );
  arraySetElementAt(
    handlers,
    SYNTAX_TYPE_DEFINITION,
    &((SyntaxNodeHandler) {
      .id = SYNTAX_TYPE_DEFINITION,
      .name = "type_definition",
      .is_void_expression = true,
      .printData = (PrintData) printSyntaxTypeDefinitionData,
      .getExpressionData = (GetExpressionData) getNotImplementedExpressionData,
    })
  );

  return handlers;
}

SyntaxNodeHandler *getSyntaxNodeHandler(int id) {
  SyntaxNodeHandler *result = arrayAt(getSyntaxNodeHandlers(), id);
  if (result == NULL) {
    printf("failed to find syntax  id %d\n", id);
  }
  return result;
}
