#include "libdraw.h"
#include <stdlib.h>
#include <string.h>

struct canvas* initCanvas(int h, int w) {
  struct canvas* cs = malloc(sizeof(struct canvas));
  if (cs == NULL) return NULL;
  cs->height = h;
  cs->width = w;
  int** c = malloc(sizeof(int*) * h);
  if (c == NULL) {
    free(cs);
    return NULL;
  }
  for (int i = 0; i < h; i++) {
    c[i] = malloc(sizeof(int) * w);
    if (c[i] == NULL) {
      for (int j = 0; j < i; j++) {
        free(c[j]);
      }
      free(c);
      free(cs);
      return NULL;
    }
    for (int j = 0; j < w; j++) {
      c[i][j] = 0;
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
  for (int i = 0; i < c->height; i++)
    free(c->pixels[i]);
  free(c->pixels);
  free(c->author);
  free(c);
}

void setAuthor(struct canvas* c, char* a) {
  free(c->author);
  c->author = a;
}

void togglePixel(struct canvas* c, int x, int y) {
  c->pixels[y-1][x-1] = !c->pixels[y-1][x-1];
}

void invertPixels(struct canvas* c) {
  for (int y = 0; y < c->height; y++) {
    for (int x = 0; x < c->width; x++) {
      c->pixels[y][x] = !c->pixels[y][x];
    }
  }
}

void setTime(struct canvas* c, time_t t) {
  c->time = t;
}

int getPixel(struct canvas* c, int x, int y) {
  return c->pixels[y-1][x-1];
}