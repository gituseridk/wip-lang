#include <stdlib.h>
#include "token/tokens.h"
#include "./helpers.h"
#include "./parsers/identifier.h"
#include "./parsers/keyword.h"
#include "./parsers/white-space.h"
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
    createToken(literal_string, 0),
    createToken(literal_float, 1),
    createToken(literal_int, 2),
    createToken(keyword, 3),
    createToken(identifier, 4),
    createToken(white_space, 5),
    createToken(separator, 6),
    createToken(operator, 7),
    createToken(comment, 8),
  );

  return tokens;
}
