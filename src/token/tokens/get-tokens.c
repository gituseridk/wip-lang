#include <stdlib.h>
#include "token/tokens.h"
#include "./helpers.h"
#include "./parsers/identifier.h"
#include "./parsers/white-space.h"
#include "./parsers/separator.h"
#include "./parsers/operator.h"
#include "./parsers/literal.h"
#include "./parsers/comment.h"

Array *tokens;

Array *getTokens() {
  if (tokens != NULL) {
    return tokens;
  }
  tokens = newArray(Token, 
    createToken(identifier, 0),
    createToken(white_space, 1),
    createToken(separator, 2),
    createToken(operator, 3),
    createToken(literal, 4),
    createToken(comment, 5),
  );

  return tokens;
}
