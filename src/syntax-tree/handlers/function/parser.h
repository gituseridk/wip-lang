#ifndef SYNTAX_PARSER_FUNCTION_H
#define SYNTAX_PARSER_FUNCTION_H

#include "syntax-tree/syntax-node.h"

List *parseFunction(List *tokens, SyntaxNode *result, char **error);

#endif
