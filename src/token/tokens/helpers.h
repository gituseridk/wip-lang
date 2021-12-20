#define ChopToken(name, token_start, error) char* chopToken_##name(char *token_start, char **error)

#define DefineChopSimpleToken(name, token_value) ChopToken(name, token_start, error) { \
  return stringComparePrefix(token_start, token_value) ? NULL : token_start + strlen(token_value); \
}

#define createToken(token_name, token_id) ((Token) { \
  .id = token_id, \
  .name = #token_name, \
  .chopToken = chopToken_##token_name \
})

#define LOWER_CASE_LETTERS "abcdefghijklmnopqrstuvwxyz"
#define UPPER_CASE_LETTERS "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define NOT_ZERO_DIGITS "123456789"
#define ZERO_DIGIT "0"
#define OPERATIONS "+-*/"
#define SEPARATORS_EXPRESSION ";\n"
#define SEPARATORS ".,:"
#define OPEN_BRACKETS "([{"
#define CLOSE_BRACKETS ")]}"

#define SPECIAL_CHARACTERS "ntvbrfa\\?\"0"

bool checkIfLetterOrDigit(char c) {
  return stringContainsChar(UPPER_CASE_LETTERS, c) ||
         stringContainsChar(LOWER_CASE_LETTERS, c) ||
         stringContainsChar(ZERO_DIGIT, c) ||
         stringContainsChar(NOT_ZERO_DIGITS, c);
}
