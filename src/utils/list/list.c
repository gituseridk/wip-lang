#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "./list.h"

struct List {
  List *prev;
  List *next;
  void *value;
};

List *createList(void *value, int element_size) {
  List *result = malloc(sizeof(List));
  result->value = malloc(element_size);
  memcpy(result->value, value, element_size);
  result->next = NULL;
  result->prev = NULL;
  return result;
}

void *listGetValue(List *self) {
  return self->value;
}

List *listNext(List *self) {
  return self->next;
}

List *listPrev(List *self) {
  return self->prev;
}

void listSetNext(List *self, List *next) {
  self->next = next;
  next->prev = self;
}

void listSetPrev(List *self, List *prev) {
  self->prev = prev;
  prev->next = self;
}

void listPop(List *self, void *result, int element_size) {
  if (result != NULL) {
    memcpy(result, self->value, element_size);
  }

  if (self->prev != NULL) {
    self->prev->next = self->next;
  }
  if (self->next != NULL) {
    self->next->prev = self->prev;
  }

  free(self->value);
  free(self);
}

List *listPushAfter(List *self, void *value, int element_size) {
  if (self == NULL) {
    return createList(value, element_size);
  }
  List *next = self->next;
  List *newEl = malloc(sizeof(List));
  newEl->prev = self;
  newEl->value = malloc(element_size);
  memcpy(newEl->value, value, element_size);
  newEl->next = next;
  self->next = newEl;
  if (next != NULL) {
    next->prev = newEl;
  }
  return newEl;
}

List *listPushBefore(List *self, void *value, int element_size) {
  if (self == NULL) {
    return createList(value, element_size);
  }
  List *prev = self->prev;
  List *newEl = malloc(sizeof(List));
  newEl->value = malloc(element_size);
  newEl->next = self;
  memcpy(newEl->value, value, element_size);
  newEl->prev = prev;
  self->prev = newEl;
  if (prev != NULL) {
    prev->next = newEl;
  }
  return newEl;
}

List *listFindBegin(List *self) {
  List *result = self->prev;
  if (result == NULL) {
    return self;
  }
  while (result->prev != NULL) {
    result = result->prev;
  }
  return result;
}

List *listFindEnd(List *self) {
  List *result = self->next;
  if (result == NULL) {
    return self;
  }
  while (result->next != NULL) {
    result = result->next;
  }
  return result;
}

void listFree(List *self) {
  List *element = listFindBegin(self);
  while (element != NULL) {
    List *next = element->next;
    listPop(element, NULL, 0);
    element = next;
  }
}
