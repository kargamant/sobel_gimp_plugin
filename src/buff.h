#pragma once
#include <libgimp/gimp.h>

typedef struct Buff
{
	guchar* buff;
	int w; //width
	int h; //height
	int c; //channels
} Buff;

Buff* buff_init(GimpPixelRgn* rgn, int channels);

guchar buff_get_pixel_channel(Buff* buff, int i, int j, int c); // i - row number, j - column number

void buff_set_pixel_channel(Buff* buff, int i, int j, int c, int new_c); // i - row number, j - column number

void buff_set_pixel(Buff* buff, int i, int j, int r, int g, int b);

float buff_get_pixel_brightness(Buff* buff, int i, int j, float (*brightness)(int, int, int));

void buff_free(Buff* buff);
