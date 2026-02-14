#ifndef LIBMENU_H
#define LIBMENU_H
#include <stdint.h>
#include <stdbool.h>

typedef struct lm_menu {
  char **options;
  char *name;
  char *version;
  char *exit_t;
  bool submenu;
  int options_l;
  int last_selection;
} lm_menu;

// create a menu
lm_menu *lm_domenu(
  char *name,
  char *version,
  char **options,
  int options_l,
  char *exit_t,
  bool submenu
);

// get input from user,
// outputting it to `menu->last_selection`
void lm_input(
  lm_menu *menu,
  bool include_name
);

// print a seperator
void lm_sep();

// clear the screen
void lm_clear();

// avoid using last input,
// making `fgets` useless
void lm_noprevinput();

// print a fancy error
void lm_error(
  char *info,
  ...
);

// print a fancy warning
void lm_warn(
  char *info,
  ...
);

#endif // LIBMENU_H