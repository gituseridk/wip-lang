#include <stdlib.h>
#include "token/tokens.h"
#include "./helpers.h"
#include "./parsers/identifier.h"
#include "./parsers/white-space.h"
#include "./parsers/separator.h"
#include "./parsers/operator.h"
#include "./parsers/literal-float.h"
#include "./parsers/literal-int.h"
#include "./parsers/comment.h"

Array *tokens;

Array *getTokens() {
  if (tokens != NULL) {
    return tokens;
  }
  tokens = newArray(Token, 
    createToken(literal_float, 5),
    createToken(literal_int, 5),
    createToken(identifier, 0),
    createToken(white_space, 1),
    createToken(separator, 2),
    createToken(operator, 3),
    createToken(comment, 6),
  );

  return tokens;
}
