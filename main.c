// do you see a strsplit in here? I friggin don't
#include "libs/libmenu.h"
#include "libs/strutils.h"
#include "libs/libdraw.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, str* argv) {
  // anl -> Author Name Length
  int anl = 256;
  // fnl -> File Name Length
  int fnl = 512;
  // fl -> File Length
  int fl = 2048;
  // devmode -> Developer Mode
  bool devmode = false;
  for (int i = 0; i < argc; i++) {
    if (strcmp("-anl", argv[i]) == 0)
      anl = atoi(argv[i+1]);
    if (strcmp("-fnl", argv[i]) == 0)
      fnl = atoi(argv[i+1]);
    if (strcmp("-fl", argv[i]) == 0)
      fl = atoi(argv[i+1]);
    if (strcmp("-dm", argv[i]) == 0)
      devmode = true;
  }

  // I love making my own libs and using them to my advantage
  lm_menu* menu = lm_domenu(
    "Cdraw",
    "1.6.0-rc1",
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
    lm_error("allocation for main menu failed, exiting");
    return 1;
  }

  lm_menu* drawing = lm_domenu(
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
    lm_error("allocation for drawing menu failed, exiting");
    free(menu);
    return 1;
  }
  bool b = false;
  lm_clear();
  // hehe funny line
  while (!b) {
    lm_input(menu, true);
    switch (menu->last) {
      // exit
      case 0: {
        lm_clear();
        b = true;
        break;
      }
      // make canvas
      case 1: {
        lm_clear();
        int w, h;
        // yo you guys should try to remake this in HolyC
        // 2/14/26 no you guys shouldn't
        printf("width: ");
        scanf("%d", &w);
        printf("height: ");
        scanf("%d", &h);
        lm_clear();
        if (h*w == 0) { // simple
          lm_error("area can't be zero");
          lm_sep();
          break;
        }
        // I love making my own libs and using them to my advantage
        ld_canvas* canvas = ld_docanvas(h, w);
        if (!canvas) {
          lm_error("failed to allocate canvas - stopping now");
          lm_sep();
          break;
        }
        ld_time(canvas, time(NULL));
        bool b2 = false;
        char s[11]; // pixel buffer
        char csep[w*2 + 1]; // canvas seperator
        memset(csep, '-', w*2);
        csep[w*2] = 0;
        while (!b2) {
          for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
              ld_FPbuf(canvas, j+1, i+1, s);
              printf("%s\x1b[0m", s);
            }
            putchar(10);
          }
            printf("\x1b[0m");
            printf("%s\n", csep);
          lm_input(drawing, true);
          switch (drawing->last) {
            // paint pixel
            case 1: {
              lm_clear();
              int x, y, v;
              printf("X coordinate (1-%d): ", w);
              scanf("%d", &x);
              printf("Y coordinate (1-%d): ", h);
              scanf("%d", &y);
              lm_clear();
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
              ld_setpixel(canvas, x, y, v);
              lm_clear();
              break;
            }
            // fill canvas
            case 2: {
              lm_clear();
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
              ld_fill(canvas, 1, 1, w, h, v);
              lm_clear();
              break;
            }
            // fill area
            case 3: {
              lm_clear();
              int x1, y1, x2, y2, v;
              printf("X1 coordinate (1-%d): ", w);
              scanf("%d", &x1);
              printf("Y1 coordinate (1-%d): ", h);
              scanf("%d", &y1);
              printf("X2 coordinate (1-%d): ", w);
              scanf("%d", &x2);
              // I'M ABOUT TO WOON
              printf("Y2 coordinate (1-%d): ", h);
              scanf("%d", &y2);
              lm_clear();
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
              ld_fill(canvas, x1, y1, x2, y2, v);
              lm_clear();
              break;
            }
            // invert canvas
            case 4: {
              lm_clear();
              ld_invertall(canvas);
              break;
            }
            // invert area
            case 5: {
              lm_clear();
              int x1, y1, x2, y2;
              printf("X1 coordinate (1-%d): ", w);
              scanf("%d", &x1);
              printf("Y1 coordinate (1-%d): ", h);
              scanf("%d", &y1);
              printf("X2 coordinate (1-%d): ", w);
              scanf("%d", &x2);
              printf("Y2 coordinate (1-%d): ", h);
              scanf("%d", &y2);
              lm_clear();
              ld_invert(canvas, x1, y1, x2, y2);
              break;
            }
            // exit
            case 0: {
              lm_clear();
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
              printf("are you sure? (y/[n]) ");
              lm_noprevinput();
              char c = getchar();
              if (c == 'y' || c == 'Y')
                b2 = true;
              else {
                lm_clear();
                break;
              }
              char aname[anl];
              printf("author name (max. %d characters): ", anl);
              lm_noprevinput();
              fgets(aname, anl, stdin);
              // some C veteran is gonna tell me this is ultra unsafe
              // 3/24/26 none has told me that yet
              if (strcmp(aname, "\n") == 0)
                memcpy(aname, "unknown", 8);
              else
                aname[strlen(aname) - 1] = 0;
              str nname = strreplace(aname, '.', '_');
              // this is actually safe because in libdraw
              // i check if if the author is NULL, if it is
              // then don't free it (avoids IOT instruction)
              ld_author(canvas, nname);
              str cuh1 = malloc(h * w + h + 1);
              if (cuh1 == NULL) {
                lm_clear();
                // truly heartbreaking
                lm_error("generating output canvas failed - your artwork has NOT been saved...");
                lm_sep();
                break;
              }
              int g = 0;
              char temp[w];
              for (int i = 0; i < h; i++) {
                for (int j = 0; j < w; j++)
                  temp[j] = canvas->pixels[w * i + j] + 48;
                memcpy(&cuh1[g], temp, w);
                g += w;
              }
              cuh1[g] = 0;
              char fname[fnl];
              printf("filename (max. %d characters & defaults to current directory): ", fnl);
              fgets(fname, fnl, stdin);
              fname[strlen(fname) - 1] = 0;
              lm_clear();
              FILE* file = fopen(fname, "w");
              if (file == NULL) {
                lm_warn("file could not be opened - data will be printed");
                // I'm sorry actually]
                // 2/12/26 no i'm not
                printf("CDC2.%d.%s.%s.%ld\n", w, cuh1, canvas->author, canvas->time);
                lm_sep();
              } else {
                fprintf(file, "CDC2.%d.%s.%s.%ld", w, cuh1, canvas->author, canvas->time);
                fclose(file);
              }
              ld_uncanvas(canvas);
              free(cuh1);
              break;
            }
            // fallback
            default: {
              lm_clear();
              lm_error("no option made for selection %d", drawing->last);
              lm_sep();
              break;
            }
          }
        }
        break;
      }
      // view canvas
      case 2: {
        lm_clear();
        char fname[fnl];
        printf("filename (max. %d characters & defaults to current directory): ", fnl);
        lm_noprevinput();
        fgets(fname, fnl, stdin);
        fname[strlen(fname) - 1] = 0;
        FILE* file = fopen(fname, "r");
        lm_clear();
        if (!file) {
          lm_error("file doesn't exist");
          lm_sep();
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
        if (strcount(buf, '.') != 4) {
          lm_error("file is in the wrong format");
          fclose(file);
          lm_sep();
          break;
        }
        str buftok = strtok(buf, ".");
        int i = 0;
        //str data[3];
        str fmt;
        int w;
        str cnv;
        str atr;
        time_t time;
        while (buftok) {
          // CDC2.w.cnv.atr.time
          switch (i) {
            case 0: {
              fmt = buftok;
              break;
            }
            case 1: {
              w = atoi(buftok);
              break;
            }
            case 2: {
              cnv = buftok;
              break;
            }
            case 3: {
              atr = buftok;
              break;
            }
            case 4: {
              time = atoi(buftok);
              break;
            }
          }
          buftok = strtok(NULL, ".");
          i++;
        }
        /*if (fmt[3] != ';') {
          lm_warn(
            "file is in an old format\x1b[0m\n\
            i will NOT attempt to load it but make it look something like this:\n\
            CDC2.width.canvas.author.time"
          );
          fclose(file);
          lm_sep();
          break;
        }*/
        if (strncmp(fmt, "CDC2", 4) != 0) {
          lm_error("file is in the wrong format");
          fclose(file);
          lm_sep();
          break;
        }
        str timefmt = ctime(&time);
        printf("who: %s\nwhen: %s\n", atr, timefmt);
        for (int i = 0; cnv[i]; i++) {
          char cur = cnv[i]-'0';
          printf(
            "\x1b[%d;%dm%d%d",
            cur+30,
            cur+40,
            cur,
            cur
          );
          if (i % w == w-1) // i am very smart.
            putchar(10);
        }
        printf("\x1b[0m");
        if (devmode) printf("\n%s.%d.%s.%s.%lu\n", fmt, w, cnv, atr, time);
        fclose(file);
        lm_sep();
        break;
      }
      // info
      case 3: {
        lm_clear(); // funnier line)
        printf("%s v. %s\nlicensed under MIT license\nmade with love and patience by Gregory Theodore Greg\n", menu->name, menu->version);
        lm_sep();
        break;
      }
      // fallback
      default: {
        lm_clear();
        lm_error("no option made for selection %d", menu->last);
        lm_sep();
        break;
      }
    }
  }
  free(menu);
  free(drawing);
  return 0;
}

// that's all folks
// gcc -o main main.c libs/*.c
