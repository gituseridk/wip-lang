#include <stdlib.h>
#include "token/tokens.h"
#include "./helpers.h"
#include "./parsers/identifier.h"
#include "./parsers/bracket-open.h"
#include "./parsers/bracket-close.h"
#include "./parsers/function-arrow.h"
#include "./parsers/keyword.h"
#include "./parsers/white-space.h"
#include "./parsers/separator-expression.h"
#include "./parsers/separator.h"
#include "./parsers/operator.h"
#include "./parsers/literal-string.h"
#include "./parsers/literal-float.h"
#include "./parsers/literal-int.h"
#include "./parsers/comment.h"

Array *tokens;

Array *getTokens() {
  if (tokens != NULL) {
    return tokens;
  }
  tokens = newArray(Token, 
    createToken(literal_string, TOKEN_LITERAL_STRING),
    createToken(literal_float, TOKEN_LITERAL_FLOAT),
    createToken(literal_int, TOKEN_LITERAL_INT),
    createToken(function_arrow, TOKEN_FUNCTION_ARROW),
    createToken(bracket_open, TOKEN_BRACKET_OPEN),
    createToken(bracket_close, TOKEN_BRACKET_CLOSE),
    createToken(keyword, TOKEN_KEYWORD),
    createToken(identifier, TOKEN_IDENTIFIER),
    createToken(separator_expression, TOKEN_SEPARATOR_EXPRESSION),
    createToken(white_space, TOKEN_WHITE_SPACE),
    createToken(separator, TOKEN_SEPARATOR),
    createToken(operator, TOKEN_OPERATOR),
    createToken(comment, TOKEN_COMMENT),
  );

  return tokens;
}
