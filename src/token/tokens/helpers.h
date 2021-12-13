#define CheckIf(name, token, size) int checkTokenStr_##name(const char *token, int size)
#define createToken(token_name, token_id) ((Token) { \
  .id = token_id, \
  .name = #token_name, \
  .checkTokenStr = checkTokenStr_##token_name \
})
