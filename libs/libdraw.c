#include "libdraw.h"
#include <stdlib.h>
#include <string.h>

struct canvas* initCanvas(int h, int w) {
  // there's no way this function segfaults a program, right?
  if (h * w == 0) return NULL;
  struct canvas* cs = malloc(sizeof(struct canvas));
  if (cs == NULL) return NULL;
  cs->height = h;
  cs->width = w;
  bool** c = malloc(sizeof(bool*) * h);
  if (c == NULL) {
    free(cs);
    return NULL;
  }
  for (int i = 0; i < h; i++) {
    c[i] = malloc(sizeof(bool) * w);
    if (c[i] == NULL) {
      for (int j = 0; j < i; j++) {
        free(c[j]);
      }
      free(c);
      free(cs);
      return NULL;
    }
    for (int j = 0; j < w; j++) {
      c[i][j] = false;
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

void togglePixel(struct canvas* c, int x, int y) {
  if (c == NULL) return;
  if (y-1 >= 0 && y-1 <= c->height-1 && x-1 >= 0 && x-1 <= c->width-1)
    c->pixels[y-1][x-1] = !c->pixels[y-1][x-1];
}

void setPixel(struct canvas* c, int x, int y, bool v) {
  if (c == NULL) return;
  if (y-1 >= 0 && y-1 <= c->height-1 && x-1 >= 0 && x-1 <= c->width-1)
    c->pixels[y-1][x-1] = v;
}

void invertPixels(struct canvas* c) {
  if (c == NULL) return;
  for (int y = 0; y < c->height; y++) {
    for (int x = 0; x < c->width; x++) {
      c->pixels[y][x] = !c->pixels[y][x];
    }
  }
}

void setTime(struct canvas* c, time_t t) {
  if (c == NULL) return;
  c->time = t;
}

bool getPixel(struct canvas* c, int x, int y) {
  if (c == NULL) return false;
  if (y-1 >= 0 && y-1 <= c->height-1 && x-1 >= 0 && x-1 <= c->width-1)
    return c->pixels[y-1][x-1];
  return false;
}