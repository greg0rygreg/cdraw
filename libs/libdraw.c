#include "libdraw.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int clampI(int min, int max, int v) {
  return v < min ? min : (v > max ? max : v);
}

ld_canvas* ld_docanvas(int h, int w) {
  // there's no way this function segfaults a program, right?
  if (h * w == 0) return NULL;
  ld_canvas* cs = malloc(sizeof(ld_canvas));
  if (!cs) return NULL;
  cs->height = h;
  cs->width = w;
  char** c = malloc(sizeof(char*) * h);
  if (!c) {
    free(cs);
    return NULL;
  }
  for (int i = 0; i < h; i++) {
    c[i] = malloc(sizeof(char) * w);
    if (!c[i]) {
      for (int j = 0; j < i; j++)
        free(c[j]);
      free(c);
      free(cs);
      return NULL;
    }
    for (int j = 0; j < w; j++)
      c[i][j] = 7;
  }
  cs->pixels = c;
  cs->author = strdup("unknown");
  if (!cs->author) {
    for (int i = 0; i < h; i++)
      free(c[i]);
    free(c);
    free(cs);
    return NULL;
  }
  cs->time = 0;
  return cs;
};

void ld_uncanvas(ld_canvas* c) {
  if (!c) return;
  for (int i = 0; i < c->height; i++) free(c->pixels[i]);
  free(c->pixels);
  free(c->author);
  free(c);
}

void ld_author(ld_canvas* c, char* a) {
  if (!c) return;
  if (c->author) free(c->author);
  c->author = a;
}

pixel ld_clamp(pixel c) {
  return clampI(0, 7, c);
}

void ld_setpixel(ld_canvas* c, int x, int y, pixel v) {
  if (!c) return;
  if (y-1 >= 0 && y-1 <= c->height-1 && x-1 >= 0 && x-1 <= c->width-1)
    c->pixels[y-1][x-1] = ld_clamp(v);
}

pixel ld_getpixel(ld_canvas* c, int x, int y) {
  if (c == NULL) return UNKNOWN;
  if (y-1 >= 0 && y-1 <= c->height-1 && x-1 >= 0 && x-1 <= c->width-1)
    return c->pixels[y-1][x-1];
  return UNKNOWN;
}

void ld_invertall(ld_canvas* c) {
  if (c == NULL) return;
  int t[] = {7, 6, 5, 4, 3, 2, 1, 0};
  for (int y = 0; y <= c->height; y++) {
    for (int x = 0; x <= c->width; x++) {
      ld_setpixel(c, x, y, t[ld_getpixel(c, x, y)]);
    }
  }
}

void ld_invert(ld_canvas* c, int x1, int y1, int x2, int y2) {
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
      ld_setpixel(c, x, y, t2[ld_getpixel(c, x, y)]);
    }
  }
}

void ld_fill(ld_canvas* c, int x1, int y1, int x2, int y2, pixel v) {
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
      ld_setpixel(c, x, y, v);
    }
  }
}

void ld_time(ld_canvas* c, time_t t) {
  if (c == NULL) return;
  c->time = t;
}

char* ld_fmtpixel(ld_canvas* c, int x, int y) {
  // \x1b[xx;yymzz 14
  // 8/5/25 it's actually 11 because \x1b is 1 character and not 3
  // 8/11/25 i'll leave it at 14 for safety
  // 2/12/26 FUCK IT WE BALL
  if (c == NULL) return NULL;
  pixel p = ld_getpixel(c, x, y);
  char* temp = malloc(11);
  snprintf(temp, 11, "\x1b[%d;%dm%d%d", p + 30, p + 40, p, p);
  return temp;
}

void ld_FPbuf(ld_canvas* c, int x, int y, char* buffer) {
  if (c == NULL) return;
  pixel p = ld_getpixel(c, x, y);
  // 13/2/16 Mustard - Ballin'
  snprintf(buffer, 11, "\x1b[%d;%dm%d%d", p + 30, p + 40, p, p);
}