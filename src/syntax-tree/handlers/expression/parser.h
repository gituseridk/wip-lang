#ifndef SYNTAX_PARSER_EXPRESSION_H
#define SYNTAX_PARSER_EXPRESSION_H

#include "syntax-tree/syntax-node.h"

typedef List* (*ChopExpression)(List *start_token, SyntaxNode *result, char **error);
typedef List* (*ChopLeftExpression)(List *start_token, SyntaxNode *left, SyntaxNode *result, char **error);

List *parseExpression(List *tokens, SyntaxNode *result, char **error);

#endif
