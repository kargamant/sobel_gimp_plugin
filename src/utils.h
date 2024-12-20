#include <libgimp/gimp.h>

void sobel(GimpDrawable* dr, int** gr1, int** gr2);

void convolution(GimpPixelRgn* rgin, GimpPixelRgn* rgout, int channels, int** matr, float (*brightness)(int, int, int));
float brightness_average(int r, int g, int b);
float brightness_humanized(int r, int g, int b);

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

void buff_free(Buff* buff);
