#include <stdio.h>

char *chopSpecialSymbol(char *token_start) {
  char *token_end = token_start;
  if (*token_end != '\\') {
    return NULL;
  }

  ++token_end;
  if (stringContainsChar(SPECIAL_CHARACTERS, *token_end)) {
    return token_end;
  }
  return NULL;
}

ChopToken(literal_string, token_start, error) {
  char *token_end = token_start;

  if (*token_end != '"') {
    return NULL;
  }
  ++token_end;

  while (*token_end != '\0') {
    if (*token_end == '"') {
      return token_end + 1;
    }
    char *special_symbol_end = chopSpecialSymbol(token_end);
    if (special_symbol_end != NULL) {
      token_end = special_symbol_end + 1;
      continue;
    }
    ++token_end;
  }

  *(char**)error = "Missing closing quotes";
  return NULL;
}
