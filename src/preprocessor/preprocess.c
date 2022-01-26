#include <stdio.h>
#include <stdlib.h>

#include "syntax-tree/syntax-helpers.h"
#include "token/tokens.h"
#include "utils/logger/log-src-error.h"
#include "utils/string/string.h"
#include "utils/array/array.h"
#include "utils/map/map.h"

#include "./preprocessor.h"

typedef struct {
  Map *includes;
  Config config;
} PreprocessorContext;

typedef struct {
  bool is_fully_processed;
} IncludeData;

static char* resolvePath(const char *dir, const char *file) {
  char *root_dir_path = realpath(dir, NULL);
  char *full_file_path;
  asprintf(&full_file_path, "%s/%s", root_dir_path, file);
  free(root_dir_path);
  return full_file_path;
}

static TokenizeResult preprocessFileWithContext(PreprocessorContext ctx, const char *path);

static void includeFile(PreprocessorContext ctx, List *include_first_token, List *include_last_token) {
  TokenData *path_token_data = listGetValue(include_last_token);
  char *path;
  parseString(path_token_data->value, &path);

  TokenizeResult result = preprocessFileWithContext(ctx, resolvePath(ctx.config.root_dir, path)); 
  listSetNext(listPrev(include_first_token), result.first_token);
  listSetPrev(listNext(include_last_token), result.last_token);
  
}

static void parseIncludes(PreprocessorContext ctx, List *first_token, List *last_token) {
  List *current_token = first_token;

  while (current_token != NULL) {
    current_token = trimTokensLeftHard(current_token);
    char *error = NULL;

    if (current_token == NULL) {
      break;
    }

    List *include_start_token = current_token;
    current_token = chopToken(current_token, TOKEN_KEYWORD, "include", &error);

    if (error == NULL) {
      List *path_token = trimTokensLeft(current_token);
      if (path_token == NULL) {
        throwSourceError("expected file path, found end of file", current_token);
      }
      current_token = path_token;

      List *after_path = chopToken(current_token, TOKEN_LITERAL_STRING, NULL, &error);
      if (error != NULL) {
        throwSourceError("unexpected token, expect file path", current_token);
      }

      includeFile(ctx, include_start_token, current_token);
      current_token = after_path;
    }

    current_token = listNext(current_token);
  }
}

static TokenizeResult preprocessFileWithContext(PreprocessorContext ctx, const char *path) {
  FILE *file = fopen(path, "r");

  if (file == NULL) {
    // !TODO print information about include location
    printf("Failed to open file '%s'.\n", path);
    exit(1);
  }

  fseek(file, 0, SEEK_END);
  long length = ftell(file);
  fseek(file, 0, SEEK_SET);


  SourceData *src = malloc(sizeof(SourceData));
  src->path = path;
  src->content = malloc(length+1);

  fread(src->content, 1, length, file);
  fclose(file);
  src->content[length] = 0;
  
  TokenizeResult result = tokenize(src);
  List *token_start = createList(&((TokenData) {
    .col = 0,
    .row = 0,
    .size = 1,
    .src = src,
    .token = *(Token*) arrayAt(getTokens(), TOKEN_SEPARATOR_EXPRESSION),
    .value = "\n",
  }), sizeof(TokenData));

  TokenData *last_token_data = listGetValue(result.last_token);

  List *token_end = createList(&((TokenData) {
    .col = 0,
    .row = last_token_data->row + 1,
    .size = 1,
    .src = src,
    .token = *(Token*) arrayAt(getTokens(), TOKEN_SEPARATOR_EXPRESSION),
    .value = "\n",
  }), sizeof(TokenData));

  listSetNext(token_start, result.first_token);
  result.first_token = token_start;

  listSetPrev(token_end, result.last_token);
  result.last_token = token_end;

  parseIncludes(ctx, result.first_token, result.last_token);

  return result;
}

TokenizeResult preprocessFile(Config config) {
  PreprocessorContext ctx = (PreprocessorContext) {
    .config = config,
    .includes = createMap(sizeof(IncludeData)),
  };

  return preprocessFileWithContext(ctx, resolvePath(config.root_dir, config.entry_point));
}
