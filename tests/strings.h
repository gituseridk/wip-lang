#include <stdio.h>
#include <assert.h>

#include "utils/string/string.h"

String createTestString() {
  return newString("test string");
}

void testStrings() {
  printf("Test strings:\n");

  printf("\t- create string\n");
  String str = newString("0123456789");

  printf("\t- get string length\n");
  assert(getStringLength(&str) == 10);

  printf("\t- find substring\n");
  assert(findSubstring(&str, newString("456")) == 4);

  printf("\t- try find not existed substring\n");
  assert(findSubstring(&str, newString("654")) == -1);

  printf("\t- check if strings are eq\n");
  assert(isStringsEq(newString("qwerty"), newString("qwerty")));

  printf("\t- check if strings aren't eq\n");
  assert(!isStringsEq(newString("qwerty"), newString("123456")));

  printf("\t- check string from another scope\n");
  assert(isStringsEq(createTestString(), newString("test string")));

  printf("Test strings: OK\n");
}
