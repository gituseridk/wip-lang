#include <stdlib.h>

#include "./expression-data.h"
#include "syntax-tree/handlers/function/data.h"
#include "type-definition/pointer/data.h"

Map *global_variables;

static void definePrint(int *offset) {
  FunctionTypeData *type_data = malloc(sizeof(FunctionTypeData));

  TypePointerData *string_data = malloc(sizeof(TypePointerData));
  string_data->type = (TypeDefinition) {
    .type_id = TYPE_ID_CHAR,
    .is_constant = true,
    .data = NULL,
  };

  string_data->size = 1;
  
  type_data->args = newArray(
    VariableData,
    (VariableData) {
      .scope = NULL,
      .name = "value",
      .scope_offset = 0,
      .type = (TypeDefinition) {
        .type_id = TYPE_ID_POINTER,
        .data = string_data,
        .is_constant = true,
      },
    },
  );
  type_data->label = GLOBAL_VAR_NAME_PRINT;
  setVoidType(&(type_data->result_type));

  TypeDefinition type_def = (TypeDefinition) {
    .data = type_data,
    .is_constant = true,
    .type_id = TYPE_ID_FUNCTION,
  };

  mapSet(global_variables, GLOBAL_VAR_NAME_PRINT, &(VariableData) {
    .scope = NULL,
    .name = GLOBAL_VAR_NAME_PRINT,
    .scope_offset = *offset,
    .type = type_def,
  });

  *offset += getTypeSize(&type_def);
}

static void defineAllocateInt(int *offset) {
  FunctionTypeData *type_data = malloc(sizeof(FunctionTypeData));

  type_data->args = newArray(
    VariableData,
    (VariableData) {
      .scope = NULL,
      .name = "value",
      .scope_offset = 0,
      .type = (TypeDefinition) {
        .type_id = TYPE_ID_INT,
        .data = NULL,
        .is_constant = true,
      },
    },
  );
  type_data->label = GLOBAL_VAR_NAME_ALLOCATE_INT;

  TypePointerData *result_ptr_data = malloc(sizeof(TypePointerData));
  result_ptr_data->type = (TypeDefinition) {
    .type_id = TYPE_ID_INT,
    .is_constant = false,
    .data = NULL,
  };

  type_data->result_type = (TypeDefinition) {
    .type_id = TYPE_ID_POINTER,
    .is_constant = true,
    .data = result_ptr_data,
  };

  TypeDefinition type_def = (TypeDefinition) {
    .data = type_data,
    .is_constant = true,
    .type_id = TYPE_ID_FUNCTION,
  };

  mapSet(global_variables, GLOBAL_VAR_NAME_ALLOCATE_INT, &(VariableData) {
    .scope = NULL,
    .name = GLOBAL_VAR_NAME_ALLOCATE_INT,
    .scope_offset = *offset,
    .type = type_def,
  });

  *offset += getTypeSize(&type_def);
}

static void definePrintInt(int *offset) {
  FunctionTypeData *type_data = malloc(sizeof(FunctionTypeData));

  type_data->args = newArray(
    VariableData,
    (VariableData) {
      .scope = NULL,
      .name = "value",
      .scope_offset = 0,
      .type = (TypeDefinition) {
        .type_id = TYPE_ID_INT,
        .data = NULL,
        .is_constant = true,
      },
    },
  );
  type_data->label = GLOBAL_VAR_NAME_PRINT_INT;
  setVoidType(&(type_data->result_type));

  TypeDefinition type_def = (TypeDefinition) {
    .data = type_data,
    .is_constant = true,
    .type_id = TYPE_ID_FUNCTION,
  };

  mapSet(global_variables, GLOBAL_VAR_NAME_PRINT_INT, &(VariableData) {
    .scope = NULL,
    .name = GLOBAL_VAR_NAME_PRINT_INT,
    .scope_offset = *offset,
    .type = type_def,
  });

  *offset += getTypeSize(&type_def);
}

Map *getGlobalVariables(int *offset) {
  if (global_variables == NULL) {
    global_variables = createMap(sizeof(VariableData));
    definePrint(offset);
    definePrintInt(offset);
    defineAllocateInt(offset);
  }

  return global_variables;
}
