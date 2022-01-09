#ifndef TYPE_DEFINITION_H
#define TYPE_DEFINITION_H

#include <stdbool.h>

#define TYPE_SIZE_VOID            0
#define TYPE_ID_VOID              0
#define TYPE_NAME_VOID            "void"

#define TYPE_SIZE_INT             8
#define TYPE_ID_INT               1
#define TYPE_NAME_INT             "int"

#define TYPE_SIZE_FLOAT           8
#define TYPE_ID_FLOAT             2
#define TYPE_NAME_FLOAT           "float"

#define TYPE_SIZE_CHAR            1
#define TYPE_ID_CHAR              3
#define TYPE_NAME_CHAR            "char"

#define COMPLEX_TYPES_START_ID    4 

#define TYPE_SIZE_POINTER         8
#define TYPE_ID_POINTER           4
#define TYPE_NAME_POINTER         "pointer"

#define TYPE_SIZE_FUNCTION        TYPE_SIZE_POINTER
#define TYPE_ID_FUNCTION          5
#define TYPE_NAME_FUNCTION        "function"

#define TYPE_ID_STRUCT            6
#define TYPE_NAME_STRUCT          "struct"

typedef struct {
  int type_id;
  void *data;
  bool is_constant;
} TypeDefinition;

bool isSameType(const TypeDefinition *left, const TypeDefinition *right);
unsigned getTypeSize(const TypeDefinition *type, char **error);
bool isBool(const TypeDefinition *type);
char *getTypeName(const TypeDefinition *type);
void printTypeDefinition(const TypeDefinition *type);
void setVoidType(TypeDefinition *type);

#endif
