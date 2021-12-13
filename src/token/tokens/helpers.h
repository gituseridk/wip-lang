#define ChopToken(name, token_start, error) char* chopToken_##name(char *token_start, char **error)
#define createToken(token_name, token_id) ((Token) { \
  .id = token_id, \
  .name = #token_name, \
  .chopToken = chopToken_##token_name \
})

#define LOWER_CASE_LETTERS "abcdefghijklmnopqrstuvwxyz"
#define UPPER_CASE_LETTERS "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define NOT_ZERO_DIGITS "123456789"
#define ZERO_DIGIT "0"
#define OPERATORS "+-*/="
#define SEPARATORS ".,;"

#define SPECIAL_CHARACTERS "ntvbrfa\\?\"0"
