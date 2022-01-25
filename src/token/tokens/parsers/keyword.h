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
    mapSet(keywords, "if", NULL);
    mapSet(keywords, "else", NULL);
    mapSet(keywords, "while", NULL);
    mapSet(keywords, "include", NULL);
    mapSet(keywords, TYPE_NAME_VOID, NULL);
    mapSet(keywords, TYPE_NAME_STRUCT, NULL);
    mapSet(keywords, TYPE_NAME_INT, NULL);
    mapSet(keywords, TYPE_NAME_FLOAT, NULL);
    mapSet(keywords, TYPE_NAME_CHAR, NULL);
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
