#include "libmenu.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* ------------------------- * INITIALIZATION * ------------------------- */
Menu* initMenu(char* name, char* version, char** options, long unsigned optionsN, char* exitText) {
  Menu* menu = (Menu*)malloc(sizeof(Menu));
  if (!menu) return NULL;
  menu->name = name;
  menu->version = version;
  menu->optionsN = optionsN;
  menu->options = options;
  menu->exitText = exitText;
  return menu;
}

/* ------------------------- * VERSION FORMATTING... what * ------------------------- */
char* getFormattedVersion(Menu* menu, int includeVersion) {
  char* _temp = (char*)malloc(strlen(menu->name) + (includeVersion ? strlen(menu->version) + 5 : 1));
  if (!_temp) return NULL;
  if (includeVersion)
    sprintf(_temp, "%s v. %s", menu->name, menu->version);
  else
    sprintf(_temp, "%s", menu->name);
  return _temp;
}

/* ------------------------- * STDIN OPERATIONS * ------------------------- */
void printAndGetInput(Menu* menu, int *optionInt, int printName, int includeVersion) {
  *optionInt = 0; // that's all it took... interesting
  char* _temp = getFormattedVersion(menu, includeVersion);
  if (printName)
    printf("%s\n", _temp);
  for (unsigned long i = 0; i < menu->optionsN; i++)
    printf("(%lu) %s\n", i+1, menu->options[i]);
  printf("(0) %s\n", menu->exitText);
  printf("\n(?) >> ");
  scanf("%d", optionInt);
  free(_temp);
}

/* ------------------------- * DEALLOCATION * ------------------------- */
void deallocMenu(Menu* menu) {
  free(menu);
}

/* ------------------------- * STDOUT OPERATIONS * ------------------------- */
void clear() {
  printf("\x1b[2J\x1b[H");
}
void sep() {
  for (int i = 0; i < 75; i++) {
    printf("=");
  }
  printf("\n");
}

/* ------------------------- * ERROR HANDLING * ------------------------- */
void error(char* info) {
  printf("\x1b[1;31merror:\x1b[0m\x1b[1m %s\x1b[0m\n", info);
}
void warning(char* info) {
  printf("\x1b[1;33mwarning:\x1b[0m\x1b[1m %s\x1b[0m\n", info);
}
void inputErr(int *input) {
  /*char _temp[50];
  sprintf(_temp, "no option made for input %d", *input);
  error(_temp);*/
  printf("\x1b[1;31merror:\x1b[0m\x1b[1m no option made for input %d\x1b[0m\n", *input);
}

/* ------------------------- * OTHER * ------------------------- */
void ignorePrev() {
  char c;
  while ((c = getchar()) != '\n' && c != EOF);
}

/* ------------------------- * DONE! * ------------------------- */

// use make