#define CheckIf(name, token, size) bool checkIfTokenIs_##name(const char *token, int size)
#define createToken(name, token_id) ((Token) {.id=token_id, .testString=checkIfTokenIs_##name})
