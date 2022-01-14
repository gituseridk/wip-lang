#include <stdlib.h>

#include "./expression-data.h"
#include "syntax-tree/handlers/function/data.h"

Map *global_variables;

static void definePrintInt(unsigned *offset) {
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

Map *getGlobalVariables(unsigned *offset) {
  if (global_variables == NULL) {
    global_variables = createMap(sizeof(VariableData));
    definePrintInt(offset);
  }

  return global_variables;
}
