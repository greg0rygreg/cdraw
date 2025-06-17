// i kinda hate it & it despises me

#include "libs/libmenu.h"
#include "libs/strutils.h"
#include "libs/libdraw.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, str* argv) {
  // anl -> Author Name Length
  int anl = 128;
  // fnl -> File Name Length
  int fnl = 512;
  // fl -> File Length
  int fl = 2048;
  // debug
  _Bool debug = false;
  // ost -> Old Save Tech
  _Bool ost = false;
  for (int i = 0; i < argc; i++) {
    if (strcmp("-anl", argv[i]) == 0)
      anl = atoi(argv[i+1]);
    if (strcmp("-fnl", argv[i]) == 0)
      fnl = atoi(argv[i+1]);
    if (strcmp("-fl", argv[i]) == 0)
      fl = atoi(argv[i+1]);
    if (strcmp("-d", argv[i]) == 0)
      debug = true;
    if (strcmp("-nst", argv[i]) == 0)
      ost = true;
  }
  int optionsN = 3;
  int optionsAN = 1;
  str* options = malloc(sizeof(str) * optionsN);
  if (!options) return 1;
  // i don't want to hear ANY of you say i need to handle errors in here too.
  // if it says (null) or outputs garbage mem it's YOUR problem for not having
  // enough memory available at the disposal of this program
  options[0] = strdup("make canvas");
  options[1] = strdup("view canvas");
  options[2] = strdup("info");
  str* optionsA = malloc(sizeof(str) * optionsAN);
  if (!optionsA) {
    dptrfree((void**)options, optionsN);
    return 1;
  }
  optionsA[0] = strdup("set pixel");

  // i love making my own libs and using them to my advantage
  Menu* menu = initMenu("Cdraw", "beta3-rc2", options, optionsN, "exit");
  // manual memory management is very fun indeed
  // (i hate it)
  if (!menu) {
    dptrfree((void**)options, optionsN);
    dptrfree((void**)optionsA, optionsAN);
    return 1;
  }
  Menu* drawing = initMenu("actions:", "", optionsA, optionsAN, "save canvas & exit");
  if (!drawing) {
    dptrfree((void**)options, optionsN);
    dptrfree((void**)optionsA, optionsAN);
    // how did this go unnoticed for such a long time????
    // for context, before it was deallocMenu(menu), it was free(menu),
    // which is very fucking much memory unsafe
    deallocMenu(menu);
    return 1;
  }

  str FV = getFormattedVersion(menu, 1);

  int b = 0;

  // do you think it's a good idea to do this?
  // i think it is
  Menu* menus[] = {menu, drawing};
  clear();
  while (!b) {
    int mO;
    printAndGetInput(menu, &mO, 1, 1);
    switch (mO) {
      case 0: {
        clear();
        b++;
        break;
      }
      case 1: {
        clear();
        int w;
        int h;
        printf("width: ");
        scanf("%d", &w);
        printf("height: ");
        scanf("%d", &h);
        clear();
        if (h * w == 0) { // simple
          error("width/height can't be zero");
          sep();
          break;
        }
        if (h <= 2 && ost) {
          error("height can't be less than or equal to 2 with Old Save Tech enabled");
          sep();
          break;
        }
        if ((h >= 15 || w >= 15) && !debug) {
          error("width/height can't be equal to or greater than 15 pixels (pass the -d parameter to skip this check)");
          sep();
          break;
        }
        // i love making my own libs and using them to my advantage
        struct canvas* canvas = initCanvas(h, w);
        if (canvas == NULL) {
          error("failed to allocate canvas - breaking now");
          sep();
          break;
        }
        setTime(canvas, time(NULL));
        int b2 = 0;
        while (!b2) {
          for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
              str s = formatPixel(canvas, j+1, i+1);
              printf("%s", s);
              free(s);
            }
            putchar('\n');
          }
          printf("\x1b[0m");
          sep();
          int dO;
          printAndGetInput(drawing, &dO, 1, 0);
          switch (dO) {
            case 1: {
              clear();
              int x;
              int y;
              int v;
              printf("X coordinate (1-%d): ", w);
              scanf("%d", &x);
              printf("Y coordinate (1-%d): ", h);
              scanf("%d", &y);
              clear();
              printf("0 = black\n\
1 = red\n\
2 = green\n\
3 = yellow\n\
4 = blue\n\
5 = magenta\n\
6 = cyan\n\
7 = white\n\
color number: ");
              scanf("%d", &v);
              setPixel(canvas, x, y, v);
              clear();
              break;
            }
            case 0: {
              clear();
              printf("are you sure? (y/n) ");
              ignorePrev();
              char c = getchar();
              if (c == 'y' || c == 'Y')
                b2++;
              else {
                clear();
                break;
              }
              char aname[anl];
              printf("author name (max. %d characters): ", anl);
              ignorePrev();
              fgets(aname, anl, stdin);
              aname[strlen(aname) - 1] = 0x0;
              str nname = NULL;
              if (strlen(aname) != 0)
                strreplace(aname, ';', '_', &nname);
              setAuthor(canvas, nname);
              // ladies and gentlemen...*
              str cuh1 = malloc(h * w + h + 1);
              if (cuh1 == NULL) {
                clear();
                // truly heartbreaking
                error("generating output canvas failed - your artwork has NOT been saved...");
                sep();
                break;
              }
              int g = 0;
              if (ost) {
                for (int i = 0; i < h; i++) {
                  for (int j = 0; j < w; j++) {
                    cuh1[g++] = getPixel(canvas, j+1, i+1) + 48;
                  }
                  if (i < h - 1)
                    cuh1[g++] = '.';
                }
              } else {
                // *i finally did it.
                for (int i = 0; i < h; i++) {
                  char* temp = malloc(w);
                  for (int j = 0; j < w; j++) {
                    temp[j] = canvas->pixels[i][j] + 48;
                  }
                  memcpy(&cuh1[g], temp, w);
                  free(temp);
                  g += w;
                  if (i < h - 1)
                    cuh1[g++] = '.';
                }
              }
              cuh1[g] = 0x0;
              str cuh[] = {"CDC", cuh1, canvas->author};
              // i love making my own libs and using them to my advantage
              str cuh3 = strjoin(cuh, 3, ';');
              char fname[fnl];
              printf("filename (max. %d characters & defaults to current directory): ", fnl);
              fgets(fname, fnl, stdin);
              fname[strlen(fname) - 1] = 0x0;
              clear();
              FILE* file = fopen(fname, "w");
              if (file == NULL) {
                warning("file could not be opened - data will be printed");
                // i'm sorry actually'
                printf("%s;%ld\n", cuh3, canvas->time);
                sep();
              } else
                fprintf(file, "%s;%ld", cuh3, canvas->time);
              delCanvas(canvas);
              free(cuh1);
              free(cuh3);
              if (file) fclose(file);
              break;
            }
            default: {
              clear();
              inputErr(&dO);
              sep();
              break;
            }
          }
        }
        break;
      }
      case 2: {
        // i might have to redo this part
        // surely i won't have to, right?
        clear();
        char fname[fnl];
        printf("filename (max. %d characters & defaults to current directory): ", fnl);
        ignorePrev();
        fgets(fname, fnl, stdin);
        fname[strlen(fname) - 1] = 0x0;
        FILE* file = fopen(fname, "r");
        clear();
        if (!file) {
          error("file doesn't exist");
          sep();
          break;
        }
        /*
           _ _                         _                               
          (_| )_ __ ___    _ __   ___ | |_   ___  ___  _ __ _ __ _   _ 
          | |/| '_ ` _ \  | '_ \ / _ \| __| / __|/ _ \| '__| '__| | | |
          | | | | | | | | | | | | (_) | |_  \__ \ (_) | |  | |  | |_| |
          |_| |_| |_| |_| |_| |_|\___/ \__| |___/\___/|_|  |_|   \__, |
                                                                  |___/
        */
        char buf[fl];
        fgets(buf, fl, file);
        size_t l = 0;
        str* split = strsplit(buf, ';', &l);
        if (strcmp(split[0], "CDC") != 0 || l != 4) {
          error("file is in the wrong format");
          sep();
          fclose(file);
          dptrfree((void**)split, l);
          break;
        }
        time_t _time = atoi(split[3]);
        struct tm* times = localtime(&_time);
        char tb[100];
        str canvas = strdup(split[1]);
        strftime(tb, 100, "%m/%d/%Y @ %H:%M:%S", times);
        printf("who: %s\nwhen: %s\n\n", split[2], tb);
        // this is terrible fucking code but it's the best i can do
        // so if it works, don't touch it
        for (size_t i = 0; i < strlen(canvas); i++) {
          if (canvas[i] != '.')
            // i have no idea why i don't need to put a second integer format specifier
            // for this specific operation
            printf("\x1b[%d;%dm%d", canvas[i] - 18, canvas[i] - 8, canvas[i]);
          else
            putchar(0xa);
        }
        printf("\x1b[0m\n");
        dptrfree((void**)split, l);
        free(canvas);
        fclose(file);
        sep();
        break;
      }
      case 3: {
        clear();
        printf("%s\nlicensed under MIT license\nmade with love and patience by greg\n", FV);
        sep();
        break;
      }
      default: {
        clear();
        inputErr(&mO);
        sep();
        break;
      }
    }
  }
  for (int i = 0; i < 2; i++) deallocMenu(menus[i]);
  free(FV);
  return 0;
}

// use make