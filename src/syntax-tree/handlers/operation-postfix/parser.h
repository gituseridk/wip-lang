#ifndef SYNTAX_PARSER_OPERATION_POSTFIX_H
#define SYNTAX_PARSER_OPERATION_POSTFIX_H

#include "syntax-tree/syntax-node.h"

List *parseOperationPostfix(List *tokens, SyntaxNode *left, SyntaxNode *result, char **error);

#endif
