#include "utils/string/string.h"

bool checkIfLetterOrDigit(char c) {
  return stringContainsChar(UPPER_CASE_LETTERS, c) ||
         stringContainsChar(LOWER_CASE_LETTERS, c) ||
         stringContainsChar(ZERO_DIGIT, c) ||
         stringContainsChar(NOT_ZERO_DIGITS, c);
}

ChopToken(identifier, token_start) {
  if (!stringContainsChar(UPPER_CASE_LETTERS, *token_start) && !stringContainsChar(LOWER_CASE_LETTERS, *token_start)) {
    return NULL;
  }

  char *token_end = token_start + 1;
  while (checkIfLetterOrDigit(*token_end)) ++token_end;

  return token_end;
}
