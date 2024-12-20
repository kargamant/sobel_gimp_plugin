#include "buff.h"
#include "metrics.h"

Buff* buff_init(GimpPixelRgn* rgn, int channels)
{
	guchar* buff=g_new(guchar, rgn->h*rgn->w*channels);
	gimp_pixel_rgn_get_rect(rgn, buff, rgn->x, rgn->y, rgn->w, rgn->h);
	
	Buff* bf = (Buff*)malloc(sizeof(Buff));
	bf->buff=buff;
	bf->w=rgn->w;
	bf->h=rgn->h;
	bf->c=channels;
	return bf;
}

guchar buff_get_pixel_channel(Buff* buff, int i, int j, int c)
{
	return buff->buff[(i*buff->w+j)*buff->c + c];
}

void buff_set_pixel_channel(Buff* buff, int i, int j, int c, int new_c)
{
	buff->buff[(i*buff->w+j)*buff->c + c] = new_c;
}

void buff_set_pixel(Buff* buff, int i, int j, int r, int g, int b)
{
	buff_set_pixel_channel(buff, i, j, 0, r);
	buff_set_pixel_channel(buff, i, j, 1, g);
	buff_set_pixel_channel(buff, i, j, 2, b);
}

float buff_get_pixel_brightness(Buff* buff, int i, int j, float (*brightness)(int, int, int))
{
	guchar r = buff_get_pixel_channel(buff, i, j, 0);
	guchar g = buff_get_pixel_channel(buff, i, j, 1);
	guchar b = buff_get_pixel_channel(buff, i, j, 2);
	return brightness(r, g, b);
}

void buff_free(Buff* buff)
{
	if(buff)
	{
		g_free(buff->buff);
		free(buff);
		buff=NULL;
	}
}

