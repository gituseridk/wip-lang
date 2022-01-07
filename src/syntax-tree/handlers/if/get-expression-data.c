#include "utils/logger/log-src-error.h"
#include "../initialization/data.h"
#include "./data.h"

void getIfExpressionData(
  const char *src,
  void *raw_data,
  List *token,
  ExpressionData *result,
  unsigned *offset,
  int handler_id
) {
  throwSourceError(src, "if is not suppurted yet", token);
}
