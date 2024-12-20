#pragma once
#include <libgimp/gimp.h>

void sobel(GimpDrawable* dr, int gr1[3][3], int gr2[3][3]);

void convolution(GimpPixelRgn* rgin, GimpPixelRgn* rgout, int channels, int matr[3][3], float (*brightness)(int, int, int));

void gradient_add(GimpPixelRgn* rgn1, GimpPixelRgn* rgn2, GimpPixelRgn* rgout,  int channels, float (*brightness)(int, int, int), float (*gradient)(int, int));

