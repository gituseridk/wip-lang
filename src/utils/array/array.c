#include <string.h>
#include <stdlib.h>

#include "./array.h"

#define ALLOC_MULT 2

const Array newArray(unsigned length, unsigned el_size, const void *data) {
  unsigned dataSize = el_size * length;
  void *value = malloc(el_size * length);
  memcpy(value, data, dataSize);
  
  return (Array) {
    .el_size = el_size,
    .length = length,
    .allocated = length,
    .value = value,
  };
}
void freeArray(Array *self) {
  self->allocated = 0;
  self->length = 0;
  free(self->value);
}

void* getElementAt(Array *self, unsigned index) {
  if (index >= self->length) {
    return NULL;
  }
  return self->value + (self->el_size * index);
}

const unsigned getArrayLength(const Array *self) {
  return self->length;
}

// !TODO free mem when more than half is unused
void* pop(Array *self) {
  if (self->length == 0) {
    return NULL;
  }
  --self->length;
  return self->value + (self->el_size * self->length);
}

void push(Array *self, void *element) {
  if (self->length < self->allocated) {
    ++self->length;
    memcpy(self->value + (self->length * self->el_size), element, self->el_size);
    return;
  }
  self->value = realloc(self->value, self->el_size * self->length * ALLOC_MULT);
  memcpy(self->value + self->length * self->el_size, element, self->el_size);
  self->allocated = self->length * ALLOC_MULT;
  ++self->length;
}
