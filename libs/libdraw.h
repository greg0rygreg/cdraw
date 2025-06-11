#ifndef LIBDRAW_H
#define LIBDRAW_H
#include <time.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

struct canvas {
  int height;
  int width;
  bool** pixels;
  char* author;
  time_t time;
};

struct canvas* initCanvas(int h, int w);
void delCanvas(struct canvas* c);
void setAuthor(struct canvas* c, char* a);
void togglePixel(struct canvas* c, int x, int y);
void invertPixels(struct canvas* c);
void setTime(struct canvas* c, time_t t);
bool getPixel(struct canvas* c, int x, int y);
void setPixel(struct canvas* c, int x, int y, bool v);

#ifdef __cplusplus
}
#endif

#endif // LIBDRAW_H