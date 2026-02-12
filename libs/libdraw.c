#include "libdraw.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int clampI (int min, int max, int v) {
  return v < min ? min : (v > max ? max : v); // dude
}

struct canvas* initCanvas(int h, int w) {
  // there's no way this function segfaults a program, right?
  if (h * w == 0) return NULL;
  struct canvas* cs = malloc(sizeof(struct canvas));
  if (cs == NULL) return NULL;
  cs->height = h;
  cs->width = w;
  char** c = malloc(sizeof(char*) * h);
  if (c == NULL) {
    free(cs);
    return NULL;
  }
  for (int i = 0; i < h; i++) {
    c[i] = malloc(sizeof(char) * w);
    if (c[i] == NULL) {
      for (int j = 0; j < i; j++) {
        free(c[j]);
      }
      free(c);
      free(cs);
      return NULL;
    }
    for (int j = 0; j < w; j++) {
      c[i][j] = 7;
    }
  }
  cs->pixels = c;
  cs->author = strdup("unknown");
  if (cs->author == NULL) {
    for (int i = 0; i < h; i++)
      free(c[i]);
    free(c);
    free(cs);
    return NULL;
  }
  cs->time = 0;
  return cs;
};

void delCanvas(struct canvas* c) {
  if (c == NULL) return;
  for (int i = 0; i < c->height; i++) free(c->pixels[i]);
  free(c->pixels);
  free(c->author);
  free(c);
}

void setAuthor(struct canvas* c, char* a) {
  if (c == NULL) return;
  if (c->author != NULL) free(c->author);
  c->author = a;
}

enum PIXEL clampPixel(enum PIXEL c) {
  if (c < BLACK)
    return BLACK;
  else if (c > WHITE)
    return WHITE;
  else
    return c;
}

void setPixel(struct canvas* c, int x, int y, enum PIXEL v) {
  if (c == NULL) return;
  if (y-1 >= 0 && y-1 <= c->height-1 && x-1 >= 0 && x-1 <= c->width-1)
    c->pixels[y-1][x-1] = clampPixel(v);
}

enum PIXEL getPixel(struct canvas* c, int x, int y) {
  if (c == NULL) return UNKNOWN;
  if (y-1 >= 0 && y-1 <= c->height-1 && x-1 >= 0 && x-1 <= c->width-1)
    return c->pixels[y-1][x-1];
  return UNKNOWN;
}

void invertPixels(struct canvas* c) {
  if (c == NULL) return;
  int t[] = {7, 6, 5, 4, 3, 2, 1, 0};
  for (int y = 0; y <= c->height; y++) {
    for (int x = 0; x <= c->width; x++) {
      setPixel(c, x, y, t[getPixel(c, x, y)]);
    }
  }
}

void invertArea(Canvas* c, int x1, int y1, int x2, int y2) {
  if (c == NULL) return;
  int t2[] = {7, 6, 5, 4, 3, 2, 1, 0};
  int t;
  if (x1 > x2) {
    t = x1;
    x1 = x2;
    x2 = t;
  }
  if (y1 > y2) {
    t = y1;
    y1 = y2;
    y2 = t;
  }

  x1 = clampI(1, c->width, x1);
  x2 = clampI(1, c->width, x2);
  y1 = clampI(1, c->height, y1);
  y2 = clampI(1, c->height, y2);
  for (int y = y1; y <= y2; y++) {
    for (int x = x1; x <= x2; x++) {
      setPixel(c, x, y, t2[getPixel(c, x, y)]);
    }
  }
}

void fillPixels(Canvas* c, int x1, int y1, int x2, int y2, enum PIXEL v) {
  if (c == NULL) return;
  int t;
  if (x1 > x2) {
    t = x1;
    x1 = x2;
    x2 = t;
  }
  if (y1 > y2) {
    t = y1;
    y1 = y2;
    y2 = t;
  }

  x1 = clampI(1, c->width, x1);
  x2 = clampI(1, c->width, x2);
  y1 = clampI(1, c->height, y1);
  y2 = clampI(1, c->height, y2);
  for (int y = y1; y <= y2; y++) {
    for (int x = x1; x <= x2; x++) {
      setPixel(c, x, y, v);
    }
  }
}

void setTime(struct canvas* c, time_t t) {
  if (c == NULL) return;
  c->time = t;
}

char* formatPixel(struct canvas* c, int x, int y) {
  // \x1b[xx;yymzz 14
  // 8/5/25 it's actually 11 because \x1b is 1 character and not 3
  // 8/11/25 i'll leave it at 14 for safety
  // 2/12/26 FUCK IT WE BALL
  if (c == NULL) return NULL;
  enum PIXEL p = getPixel(c, x, y);
  char* temp = malloc(11);
  snprintf(temp, 11, "\x1b[%d;%dm%d%d", p + 30, p + 40, p, p);
  return temp;
}

void formatPixelB(Canvas* c, int x, int y, char* buffer, size_t len) {
  if (c == NULL) return;
  enum PIXEL p = getPixel(c, x, y);
  snprintf(buffer, len, "\x1b[%d;%dm%d%d", p + 30, p + 40, p, p);
}