#include <stdlib.h>
#include "token/tokens.h"
#include "./helpers.h"
#include "./identifier.h"
#include "./keyword.h"
#include "./separator.h"
#include "./operator.h"
#include "./literal.h"
#include "./comment.h"

Array *tokens;

Array *getTokens() {
  if (tokens != NULL) {
    return tokens;
  }
  tokens = newArray(Token, 
    createToken(identifier, 0),
    createToken(keyword, 1),
    createToken(separator, 2),
    createToken(operator, 3),
    createToken(literal, 4),
    createToken(comment, 5),
  );

  return tokens;
}
