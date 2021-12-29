#include <stdlib.h>
#include <stdio.h>

#include "./handlers/scope/data.h"
#include "./handlers/assignation/data.h"
#include "./handlers/operation-lr/data.h"
#include "./handlers/initialization/data.h"
#include "./handlers/literal/data.h"
#include "./handlers/identifier/data.h"
#include "./handlers/function/data.h"
#include "./handlers/return/data.h"
#include "./handlers/function-call/data.h"
#include "./handlers/type-definition/data.h"

#include "./syntax-node-handler.h"

Array *handlers;

static Array *getSyntaxNodeHandlers() {
  handlers = newArray(
    SyntaxNodeHandler,
    (SyntaxNodeHandler) {
      .id = SYNTAX_SCOPE,
      .name = "scope",
      .printData = (PrintData) printSyntaxScopeData,
    },
    (SyntaxNodeHandler) {
      .id = SYNTAX_FUNCTION_CALL,
      .name = "function-call",
      .printData = (PrintData) printSyntaxFunctionCallData,
    },
    (SyntaxNodeHandler) {
      .id = SYNTAX_ASSIGNATION,
      .name = "assignation",
      .printData = (PrintData) printSyntaxAssignationData,
    },
    (SyntaxNodeHandler) {
      .id = SYNTAX_OPERATION_LR,
      .name = "operation-lr",
      .printData = (PrintData) printSyntaxOperationLRData,
    },
    (SyntaxNodeHandler) {
      .id = SYNTAX_INITIALIZATION,
      .name = "initialization",
      .printData = (PrintData) printSyntaxInitializationData,
    },
    (SyntaxNodeHandler) {
      .id = SYNTAX_LITERAL,
      .name = "literal",
      .printData = (PrintData) printSyntaxLiteralData,
    },
    (SyntaxNodeHandler) {
      .id = SYNTAX_IDENTIFIER,
      .name = "identifier",
      .printData = (PrintData) printSyntaxIdentifierData,
    },
    (SyntaxNodeHandler) {
      .id = SYNTAX_FUNCTION,
      .name = "function",
      .printData = (PrintData) printSyntaxFunctionData,
    },
    (SyntaxNodeHandler) {
      .id = SYNTAX_RETURN,
      .name = "return",
      .printData = (PrintData) printSyntaxReturnData,
    },
    (SyntaxNodeHandler) {
      .id = SYNTAX_TYPE_DEFINITION,
      .name = "type_refinition",
      .printData = (PrintData) printSyntaxTypeDefinitionData,
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
