#include "libdraw.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
      c[i][j] = 0x7;
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
  for (int i = 0; i < c->height; i++)
    free(c->pixels[i]);
  free(c->pixels);
  free(c->author);
  free(c);
}

void setAuthor(struct canvas* c, char* a) {
  if (a == NULL || c == NULL) return;
  free(c->author);
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

/*void invertPixels(struct canvas* c) {
  if (c == NULL) return;
  for (int y = 0; y < c->height; y++) {
    for (int x = 0; x < c->width; x++)
      if (c->pixels[y][x] < 0x3)
        c->pixels[y][x] = clampChar(c->pixels[y][x] + 0x3);
      else if (c->pixels[y][x] > 0x3)
        c->pixels[y][x] = clampChar(c->pixels[y][x] - 0x3);
  }
}*/

void setTime(struct canvas* c, time_t t) {
  if (c == NULL) return;
  c->time = t;
}

enum PIXEL getPixel(struct canvas* c, int x, int y) {
  if (c == NULL) return UNKNOWN;
  if (y-1 >= 0 && y-1 <= c->height-1 && x-1 >= 0 && x-1 <= c->width-1)
    return c->pixels[y-1][x-1];
  return UNKNOWN;
}

char* formatPixel(struct canvas* c, int x, int y) {
  // \x1b[xx;yymzz 14
  char* temp = malloc(sizeof(char) * 14);
  sprintf(temp, "\x1b[%d;%dm%d%d", getPixel(c, x, y) + 30, getPixel(c, x, y) + 40, getPixel(c, x, y), getPixel(c, x, y));
  return temp;
}