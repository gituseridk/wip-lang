#include "../data.h"
#include "utils/logger/log-src-error.h"
#include "compiler/x86/compile-utils.h"


static void compileIncDec(
  char *src,
  ExpressionData *self,
  ExpressionData *target,
  bool dec,
  bool address,
  FILE *out_stream
) {
  char err[100];
  switch (self->result_type.type_id) {
  case TYPE_ID_INT:
    expressionCompile(target, ARCH_X86, src, true, out_stream);

    L("    pop     rax");
    L("    %s     QWORD [rax]", dec ? "dec" : "inc");
    if (address) {
      L("    push    rax");
    } else {
      L("    push    QWORD [rax]");
    }
    return;

  case TYPE_ID_POINTER:
    expressionCompile(target, ARCH_X86, src, true, out_stream);

    L("    pop     rax");
    L("    %s     QWORD [rax], %d", dec ? "sub" : "add", TYPE_SIZE_POINTER);
    if (address) {
      L("    push    rax");
    } else {
      L("    push    QWORD [rax]");
    }
    return;

  default:
    sprintf(
      err,
      "%s for %s type is not implemented yet",
      dec ? "dec" : "inc",
      getTypeName(&(self->result_type))
    );
    throwSourceError(src, err, self->token);
  }
}

static void compileDereference(
  char *src,
  ExpressionData *self,
  ExpressionData *target,
  bool address,
  FILE *out_stream
) {
  char err[100];
  switch (self->result_type.type_id) {
  case TYPE_ID_INT:
    expressionCompile(target, ARCH_X86, src, false, out_stream);

    if (address) {
      return;
    }

    L("    pop     rax");
    L("    push    QWORD [rax]");

    return;
  default:
    sprintf(
      err,
      "dereferencing for %s type is not implemented yet",
      getTypeName(&(self->result_type))
    );
    throwSourceError(src, err, self->token);
  }
}

static void compileNegotation(
  char *src,
  ExpressionData *self,
  ExpressionData *target,
  bool address,
  FILE *out_stream
) {
  FORBID_ADDRESS_AS_RESULT

  char err[100];
  switch (self->result_type.type_id) {
  case TYPE_ID_INT:
    expressionCompile(target, ARCH_X86, src, false, out_stream);

    L("    pop     rax");
    L("    cmp     rax, 0");
    L("    sete    al");
    L("    movzx   rax, al");
    L("    push    rax");

    return;
  default:
    sprintf(
      err,
      "negotation for %s type is not implemented yet",
      getTypeName(&(self->result_type))
    );
    throwSourceError(src, err, self->token);
  }
}

void compileOperationPrefixX86(char *src, ExpressionData *self, bool address, FILE *out_stream) {
  ExpressionData *target = (ExpressionData*) arrayAt(self->child_expressions, 0);

  switch (self->id - EXPRESSION_OPERATIONS_PREFIX) {
  case OPERATION_PREFIX_ID_INC:
    compileIncDec(src, self, target, false, address, out_stream);
    return;
  case OPERATION_PREFIX_ID_DEC:
    compileIncDec(src, self, target, true, address, out_stream);
    return;
  case OPERATION_PREFIX_ID_DEREFERENCING:
    compileDereference(src, self, target, address, out_stream);
    return;
  case OPERATION_PREFIX_ID_NEGOTATION:
    compileNegotation(src, self, target, address, out_stream);
    return;
  
  default:
    throwSourceError(src, "this prefix expression is not supported yet", self->token);
  }
}
