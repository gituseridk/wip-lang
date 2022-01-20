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
  const char *src,
  void *raw_data,
  List *token,
  ExpressionData *result,
  int *offset,
  int handler_id
) {
  char err[100];
  sprintf(err, "\"%s\" syntax node is not implemented yet", getSyntaxNodeHandler(handler_id)->name);
  throwSourceError(src, err, token);
}

static Array *getSyntaxNodeHandlers() {
  if (handlers != NULL) {
    return handlers;
  }
  handlers = newArray(
    SyntaxNodeHandler,
    (SyntaxNodeHandler) {
      .id = SYNTAX_SCOPE,
      .name = "scope",
      .is_void_expression = true,
      .printData = (PrintData) printSyntaxScopeData,
      .getExpressionData = (GetExpressionData) getScopeExpressionData,
    },
    (SyntaxNodeHandler) {
      .id = SYNTAX_IF,
      .name = "if",
      .is_void_expression = true,
      .printData = (PrintData) printSyntaxIfData,
      .getExpressionData = (GetExpressionData) getIfExpressionData,
    },
    (SyntaxNodeHandler) {
      .id = SYNTAX_WHILE,
      .name = "while",
      .is_void_expression = true,
      .printData = (PrintData) printSyntaxWhileData,
      .getExpressionData = (GetExpressionData) getWhileExpressionData,
    },
    (SyntaxNodeHandler) {
      .id = SYNTAX_FUNCTION_CALL,
      .name = "function-call",
      .is_void_expression = false,
      .printData = (PrintData) printSyntaxFunctionCallData,
      .getExpressionData = (GetExpressionData) getFunctionCallExpressionData,
    },
    (SyntaxNodeHandler) {
      .id = SYNTAX_ASSIGNATION,
      .name = "assignation",
      .is_void_expression = true,
      .printData = (PrintData) printSyntaxAssignationData,
      .getExpressionData = (GetExpressionData) getAssignationExpressionData,
    },
    (SyntaxNodeHandler) {
      .id = SYNTAX_OPERATION_PREFIX,
      .name = "operation-prefix",
      .is_void_expression = false,
      .printData = (PrintData) printSyntaxOperationPrefixData,
      .getExpressionData = (GetExpressionData) getOperationPrefixExpressionData,
    },
    (SyntaxNodeHandler) {
      .id = SYNTAX_OPERATION_POSTFIX,
      .name = "operation-postfix",
      .is_void_expression = false,
      .printData = (PrintData) printSyntaxOperationPostfixData,
      .getExpressionData = (GetExpressionData) getOperationPostfixExpressionData,
    },
    (SyntaxNodeHandler) {
      .id = SYNTAX_OPERATION_LR,
      .name = "operation-lr",
      .is_void_expression = false,
      .printData = (PrintData) printSyntaxOperationLRData,
      .getExpressionData = (GetExpressionData) getOperationLRExpressionData,
    },
    (SyntaxNodeHandler) {
      .id = SYNTAX_INITIALIZATION,
      .name = "initialization",
      .is_void_expression = false,
      .printData = (PrintData) printSyntaxInitializationData,
      .getExpressionData = (GetExpressionData) getInitializationExpressionData,
    },
    (SyntaxNodeHandler) {
      .id = SYNTAX_LITERAL,
      .name = "literal",
      .is_void_expression = false,
      .printData = (PrintData) printSyntaxLiteralData,
      .getExpressionData = (GetExpressionData) getLiteralExpressionData,
    },
    (SyntaxNodeHandler) {
      .id = SYNTAX_IDENTIFIER,
      .name = "identifier",
      .is_void_expression = false,
      .printData = (PrintData) printSyntaxIdentifierData,
      .getExpressionData = (GetExpressionData) getIdentifierExpressionData,
    },
    (SyntaxNodeHandler) {
      .id = SYNTAX_FUNCTION,
      .name = "function",
      .is_void_expression = false,
      .printData = (PrintData) printSyntaxFunctionData,
      .getExpressionData = (GetExpressionData) getFunctionExpressionData,
    },
    (SyntaxNodeHandler) {
      .id = SYNTAX_RETURN,
      .name = "return",
      .is_void_expression = true,
      .printData = (PrintData) printSyntaxReturnData,
      .getExpressionData = (GetExpressionData) getReturnExpressionData,
    },
    (SyntaxNodeHandler) {
      .id = SYNTAX_TYPE_DEFINITION,
      .name = "type_definition",
      .is_void_expression = true,
      .printData = (PrintData) printSyntaxTypeDefinitionData,
      .getExpressionData = (GetExpressionData) getNotImplementedExpressionData,
    },
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
