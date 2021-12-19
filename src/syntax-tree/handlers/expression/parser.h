#ifndef SYNTAX_PARSER_EXPRESSION_H
#define SYNTAX_PARSER_EXPRESSION_H

#include "syntax-tree/syntax-node.h"

typedef List* (*ChopExpression)(List *first_token, SyntaxNode *result, char **error);
List *parseExpression(List *tokens, SyntaxNode *result, char **error, bool without_operation);

#endif
