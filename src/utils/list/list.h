#ifndef LIST_H
#define LIST_H

typedef struct List List;

List *createList(void *value, int element_size);

void *listGetValue(List *self);

List *listNext(List *self);
List *listPrev(List *self);

void listSetNext(List *self, List *next);
void listSetPrev(List *self, List *prev);

void listPop(List *self, void *result, int element_size);

List *listPushAfter(List *self, void *value, int element_size);
List *listPushBefore(List *self, void *value, int element_size);

List *listFindBegin(List *self);
List *listFindEnd(List *self);

void listFree(List *self);

#endif
