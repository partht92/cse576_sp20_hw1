#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>

#include "image.h"

using namespace std;

// HW0 #3
// const Image& im: input image
// return the corresponding grayscale image
Image rgb_to_grayscale(const Image& im) {
  assert(im.c == 3);          // only accept RGB images
  Image gray(im.w, im.h, 1);  // create a new grayscale image (note: 1 channel)

  for (int i = 0; i < im.w; i++) {
    for (int j = 0; j < im.h; j++) {
      set_pixel(gray, i, j, 0,
                0.299 * im(i, j, 0) + 0.587 * im(i, j, 1) + .114 * im(i, j, 2));
    }
  }

  return gray;
}

// Example function that changes the color of a grayscale image
Image grayscale_to_rgb(const Image& im, float r, float g, float b) {
  assert(im.c == 1);
  Image rgb(im.w, im.h, 3);

  for (int q2 = 0; q2 < im.h; q2++)
    for (int q1 = 0; q1 < im.w; q1++) {
      rgb(q1, q2, 0) = r * im(q1, q2);
      rgb(q1, q2, 1) = g * im(q1, q2);
      rgb(q1, q2, 2) = b * im(q1, q2);
    }

  return rgb;
}

// HW0 #4
// Image& im: input image to be modified in-place
// int c: which channel to shift
// float v: how much to shift
void shift_image(Image& im, int c, float v) {
  assert(c >= 0 && c < im.c);  // needs to be a valid channel

  for (int i = 0; i < im.w; i++) {
    for (int j = 0; j < im.h; j++) {
      set_pixel(im, i, j, c, im(i, j, c) + v);
    }
  }
}

// HW0 #8
// Image& im: input image to be modified in-place
// int c: which channel to scale
// float v: how much to scale
void scale_image(Image& im, int c, float v) {
  assert(c >= 0 && c < im.c);  // needs to be a valid channel

  for (int i = 0; i < im.w; i++) {
    for (int j = 0; j < im.h; j++) {
      set_pixel(im, i, j, c, im(i, j, c) * v);
    }
  }
}

// HW0 #5
// Image& im: input image to be modified in-place
void clamp_image(Image& im) {
  for (int i = 0; i < im.w * im.h * im.c; i++) {
    if (im.data[i] < 0) im.data[i] = 0;
    if (im.data[i] > 1) im.data[i] = 1;
  }
}

// These might be handy
float max(float a, float b, float c) { return max({a, b, c}); }

float min(float a, float b, float c) { return min({a, b, c}); }

// HW0 #6
// Image& im: input image to be modified in-place
void rgb_to_hsv(Image& im) {
  assert(im.c == 3 && "only works for 3-channels images");

  for (int i = 0; i < im.w; i++) {
    for (int j = 0; j < im.h; j++) {
      float r = im(i, j, 0);
      float g = im(i, j, 1);
      float b = im(i, j, 2);
      float value = max(r, g, b);
      float chroma = value - min(r, g, b);
      float saturation = value == 0 ? 0 : chroma / value;
      float hue = 0;
      if (chroma != 0) {
        if (value == r) hue = (g - b) / chroma;
        if (value == g) hue = (b - r) / chroma + 2;
        if (value == b) hue = (r - g) / chroma + 4;
      }
      hue = hue < 0 ? hue / 6 + 1 : hue / 6;

      im(i, j, 0) = hue;
      im(i, j, 1) = saturation;
      im(i, j, 2) = value;
    }
  }
}

// HW0 #7
// Image& im: input image to be modified in-place
void hsv_to_rgb(Image& im) {
  assert(im.c == 3 && "only works for 3-channels images");

  for (int i = 0; i < im.w; i++) {
    for (int j = 0; j < im.h; j++) {
      float H = im(i, j, 0);
      float S = im(i, j, 1);
      float V = im(i, j, 2);

      // Given the H, S, V channels of an image:
      float C = V * S;
      float X = C * (1 - abs(fmod(6 * H, 2) - 1));
      float m = V - C;

      float threshold = 1.0 / 6;
      float R, G, B = 0;
      if (H < threshold) {
        R = C;
        G = X;
        B = 0;
      } else if (H < 2 * threshold) {
        R = X;
        G = C;
        B = 0;
      } else if (H < 3 * threshold) {
        R = 0;
        G = C;
        B = X;
      } else if (H < 4 * threshold) {
        R = 0;
        G = X;
        B = C;
      } else if (H < 5 * threshold) {
        R = X;
        G = 0;
        B = C;
      } else {
        R = C;
        G = 0;
        B = X;
      }

      im(i, j, 0) = R + m;
      im(i, j, 1) = G + m;
      im(i, j, 2) = B + m;
    }
  }
}

// HW0 #9
// Image& im: input image to be modified in-place
void rgb_to_lch(Image& im) {
  assert(im.c == 3 && "only works for 3-channels images");

  // TODO: Convert all pixels from RGB format to LCH format

  NOT_IMPLEMENTED();
}

// HW0 #9
// Image& im: input image to be modified in-place
void lch_to_rgb(Image& im) {
  assert(im.c == 3 && "only works for 3-channels images");

  // TODO: Convert all pixels from LCH format to RGB format

  NOT_IMPLEMENTED();
}

// Implementation of member functions
void Image::clamp(void) { clamp_image(*this); }
void Image::shift(int c, float v) { shift_image(*this, c, v); }
void Image::scale(int c, float v) { scale_image(*this, c, v); }

void Image::HSVtoRGB(void) { hsv_to_rgb(*this); }
void Image::RGBtoHSV(void) { rgb_to_hsv(*this); }
void Image::LCHtoRGB(void) { lch_to_rgb(*this); }
void Image::RGBtoLCH(void) { rgb_to_lch(*this); }
