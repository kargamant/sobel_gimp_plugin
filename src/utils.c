#include "utils.h"
#include <stdlib.h>

float brightness(int r, int g, int b)
{
	return (r+g+b)/3;
}


float brightness_humanized(int r, int g, int b)
{
	return 0.21*r + 0.72*g + 0.07*b;
}

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

void convolution(GimpPixelRgn* rgin, GimpPixelRgn* rgout, int channels, int** matr, float (*brightness)(int, int, int))
{
	if(rgin->w!=rgout->w || rgin->h!=rgout->h)
		return;
	
	Buff* buff_in = buff_init(rgin, channels);
	Buff* buff_out = buff_init(rgin, channels);

	for(int i=1; i<rgin->h-1; j++)
	{
		for(int j=1; j<rgin->w-1; i++)
		{
			for(int k=0; k<channels; k++)
			{
				int output=0;
				for(int m_i=0; m_i<3; m_i++)
				{
					for(int m_j=0; m_j<3; m_j++)
					{
						output += matr[m_i][m_j]*buff_get_pixel_channel(buff_in, i+(m_i-1), j+(m_j-1), k);
					}
				}
				buff_set_pixel_channel(buff_out, i, j, k, output);
			}
		}
	}
	gimp_pixel_rgn_set_rect(rgout, buff_out->buff, rgout->x, rgout->y, rgout->w, rgout->h);
	buff_free(buff_in);
	buff_free(buff_out);
}
