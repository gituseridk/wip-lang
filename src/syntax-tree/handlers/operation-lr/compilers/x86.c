#include "../data.h"
#include "utils/logger/log-src-error.h"
#include "compiler/x86/compile-utils.h"

static void compileSum(
  ExpressionData *self,
  ExpressionData *left,
  ExpressionData *right,
  bool difference,
  FILE *out_stream
) {
  expressionCompile(left, ARCH_X86, false, out_stream);
  expressionCompile(right, ARCH_X86, false, out_stream);

  char err[100];
  switch (self->result_type.type_id) {
  case TYPE_ID_INT: {
    L("    pop     rbx");
    L("    pop     rax");
    L("    %s     rax, rbx", difference ? "sub" : "add");
    L("    push    rax");
    break;
  }
  case TYPE_ID_POINTER: {
    unsigned type_size = getTypeSize(&(left->result_type));

    L("    pop     rax");
    L("    mov     rbx, %d", type_size);
    L("    mul     rbx");

    L("    pop     rbx");
    
    L("    %s     rbx, rax", difference ? "sub" : "add");
    L("    push    rbx");

    return;
  }
  default:
    sprintf(
      err,
      "%s for %s type is not implemented yet",
      difference ? "diff" : "sum",
      getTypeName(&(self->result_type))
    );
    throwSourceError(err, self->token);
  }
}

static void compileProduct(
  ExpressionData *self,
  ExpressionData *left,
  ExpressionData *right,
  FILE *out_stream
) {
  char err[100];
  switch (self->result_type.type_id) {
  case TYPE_ID_INT:
    expressionCompile(left, ARCH_X86, false, out_stream);
    expressionCompile(right, ARCH_X86, false, out_stream);

    L("    pop     rax");
    L("    pop     rdx");
    L("    mul     rdx");
    L("    push    rax");

    return;
  default:
    sprintf(
      err,
      "product for %s type is not implemented yet",
      getTypeName(&(self->result_type))
    );
    throwSourceError(err, self->token);
  }
}

static void compileCmp(
  ExpressionData *self,
  ExpressionData *left,
  ExpressionData *right,
  char *instruction,
  FILE *out_stream
) {
  char err[100];
  switch (self->result_type.type_id) {
  case TYPE_ID_INT:
    expressionCompile(left, ARCH_X86, false, out_stream);
    expressionCompile(right, ARCH_X86, false, out_stream);

    L("    pop     rbx");
    L("    pop     rax");

    L("    cmp     rax, rbx");
    L("    %s    al", instruction);
    L("    movzx   rax, al");
    
    L("    push    rax");

    return;
  default:
    sprintf(
      err,
      "cmp operations for %s type is not implemented yet",
      getTypeName(&(self->result_type))
    );
    throwSourceError(err, self->token);
  }
}

int logical_last_id = 0;

static void compileLogical(
  ExpressionData *self,
  ExpressionData *left,
  ExpressionData *right,
  bool or,
  FILE *out_stream
) {
  int operation_id = logical_last_id++;

  char err[100];
  switch (self->result_type.type_id) {
  case TYPE_ID_INT:
    expressionCompile(left, ARCH_X86, false, out_stream);

    L("    pop     rax");
    L("    cmp     rax, 0");
    L("    %s     logical_op_%d", or ? "jne" : "je ", operation_id);

    expressionCompile(right, ARCH_X86, false, out_stream);

    L("    pop     rax");
    L("    cmp     rax, 0");
    L("    %s     logical_op_%d", or ? "jne" : "je ", operation_id);

    L("    push    %d", or ? 0 : 1);
    L("    jmp     logical_op_end_%d", operation_id);

    L("logical_op_%d:", operation_id);
    L("    push    %d", or ? 1 : 0);

    L("logical_op_end_%d:", operation_id);

    return;
  default:
    sprintf(
      err,
      "cmp operations for %s type is not implemented yet",
      getTypeName(&(self->result_type))
    );
    throwSourceError(err, self->token);
  }
}

void compileOperationLRX86(ExpressionData *self, bool address, FILE *out_stream) {
  FORBID_ADDRESS_AS_RESULT

  ExpressionData *left = (ExpressionData*) arrayAt(self->child_expressions, 0);
  ExpressionData *right = (ExpressionData*) arrayAt(self->child_expressions, 1);

  switch (self->id - EXPRESSION_OPERATIONS) {
  case OPERATION_ID_SUM:
    compileSum(self, left, right, false, out_stream);
    return;
  case OPERATION_ID_DIFFERENCE:
    compileSum(self, left, right, true, out_stream);
    return;
  case OPERATION_ID_PRODUCT:
    compileProduct(self, left, right, out_stream);
    return;

  case OPERATION_ID_LESS:
    compileCmp(self, left, right, "setl", out_stream);
    return;
  case OPERATION_ID_GRATER:
    compileCmp(self, left, right, "setg", out_stream);
    return;
  case OPERATION_ID_LESS_OR_EQUAL:
    compileCmp(self, left, right, "setle", out_stream);
    return;
  case OPERATION_ID_GRATER_OR_EQUAL:
    compileCmp(self, left, right, "setge", out_stream);
    return;
  case OPERATION_ID_EQUALS:
    compileCmp(self, left, right, "sete", out_stream);
    return;
  case OPERATION_ID_NOT_EQUALS:
    compileCmp(self, left, right, "setne", out_stream);
    return;

  case OPERATION_ID_AND:
    compileLogical(self, left, right, false, out_stream);
    return;
  case OPERATION_ID_OR:
    compileLogical(self, left, right, true, out_stream);
    return;
  
  default:
    throwSourceError("this expression is not supported yet", self->token);
  }
}
