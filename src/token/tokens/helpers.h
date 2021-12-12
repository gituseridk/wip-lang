#define CheckIf(name, token) bool checkIfTokenIs_##name(const char *token)
#define createToken(name, token_id) ((Token) {.id=token_id, .testString=checkIfTokenIs_##name})
