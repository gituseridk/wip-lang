#include <stdlib.h>

#include "syntax-tree/syntax-node.h"
#include "utils/map/map.h"

static Map *keywords;
static Map *getKeywords() {
  if (keywords == NULL) {
    // map with element-size = 0 - essentially is a set of strings
    keywords = createMap(0);
    mapSet(keywords, "const", NULL);
    mapSet(keywords, "var", NULL);
    mapSet(keywords, "return", NULL);
    mapSet(keywords, SYNTAX_TYPE_VOID_NAME, NULL);
    mapSet(keywords, SYNTAX_TYPE_STRUCT_NAME, NULL);
    mapSet(keywords, SYNTAX_TYPE_INT_NAME, NULL);
    mapSet(keywords, SYNTAX_TYPE_FLOAT_NAME, NULL);
    mapSet(keywords, SYNTAX_TYPE_CHAR_NAME, NULL);
  }
  return keywords;
}

ChopToken(keyword, token_start, error) {
  int token_size = mapGetFirstPrefixKeySize(getKeywords(), token_start);
  if (token_size == 0) {
    return NULL;
  }

  if (checkIfLetterOrDigit(token_start[token_size])) {
    return NULL;
  }

  return token_start + token_size;
}
