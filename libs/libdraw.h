#ifndef LIBDRAW_H
#define LIBDRAW_H
#include <time.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct canvas {
  int height;
  int width;
  char** pixels;
  char* author;
  time_t time;
} Canvas;

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

// initialize a libdraw canvas
struct canvas* initCanvas(int h, int w);

// delete a libdraw canvas
void delCanvas(struct canvas* c);

// set the author of a certain canvas to a certain name
void setAuthor(struct canvas* c, char* a);

// clamp a pixel (from BLACK to WHITE)
enum PIXEL clampPixel(enum PIXEL c);
// format a pixel
char* formatPixel(struct canvas* c, int x, int y);

// set the time of a certain canvas to a certain UNIX timestamp
// (defines creation time)
void setTime(struct canvas* c, time_t t);

// get a certain pixel from a certain canvas at a certain coordinate
enum PIXEL getPixel(struct canvas* c, int x, int y);

// set a certain pixel from a certain canvas at a certain coordinate
// to a certain `enum PIXEL` value
void setPixel(struct canvas* c, int x, int y, enum PIXEL v);

// fill a part of a certain canvas with a certain color
void fillPixels(Canvas* c, int x1, int y1, int x2, int y2, enum PIXEL v);

// format a pixel, but print it to `buffer`
void formatPixelB(Canvas* c, int x, int y, char* buffer, size_t len);
void invertPixels(struct canvas* c);

#ifdef __cplusplus
}
#endif

#endif // LIBDRAW_H