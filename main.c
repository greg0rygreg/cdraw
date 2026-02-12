#include "libs/libmenu.h"
#include "libs/strutils.h"
#include "libs/libdraw.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define VERSION "1.4.3"

int main(int argc, str* argv) {
  // anl -> Author Name Length
  int anl = 256;
  // fnl -> File Name Length
  int fnl = 512;
  // fl -> File Length
  int fl = 2048;
  // devmode -> Developer Mode
  bool devmode = false;
  // osm -> Older Saving Method
  bool osm = false;
  // editing
  bool editing = false;
  for (int i = 0; i < argc; i++) {
    if (strcmp("-anl", argv[i]) == 0)
      anl = atoi(argv[i+1]);
    if (strcmp("-fnl", argv[i]) == 0)
      fnl = atoi(argv[i+1]);
    if (strcmp("-fl", argv[i]) == 0)
      fl = atoi(argv[i+1]);
    if (strcmp("-dm", argv[i]) == 0)
      devmode = true;
    if (strcmp("-osm", argv[i]) == 0)
      osm = true;
  }

  // I love making my own libs and using them to my advantage
  lm_menu* menu = make_menu(
    "Cdraw",
    VERSION,
    (str[]){
      "make canvas",
      "view canvas",
      "info"
    },
    3,
    NULL, // as far as I'm aware this'll work
    false
  );
  if (!menu) {
    error("allocation for main menu failed, exiting");
    return 1;
  }

  lm_menu* drawing = make_menu(
    "actions:",
    NULL,
    (str[]){
      "paint pixel",
      "fill canvas",
      "fill area",
      "invert canvas",
      "invert area"
    },
    5,
    "save canvas & exit",
    true
  );
  if (!drawing) {
    error("allocation for drawing menu failed, exiting");
    unmake_menu(menu);
    // hehe funny line
    return 1;
  }
  bool b = false;

  // do you think it's a good idea to do this?
  // I think it is
  // Menu* menus[] = {menu, drawing};
  // 8/13/25 it's not
  // 2/4/26 it really isn't

  clear();
  while (!b) {
    get_input(menu, true);
    switch (menu->last_selection) {
      // exit
      case 0: {
        clear();
        b = true;
        break;
      }
      // make canvas
      case 1: {
        clear();
        int w;
        int h;
        // yo you guys should try to remake this in HolyC
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
        if (h <= 2 && osm) {
          error("height can't be less than or equal to 2 (disable osm (Older Saving Method) to skip this check)");
          sep();
          break;
        }
        if ((h >= 15 || w >= 15) && !devmode) {
          error("width/height can't be equal to or greater than 15 pixels (pass the -dm parameter to skip this check)");
          sep();
          break;
        }
        // I love making my own libs and using them to my advantage
        Canvas* canvas = initCanvas(h, w);
        if (canvas == NULL) {
          error("failed to allocate canvas - breaking now");
          sep();
          break;
        }
        setTime(canvas, time(NULL));
        bool b2 = false;
        char s[20];
        char temp[w*2 + 1];
        memset(temp, '-', w*2);
        temp[w*2] = 0;
        while (!b2) {
          for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
              formatPixelB(canvas, j+1, i+1, s, 20);
              printf("%s\x1b[0m", s);
            }
            putchar(10);
          }
          printf("\x1b[0m");
          printf("%s\n", temp);
          get_input(drawing, true);
          switch (drawing->last_selection) {
            // paint pixel
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
              printf("colors:\n\
  0 = black\n\
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
            // fill canvas
            case 2: {
              clear();
              int v;
              printf("colors:\n\
  0 = black\n\
  1 = red\n\
  2 = green\n\
  3 = yellow\n\
  4 = blue\n\
  5 = magenta\n\
  6 = cyan\n\
  7 = white\n\
color number: ");
              scanf("%d", &v);
              fillPixels(canvas, 1, 1, w, h, v);
              clear();
              break;
            }
            // fill area
            case 3: {
              clear();
              int x1;
              int y1;
              int x2;
              int y2;
              int v;
              printf("X1 coordinate (1-%d): ", w);
              scanf("%d", &x1);
              printf("Y1 coordinate (1-%d): ", h);
              scanf("%d", &y1);
              printf("X2 coordinate (1-%d): ", w);
              scanf("%d", &x2);
              // I'M ABOUT TO WOON
              printf("Y2 coordinate (1-%d): ", h);
              scanf("%d", &y2);
              clear();
              printf("colors:\n\
  0 = black\n\
  1 = red\n\
  2 = green\n\
  3 = yellow\n\
  4 = blue\n\
  5 = magenta\n\
  6 = cyan\n\
  7 = white\n\
color number: ");
              scanf("%d", &v);
              fillPixels(canvas, x1, y1, x2, y2, v);
              clear();
              break;
            }
            // invert canvas
            case 4: {
              clear();
              invertPixels(canvas);
              break;
            }
            // invert area
            case 5: {
              clear();
              int x1;
              int y1;
              int x2;
              int y2;
              printf("X1 coordinate (1-%d): ", w);
              scanf("%d", &x1);
              printf("Y1 coordinate (1-%d): ", h);
              scanf("%d", &y1);
              printf("X2 coordinate (1-%d): ", w);
              scanf("%d", &x2);
              printf("Y2 coordinate (1-%d): ", h);
              scanf("%d", &y2);
              clear();
              invertArea(canvas, x1, y1, x2, y2);
              break;
            }
            // exit
            case 0: {
              clear();
              /*
              58641 21:16 For thus hath the LORD said unto me, Within a year, according to
              58642 the years of an hireling, and all the glory of Kedar shall fail: 21:17
              58643 And the residue of the number of archers, the mighty men of the
              58644 children of Kedar, shall be diminished: for the LORD God of Israel
              58645 hath spoken it.
              58646
              58647 22:1 The burden of the valley of vision. What aileth thee now, that
              58648 thou art wholly gone up to the housetops?  22:2 Thou that art full of
              58649 stirs, a tumultuous city, joyous city: thy slain men are not slain
              58650 with the sword, nor dead in battle.
              58651
              58652 22:3 All thy rulers are fled together, they are bound by the archers:
              58653 all that are found in thee are bound together, which have fled from
              58654 far.
              58655
              58656 22:4 Therefore said I, Look away from me; I will weep bitterly, labour
              58657 not to comfort me, because of the spoiling of the daughter of my
              58658 people.
              58659
              58660 22:5 For it is a day of trouble, and of treading down, and of
              58661 perplexity by the Lord GOD of hosts in the valley of vision, breaking
              58662 down the walls, and of crying to the mountains.
              58663
              58664 22:6 And Elam bare the quiver with chariots of men and horsemen, and
              58665 Kir uncovered the shield.
              */
              printf("are you sure? (y/n) ");
              ignore_previous_input();
              char c = getchar();
              if (c == 'y' || c == 'Y')
                b2 = true;
              else {
                clear();
                break;
              }
              char aname[anl];
              printf("author name (max. %d characters): ", anl);
              ignore_previous_input();
              fgets(aname, anl, stdin);
              // some C veteran is gonna tell me this is hyper unsafe
              if (strcmp(aname, "\n") == 0)
                memcpy(aname, "unknown", 8);
              else
                aname[strlen(aname) - 1] = 0;
              str nname = strreplace(aname, ';', '_');
              // this is actually safe because in libdraw
              // I check if if the author is NULL, if it is
              // then don't free it (avoids IOT instruction)
              setAuthor(canvas, nname);
              str cuh1 = malloc(h * w + h + 1);
              if (cuh1 == NULL) {
                clear();
                // truly heartbreaking
                error("generating output canvas failed - your artwork has NOT been saved...");
                sep();
                break;
              }
              int g = 0;
              if (!osm) {
                // FUCKING FINALLY
                for (int i = 0; i < h; i++) {
                  char* temp = malloc(w);
                  for (int j = 0; j < w; j++)
                    temp[j] = canvas->pixels[i][j] + 48;
                  memcpy(&cuh1[g], temp, w);
                  free(temp);
                  g += w;
                  if (i < h - 1)
                    cuh1[g++] = '.';
                }
              } else {
                for (int i = 0; i < h; i++) {
                  for (int j = 0; j < w; j++)
                    cuh1[g++] = getPixel(canvas, j+1, i+1) + 48;
                  if (i < h - 1)
                    cuh1[g++] = '.';
                }
              }
              cuh1[g] = 0;
              char fname[fnl];
              printf("filename (max. %d characters & defaults to current directory): ", fnl);
              fgets(fname, fnl, stdin);
              fname[strlen(fname) - 1] = 0;
              clear();
              FILE* file = fopen(fname, "w");
              if (file == NULL) {
                warning("file could not be opened - data will be printed");
                // I'm sorry actually]
                // 2/12/26 no i'm not
                printf("CDC;%s;%s;%ld\n", cuh1, canvas->author, canvas->time);
                sep();
              } else {
                fprintf(file, "CDC;%s;%s;%ld", cuh1, canvas->author, canvas->time);
                fclose(file);
              }
              if (!editing){
                delCanvas(canvas);
                free(cuh1);
              } else {
              }
              break;
            }
            // fallback
            default: {
              clear();
              error("no option made for selection %d", drawing->last_selection);
              sep();
              break;
            }
          }
        }
        break;
      }
      // view canvas
      case 2: {
        clear();
        char fname[fnl];
        printf("filename (max. %d characters & defaults to current directory): ", fnl);
        ignore_previous_input();
        fgets(fname, fnl, stdin);
        fname[strlen(fname) - 1] = 0;
        FILE* file = fopen(fname, "r");
        clear();
        if (!file) {
          error("file doesn't exist");
          sep();
          break;
        }
        /*
          ██╗██╗███╗   ███╗    ███╗   ██╗ ██████╗ ████████╗    ███████╗ ██████╗ ██████╗ ██████╗ ██╗   ██╗
          ██║██║████╗ ████║    ████╗  ██║██╔═══██╗╚══██╔══╝    ██╔════╝██╔═══██╗██╔══██╗██╔══██╗╚██╗ ██╔╝
          ██║╚═╝██╔████╔██║    ██╔██╗ ██║██║   ██║   ██║       ███████╗██║   ██║██████╔╝██████╔╝ ╚████╔╝
          ██║   ██║╚██╔╝██║    ██║╚██╗██║██║   ██║   ██║       ╚════██║██║   ██║██╔══██╗██╔══██╗  ╚██╔╝
          ██║   ██║ ╚═╝ ██║    ██║ ╚████║╚██████╔╝   ██║       ███████║╚██████╔╝██║  ██║██║  ██║   ██║
          ╚═╝   ╚═╝     ╚═╝    ╚═╝  ╚═══╝ ╚═════╝    ╚═╝       ╚══════╝ ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝
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
        char tb[30];
        str canvas = strdup(split[1]);
        strftime(tb, 30, "%m/%d/%Y @ %H:%M:%S", times);
        printf("who: %s\nwhen: %s\n\n", split[2], tb);
        for (size_t i = 0; i < strlen(canvas); i++) {
          if (canvas[i] != '.')
            // found the problem
            // I was casting char to int which caused, let's say, a 0, to turn into 48
            printf("\x1b[%d;%dm%c%c", (canvas[i]-'0') + 30, (canvas[i]-'0') + 40, canvas[i], canvas[i]);
          else
            putchar(10);
        }
        printf("\x1b[0m\n");
        if (devmode) printf("%s\n", canvas);
        dptrfree((void**)split, l);
        free(canvas);
        fclose(file);
        sep();
        break;
      }
      // info
      case 3: {
        clear();
        printf("%s v. %s\nlicensed under MIT license\nmade with love and patience by greg\n", menu->name, menu->version);
        sep();
        break;
      }
      // fallback
      default: {
        clear();
        error("no option made for selection %d", menu->last_selection);
        sep();
        break;
      }
    }
  }
  unmake_menu(menu);
  unmake_menu(drawing);
  return 0;
}

// that's all folks
// to compile, use make
// funnier line