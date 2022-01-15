#include "compile.h"
#include "compile-utils.h"
#include "expression-data/expression-data.h"

static void defineExit(FILE *out_stream) {
  L("\n\nexit:");
  L("    mov     rbx, rax");
  L("    mov     rax, 1");
  L("    int     80h");
}

// pop pointer from the stack, mesure str length ant push it to the stack
// effects rax and 
static void defineStrLen(FILE *out_stream) {
  L("\n\n%s:", GLOBAL_VAR_NAME_STR_LEN);

  L("    push    rbp");
  L("    mov     rbp, rsp");

  // pop first arg(pointer to the string) from the stack
  L("    mov     rax, QWORD [rbp + 16]");
  // copy string pointer
  L("    mov     rbx, rax");

  // itterate through string until \0 char
  L("strlen_compare_char:");
  L("    cmp     BYTE [rax], 0");
  // if \0 go to strlen_finish
  L("    jz      strlen_finish");
  L("    inc     rax");
  L("    jmp     strlen_compare_char");

  L("strlen_finish:");
  L("    sub     rax, rbx");

  L("    mov     rsp, rbp");
  L("    pop     rbp");

  L("    ret");
}

static void definePrint(FILE *out_stream) {
  L("\n\n%s:", GLOBAL_VAR_NAME_PRINT);

  L("    push    rbp");
  L("    mov     rbp, rsp");

  L("    push    QWORD [rbp + 16]");
  L("    call    %s", GLOBAL_VAR_NAME_STR_LEN);
  L("    mov     rdx, rax");

  L("    mov     rsi, QWORD [rbp + 16]");
  L("    mov     rax, 1");
  L("    mov     rdi, 1");  
  L("    syscall");

  L("    mov     rsp, rbp");
  L("    pop     rbp");

  L("    ret");
}

void defineIntToStr(FILE *out_stream) {
  L("\n\ndec_length:");
  L("    push    rax");
  L("    push    rdx");
  L("    xor     rbx, rbx");
  L("dec_lengt_iteration:");
  L("    inc     rbx");
  L("    xor     rdx, rdx");
  L("    mov     rcx, 10");
  L("    div     rcx");
  L("    cmp     rax, 0");
  L("    jne     dec_lengt_iteration");
  L("    pop     rdx");
  L("    pop     rax");
  L("    ret");
  
  // helper func to convert unsigned int
  L("\n\nuint_to_str:");
  L("    push    rdx");
  L("    push    rcx");
  L("    push    rbx");
  L("    push    rax");
  L("    push    r8");
  L("    push    rbx");
  L("    call    dec_length");
  L("    mov     r8, rbx");
  L("    pop     rbx");
  L("    add     rbx, r8");
  L("    mov     byte [rbx], 0");
  L("uint_to_str_iteration:");
  L("    dec     rbx");

  L("    xor     rdx, rdx");
  L("    mov     rcx, 10");
  L("    div     rcx");

  L("    add     dl, 48");
  L("    mov     byte [rbx], dl");
  
  L("    cmp     rax, 0");
  L("    jne     uint_to_str_iteration");

  L("    pop     r8");
  L("    pop     rax");
  L("    pop     rbx");
  L("    pop     rcx");
  L("    pop     rdx");
  L("    ret");


  L("\n\n%s:", GLOBAL_VAR_NAME_INT_TO_STR);

  L("    push    rbp");
  L("    mov     rbp, rsp");

  // pop first arg (int to convert)
  L("    mov     rax, QWORD [rbp + 16]");

  // pop second arg (result string ptr)
  L("    mov     rbx, QWORD [rbp + 24]");

  L("    cmp     rax, 0");
  L("    jge     int_to_str_uint");

  L("    neg     rax");
  L("    mov     byte [rbx], 45");
  L("    inc     rbx");

  L("int_to_str_uint:");
  L("    call    uint_to_str");


  L("    mov     rsp, rbp");
  L("    pop     rbp");

  L("    ret");
}

void definePrintInt(FILE *out_stream) {
  L("\n\n%s:", GLOBAL_VAR_NAME_PRINT_INT);

  L("    push    rbp");
  L("    mov     rbp, rsp");
  L("    mov     rax, QWORD [rbp + 16]");


  L("    sub     rsp, 32");
  L("    mov     rbx, rsp");

  L("    push    rbx");
  L("    push    rax");
  L("    call    %s", GLOBAL_VAR_NAME_INT_TO_STR);

  L("    push    rbx");
  L("    call    %s", GLOBAL_VAR_NAME_PRINT);

  // !TODO remove later
  // new line after number
  L("    push    0Ah");
  L("    mov     rax, rsp")
  L("    push    rax");
  L("    call    %s", GLOBAL_VAR_NAME_PRINT);

  L("    mov     rsp, rbp");
  L("    pop     rbp");

  L("    ret");
}

void compileX86(char *src, ExpressionData root_expression, FILE *out_stream) {
  L("section .text");
  L("global _start\n");
  L("_start:");

  expressionCompile(&root_expression, ARCH_X86, src, false, out_stream);

  defineExit(out_stream);
  defineStrLen(out_stream);
  definePrint(out_stream);
  defineIntToStr(out_stream);
  definePrintInt(out_stream);
}
