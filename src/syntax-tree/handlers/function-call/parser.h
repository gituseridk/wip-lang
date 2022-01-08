#ifndef SYNTAX_PARSER_FUNCTION_CALL_H
#define SYNTAX_PARSER_FUNCTION_CALL_H

#include "syntax-tree/syntax-node.h"

List *parseFunctionCall(List *start_token, SyntaxNode *left, SyntaxNode *result, char **error);

#endif
