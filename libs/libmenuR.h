#ifndef LIBMENUR_H
#define LIBMENUR_H
#include <stdint.h>
#include <stdbool.h>

typedef struct {
  char *name;
  char *version;
  char **options;
  uint8_t options_l;
  uint8_t last_selection;
  char *exit_t;
  bool submenu;
} lm_menu;

lm_menu *make_menu(
  char* name,
  char* version,
  char** options,
  uint8_t options_l,
  char* exit_t,
  bool submenu
);

void get_input(
  lm_menu *menu,
  bool include_name
);

void unmake_menu(
  lm_menu *menu
);

void sep();
void clear();
void ignore_previous_input();

void error(
  char *info,
  ...
);

void warning(
  char *info,
  ...
);

#endif // LIBMENUR_H