#include <stdlib.h>

#include "utils/map/map.h"

static Map *keywords;
static Map *getKeywords() {
  if (keywords == NULL) {
    // map with element-size = 0 - essentially is a set of strings
    keywords = createMap(0);
    mapSet(keywords, "const", NULL);
    mapSet(keywords, "var", NULL);
    mapSet(keywords, "float", NULL);
    mapSet(keywords, "int", NULL);
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
