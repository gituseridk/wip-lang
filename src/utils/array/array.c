#include <string.h>
#include <stdlib.h>

#include "./array.h"

Array newArray(unsigned length, unsigned el_size, void *data) {
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
  free(self->value);
}

void* getElementAt(Array *self, unsigned index) {
  if (index >= self->length) {
    return NULL;
  }
  return self->value + (self->el_size * index);
}

unsigned getArrayLength(Array *self) {
  return self->length;
}

void* pop(Array *self) {
  if (self->length == 0) {
    return NULL;
  }
  --self->length;
  return getElementAt(self, self->length);
}

void push(Array *self, void *element) {
  if (self->length < self->allocated) {
    ++self->length;
    memcpy(self->value + (self->length * self->el_size), element, self->el_size);
  }
}
