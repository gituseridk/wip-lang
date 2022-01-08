#ifndef SYNTAX_PARSER_OPERATION_H
#define SYNTAX_PARSER_OPERATION_H

#include "syntax-tree/syntax-node.h"

List *parseOperation(List *tokens, SyntaxNode *left, SyntaxNode *result, char **error);

#endif
