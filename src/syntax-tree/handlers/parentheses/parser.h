#ifndef SYNTAX_PARSER_PARENTHESIS_H
#define SYNTAX_PARSER_PARENTHESIS_H

#include "syntax-tree/syntax-node.h"

List* parseParentheses(List *start_token, SyntaxNode *result, char **error);

#endif
