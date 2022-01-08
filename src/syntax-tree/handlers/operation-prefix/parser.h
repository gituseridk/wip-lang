#ifndef SYNTAX_PARSER_OPERATION_PREFIX_H
#define SYNTAX_PARSER_OPERATION_PREFIX_H

#include "syntax-tree/syntax-node.h"

List *parseOperationPrefix(List *tokens, SyntaxNode *result, char **error);

#endif
