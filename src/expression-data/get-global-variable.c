#include <stdlib.h>

#include "./expression-data.h"
#include "syntax-tree/handlers/function/data.h"

#define PRINT_NAME "print"

Map *global_variables;

static void definePrint() {

  FunctionTypeData *type_data = malloc(sizeof(FunctionTypeData));

  type_data->args = newArray(
    VariableData,
    (VariableData) {
      .name = "value",
      .scope_offset = 0,
      .type = (TypeDefinition) {
        .type_id = TYPE_ID_INT,
        .data = NULL,
        .is_constant = true,
      },
    },
  );
  setVoidType(&(type_data->result_type));

  mapSet(global_variables, PRINT_NAME, &(VariableData) {
    .name = PRINT_NAME,
    .scope_offset = 0,
    .type = (TypeDefinition) {
      .data = type_data,
      .is_constant = true,
      .type_id = TYPE_ID_FUNCTION,
    },
  });
}

VariableData *getGlobalVariable(char *name) {
  if (global_variables == NULL) {
    global_variables = createMap(sizeof(VariableData));
    definePrint();
  }

  return mapGet(global_variables, name);
}
