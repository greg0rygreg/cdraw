#include "libdraw.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int clampI(int min, int max, int v) {
  return v < min ? min : (v > max ? max : v);
}

ld_canvas* ld_docanvas(int h, int w) {
  // pre-malloc checks
  int a = h * w;
  if (a == 0) return NULL;
  // mallocs
  ld_canvas* c = malloc(sizeof(ld_canvas));
  if (!c) return NULL;
  char* au = strdup("unknown");
  if (!au) {
    free(c);
    return NULL;
  }
  pixel* p = malloc(sizeof(pixel) * a);
  if (!p) {
    free(c);
    free(au);
    return NULL;
  }
  for (int i = 0; i < a; i++)
    p[i] = WHITE;
  // post-mallocs
  c->pixels = p;
  c->author = au;
  c->time = time(NULL);
  c->width = w;
  c->height = h;
  return c;
};

void ld_uncanvas(ld_canvas* c) {
  if (!c) return;
  free(c->pixels);
  free(c->author);
  free(c);
}

void ld_author(ld_canvas* c, char* a) {
  if (!c) return;
  if (c->author) free(c->author);
  c->author = a;
}

void ld_setpixel(ld_canvas* c, int x, int y, pixel v) {
  if (!c) return;
  int ax = x - 1;
  int ay = y - 1;
  if (ay >= 0 && ay <= c->height-1 && ax >= 0 && ax <= c->width-1)
    c->pixels[c->width * ay + ax] = clampI(BLACK, WHITE, v);
}

pixel ld_getpixel(ld_canvas* c, int x, int y) {
  if (c == NULL) return UNKNOWN;
  int ax = x - 1;
  int ay = y - 1;
  if (ay >= 0 && ay <= c->height-1 && ax >= 0 && ax <= c->width-1)
    return c->pixels[c->width * ay + ax];
  return UNKNOWN;
}

void ld_invertall(ld_canvas* c) {
  if (c == NULL) return;
  for (int y = 0; y <= c->height; y++) {
    for (int x = 0; x <= c->width; x++)
      ld_setpixel(c, x, y, ld_getpixel(c, x, y) ^ 7);
  }
}

void ld_invert(ld_canvas* c, int x1, int y1, int x2, int y2) {
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
    for (int x = x1; x <= x2; x++)
      ld_setpixel(c, x, y, ld_getpixel(c, x, y) ^ 7);
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