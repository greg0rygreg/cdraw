#ifndef LIBDRAW_H
#define LIBDRAW_H
#include <time.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ld_canvas {
  char** pixels;
  char* author;
  time_t time;
  int height;
  int width;
} ld_canvas;

typedef enum pixel {
  BLACK,
  RED,
  GREEN,
  YELLOW,
  BLUE,
  MAGENTA,
  CYAN,
  WHITE,
  UNKNOWN
} pixel;

// initialize a libdraw canvas
ld_canvas* ld_docanvas(int h, int w);

// delete a libdraw canvas
void ld_uncanvas(ld_canvas* c);

// set the author of a certain canvas to a certain name
void ld_author(ld_canvas* c, char* a);

// clamp a pixel (from BLACK to WHITE)
pixel ld_clamp(pixel c);

// format a pixel
char* ld_fmtpixel(ld_canvas* c, int x, int y);

// set the time of a certain canvas to a certain UNIX timestamp
// (defines creation time)
void ld_time(ld_canvas* c, time_t t);

// get a certain pixel from a certain canvas at a certain coordinate
pixel ld_getpixel(ld_canvas* c, int x, int y);

// set a certain pixel from a certain canvas at a certain coordinate
// to a certain `enum pixel` value
void ld_setpixel(ld_canvas* c, int x, int y, pixel v);

// fill a certain area of a certain canvas with a certain color
void ld_fill(ld_canvas* c, int x1, int y1, int x2, int y2, pixel v);

// format a pixel, but print it to `buffer`
void ld_FPbuf(ld_canvas* c, int x, int y, char* buffer);

// invert the colors of every pixel in a certain canvas
void ld_invertall(ld_canvas* c);

// invert the colors of a certain area in a certain canvas
void ld_invert(ld_canvas* c, int x1, int y1, int x2, int y2);

#ifdef __cplusplus
}
#endif

#endif // LIBDRAW_H