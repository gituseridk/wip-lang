#include <stdlib.h>

#include "utils/map/map.h"

static Map *keywords;
static Map *getKeywords() {
  if (keywords == NULL) {
    keywords = createMap(0);
    mapSet(keywords, "const", NULL);
    mapSet(keywords, "var", NULL);
  }
  return keywords;
}

ChopToken(keyword, token_start, error) {
  char *token_end = token_start;

  int token_size = mapGetFirstPrefixKeySize(getKeywords(), token_start);
  if (token_size == 0) {
    return NULL;
  }

  return token_start + token_size;
}
