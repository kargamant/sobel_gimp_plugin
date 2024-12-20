#pragma once
#include <libgimp/gimp.h>
#include "buff.h"


void sobel(GimpDrawable* dr, int gr1[3][3], int gr2[3][3], float multiplier, float (*br)(int, int, int), float (*gr)(int, int));

void convolution(GimpPixelRgn* rgin, Buff* buff_out, int channels, int matr[3][3], float multiplier, float (*brightness)(int, int, int));

void gradient_add(Buff* buff1, Buff* buff2, GimpPixelRgn* rgout,  int channels, float (*brightness)(int, int, int), float (*gradient)(int, int));

void delete_border(GimpPixelRgn* rgout, int channels);


