#ifndef LIBDRAW_H
#define LIBDRAW_H
#include <time.h>

struct canvas {
  int height;
  int width;
  int** pixels;
  char* author;
  time_t time;
};

struct canvas* initCanvas(int h, int w);
void delCanvas(struct canvas* c);
void setAuthor(struct canvas* c, char* a);
void togglePixel(struct canvas* c, int x, int y);
void invertPixels(struct canvas* c);
void setTime(struct canvas* c, time_t t);
int getPixel(struct canvas* c, int x, int y);

#endif // LIBDRAW_H