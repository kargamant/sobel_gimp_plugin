#include "buff.h"


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

void buff_free(Buff* buff)
{
	if(buff)
	{
		g_free(buff->buff);
		free(buff);
		buff=NULL;
	}
}

