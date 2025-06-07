#include "libmenu.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Menu* initMenu(char* name, char* version, char** options, long unsigned optionsN, char* exitText) {
    Menu* menu = (Menu*)malloc(sizeof(Menu));
    if (!menu) return NULL;
    menu->name = strdup(name);
    if (!menu->name) menu->name = strdup("libmenu binary");
    if (!menu->name) return NULL;
    menu->version = strdup(version);
    if (!menu->version) menu->version = strdup("1.0");
    if (!menu->version) return NULL;
    menu->optionsN = optionsN;
    menu->options = (char**)malloc(sizeof(char*) * optionsN);
    if (!menu->options) {
        free(menu->name);
        free(menu->version);
        free(menu);
        return NULL;
    }
    for (long unsigned i = 0; i < optionsN; i++) menu->options[i] = options[i];
    menu->exitText = strdup(exitText);
    if (!menu->exitText) menu->exitText = strdup("exit");
    if (!menu->exitText) return NULL;
    return menu;
}
SelMenu* initSelMenu(char* action, char** options, long unsigned optionsN, char* cancelText) {
    SelMenu* menu = (SelMenu*)malloc(sizeof(SelMenu));
    if (!menu) return NULL;
    menu->action = strdup(action);
    if (!menu->action) menu->action = strdup("options:");
    if (!menu->action) return NULL;
    menu->optionsN = optionsN;
    menu->options = (char**)malloc(sizeof(char*) * optionsN);
    if (!menu->options) {
        free(menu->action);
        free(menu);
        return NULL;
    }
    for (long unsigned i = 0; i < optionsN; i++) menu->options[i] = options[i];
    menu->cancelText = strdup(cancelText);
    if (!menu->cancelText) menu->cancelText = strdup("cancel");
    if (!menu->cancelText) return NULL;
    return menu;
}
char* getFormattedVersion(Menu* menu, int includeVersion) {
    char* _temp = (char*)malloc(strlen(menu->name) + (includeVersion ? strlen(menu->version) + 5 : 1));
    if (!_temp) return NULL;
    if (includeVersion)
        sprintf(_temp, "%s v. %s", menu->name, menu->version);
    else
        sprintf(_temp, "%s", menu->name);
    return _temp;
}
void printAndGetInput(Menu* menu, int *optionInt, int printName, int includeVersion) {
    *optionInt = 0; // that's all it took... interesting
    char* _temp = getFormattedVersion(menu, includeVersion);
    if (printName)
        printf("%s\n", _temp);
    for (long unsigned i = 0; i < menu->optionsN; i++)
        printf("(%lu) %s\n", i+1, menu->options[i]);
    printf("(0) %s\n", menu->exitText);
    printf("\n(?) >> ");
    scanf("%d", optionInt);
    free(_temp);
}
void getSelMenuInput(SelMenu* menu, int *optionInt, int printAction, int includeCancel) {
    *optionInt = 0;
    if (printAction)
        printf("%s\n", menu->action);
    for (long unsigned i = 0; i < menu->optionsN; i++)
        printf("(%lu) %s\n", i+1, menu->options[i]);
    if (includeCancel)
        printf("(0) %s\n", menu->cancelText);
    printf("\n(?) >> ");
    scanf("%d", optionInt);
}
void deallocMenu(Menu* menu) {
    for (long unsigned i = 0; i < menu->optionsN; i++) free(menu->options[i]);
    free(menu->options);
    free(menu->exitText);
    free(menu->name);
    free(menu->version);
    free(menu);
}
void deallocSelMenu(SelMenu* menu) {
    for (long unsigned i = 0; i < menu->optionsN; i++) free(menu->options[i]);
    free(menu->options);
    free(menu->cancelText);
    free(menu->action);
    free(menu);
}

void clear() {
    printf("\x1b[2J\x1b[H");
}
void sep() {
    for (int i = 0; i < 75; i++) {
        printf("=");
    }
    printf("\n");
}

void error(char* info) {
    printf("\x1b[1;31merror:\x1b[0m\x1b[1m %s\x1b[0m\n", info);
}
void warning(char* info) {
    printf("\x1b[1;33mwarning:\x1b[0m\x1b[1m %s\x1b[0m\n", info);
}
void inputErr(int *input) {
    char* _temp = (char*)malloc(25 + sizeof(*input));
    sprintf(_temp, "no option made for input %d", *input);
    error(_temp);
    free(_temp);
}

// use make