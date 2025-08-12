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

//menu configurator
Menu* initMenu(char* name, char* version, char* options[], long unsigned optionsN, char* exitText);

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

//deallocates a menu, just a free()
void deallocMenu(Menu* menu);

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
