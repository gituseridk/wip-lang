#ifndef SYNTAX_HELPERS_H
#define SYNTAX_HELPERS_H

#include "utils/list/list.h"

List *trimTokensLeft(List *start_token);

List *chopExpressionEnd(List *start_token, char **error);

// like trimTokensLeft but trims separator_expression tokens too
List *trimTokensLeftHard(List *start_token);

#endif
