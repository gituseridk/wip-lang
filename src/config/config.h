#ifndef CONFIG_H
#define CONFIG_H

typedef struct {
  const char *root_dir;
  const char *entry_point;
} Config;

Config readConfig(int argc, char **argv);

#endif
