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
  char** pixels;
  char* author;
  time_t time;
};

enum PIXEL {
  BLACK,
  RED,
  GREEN,
  YELLOW,
  BLUE,
  MAGENTA,
  CYAN,
  WHITE,
  UNKNOWN
};

struct canvas* initCanvas(int h, int w);
void delCanvas(struct canvas* c);
void setAuthor(struct canvas* c, char* a);
enum PIXEL clampPixel(enum PIXEL c);
char* formatPixel(struct canvas* c, int x, int y);
void setTime(struct canvas* c, time_t t);
enum PIXEL getPixel(struct canvas* c, int x, int y);
void setPixel(struct canvas* c, int x, int y, enum PIXEL v);
//void invertPixels(struct canvas* c);

#ifdef __cplusplus
}
#endif

#endif // LIBDRAW_H