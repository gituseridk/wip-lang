#include <stdlib.h>

#include "token/tokens.h"
#include "utils/string/string.h"

#include "./helpers.h"
#include "./parsers/identifier.h"
#include "./parsers/bracket-open.h"
#include "./parsers/bracket-close.h"
#include "./parsers/function-arrow.h"
#include "./parsers/keyword.h"
#include "./parsers/white-space.h"
#include "./parsers/separator-expression.h"
#include "./parsers/separator.h"
#include "./parsers/operators.h"
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
    createToken(comment, TOKEN_COMMENT),
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

    createToken(operator_not_equals_strict, TOKEN_OPERATOR_NOT_EQUALS_STRICT),
    createToken(operator_equals_strict, TOKEN_OPERATOR_EQUALS_STRICT),
    createToken(operator_not_equals, TOKEN_OPERATOR_NOT_EQUALS),
    createToken(operator_equals, TOKEN_OPERATOR_EQUALS),
    createToken(operator_greater_or_equal, TOKEN_OPERATOR_GRATER_OR_EQUAL),
    createToken(operator_less_or_equal, TOKEN_OPERATOR_LESS_OR_EQUAL),
    createToken(operator_greater, TOKEN_OPERATOR_GRATER),
    createToken(operator_less, TOKEN_OPERATOR_LESS),
    createToken(operator_or, TOKEN_OPERATOR_OR),
    createToken(operator_and, TOKEN_OPERATOR_AND),
    createToken(operator_inc, TOKEN_OPERATOR_INC),
    createToken(operator_dec, TOKEN_OPERATOR_DEC),
    createToken(operator_not, TOKEN_OPERATOR_NOT),
    createToken(operator_assignation, TOKEN_OPERATOR_ASSIGNATION),
    createToken(operator_sum, TOKEN_OPERATOR_SUM),
    createToken(operator_difference, TOKEN_OPERATOR_DIFFERENCE),
    createToken(operator_product, TOKEN_OPERATOR_PRODUCT),
    createToken(operator_ratio, TOKEN_OPERATOR_RATIO),
    createToken(operator_bit_or, TOKEN_OPERATOR_BIT_OR),
    createToken(operator_bit_and, TOKEN_OPERATOR_BIT_AND),
  );

  return tokens;
}
