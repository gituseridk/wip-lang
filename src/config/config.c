#include <stdio.h>
#include <stdlib.h>

#include "./config.h"

Config readConfig(int argc, char **argv) {
  if (argc != 2) {
    printf("wrong number of args, expected input file name\n");
    exit(1);
  }

  const char *file_name = argv[1];

  return (Config) {
    .root_dir = file_name,
    .entry_point = "./main.wip",
  };
}
