#define CheckIf(name, token, size) int checkTokenStr_##name(const char *token, int size)
#define createToken(name, token_id) ((Token) { .id = token_id, .checkTokenStr = checkTokenStr_##name })
