#include "image.h"

// HW0 #1
// const Image& im: input image
// int x,y: pixel coordinates
// int ch: channel of interest
// returns the 0-based location of the pixel value in the data array
int pixel_address(const Image &im, int x, int y, int ch) {
  return (im.w) * (im.h) * ch + (im.w) * y + x;
}

// HW0 #1
// const Image& im: input image
// int x,y,ch: pixel coordinates and channel of interest
// returns the value of the clamped pixel at channel ch
float get_clamped_pixel(const Image &im, int x, int y, int ch) {
  int clamped_x = x >= im.w ? im.w - 1 : (x < 0 ? 0 : x);
  int clamped_y = y >= im.h ? im.h - 1 : (y < 0 ? 0 : y);
  return im.data[pixel_address(im, clamped_x, clamped_y, ch)];
}

// HW0 #1
// Image& im: input image
// int x,y,ch: pixel coordinates and channel of interest
void set_pixel(Image &im, int x, int y, int c, float value) {
  // Only set the pixel to the value if it's inside the image
  if (x < 0 || x > im.w || y < 0 || y > im.h) return;

  im.data[pixel_address(im, x, y, c)] = value;
}

// HW0 #2
// Copies an image
// Image& to: destination image
// const Image& from: source image
void copy_image(Image &to, const Image &from) {
  // allocating data for the new image
  to.data = (float *)calloc(from.w * from.h * from.c, sizeof(float));
  to.c = from.c;
  to.w = from.w;
  to.h = from.h;

  memcpy(to.data, from.data, from.w * from.h * from.c * sizeof(float));
}
