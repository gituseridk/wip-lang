#ifndef SYNTAX_PARSER_TYPE_DEFINITION_H
#define SYNTAX_PARSER_TYPE_DEFINITION_H

#include "syntax-tree/syntax-node.h"

List* parseTypeDefinition(List *tokens, SyntaxNode *result, char **error);

#endif
