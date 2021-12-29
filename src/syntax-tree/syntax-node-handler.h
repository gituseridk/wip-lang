#ifndef SYNTAX_NODE_HANDLER_H
#define SYNTAX_NODE_HANDLER_H

#include "utils/array/array.h"

#define SYNTAX_SCOPE            0
#define SYNTAX_FUNCTION_CALL    1
#define SYNTAX_ASSIGNATION      2
#define SYNTAX_OPERATION_LR     3
#define SYNTAX_INITIALIZATION   4
#define SYNTAX_LITERAL          5
#define SYNTAX_IDENTIFIER       6
#define SYNTAX_FUNCTION         7
#define SYNTAX_RETURN           8
#define SYNTAX_TYPE_DEFINITION  9

typedef void (*PrintData)(void *data);

typedef struct {
  int id;
  char *name;
  PrintData printData;
} SyntaxNodeHandler;

SyntaxNodeHandler *getSyntaxNodeHandler(int id);

#endif
