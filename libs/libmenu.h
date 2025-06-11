#ifndef LIBMENU_H
#define LIBMENU_H
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif
//contains information about a menu
typedef struct menu {
  //menu name
  char* name;
  //menu version
  char* version;
  //menu options
  char** options;
  //number of menu options
  long unsigned optionsN;
  //menu exit text
  char* exitText;
} Menu;
//contains information about a selection menu
typedef struct selmenu {
  //menu action
  char* action;
  //menu options
  char** options;
  //number of menu options
  long unsigned optionsN;
  //menu cancel text
  char* cancelText;
} SelMenu;
//menu configurator
Menu* initMenu(char* name, char* version, char** options, long unsigned optionsN, char* exitText);
//selection menu configurator
SelMenu* initSelMenu(char* action, char** options, long unsigned optionsN, char* exitText);
/*get a formatted string of the name and version of the menu

`int includeVersion`: defines if you want to include `Menu->version`,
useful for submenus
*/
char* getFormattedVersion(Menu* menu, int includeVersion);
/*print a menu, get user input and put it
on `optionInt`
`int printName`: if 1, print the name and version of the menu defined
in `Menu->name` and `Menu->version` respectively

else, don't print them

`int includeVersion`: defines if you want to include `Menu->version`
on the menu name header, useful for submenus that have set their version
to an empty string
*/
void printAndGetInput(Menu* menu, int *optionInt, int printName, int includeVersion);

/*print a selection menu, get user input and put it
on `optionInt`

`int printAction`: if 1, print the name of the menu defined
in your `SelMenu->action`

else, don't print it

`int includeCancel`: defines if you want to include `SelMenu->cancelText`
on the output
*/
void getSelMenuInput(SelMenu* selMenu, int *optionInt, int printAction, int includeCancel);
//deallocates a menu
void deallocMenu(Menu* menu);
//deallocates a selection menu
void deallocSelMenu(SelMenu* menu);
//clear the screen for the next operation
void clear();
//seperate the screen by exactly 75 equal signs
void sep();
/*print an error incase of input invalidation or something
else*/
void error(char* info);
/*print a warning incase something goes wrong and an error
doesn't fit*/
void warning(char* info);
//print an input error
void inputErr(int* input);
//ignore previous input incase the next one is an fgets
void ignorePrev();
#ifdef __cplusplus
}
#endif

#endif // LIBMENU_H
// (no compile)