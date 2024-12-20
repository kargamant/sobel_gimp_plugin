#include "utils.h"
#include <stdlib.h>
#include "buff.h"
#include "metrics.h"


void convolution(GimpPixelRgn* rgin, GimpPixelRgn* rgout, int channels, int matr[3][3], float (*brightness)(int, int, int))
{
	if(rgin->w!=rgout->w || rgin->h!=rgout->h)
		return;
	
	Buff* buff_in = buff_init(rgin, channels);
	Buff* buff_out = buff_init(rgin, channels);

	for(int i=1; i<rgin->h-1; i++)
	{
		for(int j=1; j<rgin->w-1; j++)
		{
			//	brightness version
			if(brightness)
			{
				int output=0;
				for(int m_i=0; m_i<3; m_i++)
				{
					for(int m_j=0; m_j<3; m_j++)
					{
						int r = buff_get_pixel_channel(buff_in, i+(m_i-1), j+(m_j-1), 0);
						int g = buff_get_pixel_channel(buff_in, i+(m_i-1), j+(m_j-1), 1);
						int b = buff_get_pixel_channel(buff_in, i+(m_i-1), j+(m_j-1), 2);
						output += matr[m_i][m_j]*brightness(r, g, b);
					}
				}
				buff_set_pixel_channel(buff_out, i, j, 0, output);
				buff_set_pixel_channel(buff_out, i, j, 1, output);
				buff_set_pixel_channel(buff_out, i, j, 2, output);
			}
			else
			{
			//	channel version
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
	}
	gimp_pixel_rgn_set_rect(rgout, buff_out->buff, rgout->x, rgout->y, rgout->w, rgout->h);
	buff_free(buff_in);
	buff_free(buff_out);
}

void gradient_add(GimpPixelRgn* rgn1, GimpPixelRgn* rgn2, GimpPixelRgn* rgout,  int channels, float (*brightness)(int, int, int), float (*gradient)(int, int))
{
	if(gradient==NULL)
		gradient=&gradient_sqrt;

	Buff* buff1 = buff_init(rgn1, channels);
	Buff* buff2 = buff_init(rgn2, channels);
	Buff* buff_out = buff_init(rgout, channels);

	int w=buff1->w;
	int h=buff1->h;

	for(int i=0; i<h; i++)
	{
		for(int j=0; j<w; j++)
		{
			for(int k=0; k<channels; k++)
			{
				guchar gr1 = buff_get_pixel_channel(buff1, i, j, k);
				guchar gr2 = buff_get_pixel_channel(buff2, i, j, k);
				buff_set_pixel_channel(buff_out, i, j, k, gradient(gr1, gr2));
			}
		}
	}
	gimp_pixel_rgn_set_rect(rgout, buff_out->buff, rgout->x, rgout->y, rgout->w, rgout->h);
	buff_free(buff1);
	buff_free(buff2);
	buff_free(buff_out);
}

void sobel(GimpDrawable* dr, int gr1[3][3], int gr2[3][3])
{
	gint x1, y1, x2, y2;
	gimp_drawable_mask_bounds(dr->drawable_id, &x1, &y1, &x2, &y2);
	int channels = gimp_drawable_bpp(dr->drawable_id);

	GimpPixelRgn rgin, rgout1, rgout2, rgout;
	gimp_pixel_rgn_init(&rgin, dr, 0, 0, x2-x1, y2-y1, FALSE, FALSE);
	gimp_pixel_rgn_init(&rgout1, dr, 0, 0, x2-x1, y2-y1, TRUE, FALSE);
	gimp_pixel_rgn_init(&rgout2, dr, 0, 0, x2-x1, y2-y1, TRUE, FALSE);
	gimp_pixel_rgn_init(&rgout, dr, 0, 0, x2-x1, y2-y1, TRUE, FALSE);
	
	convolution(&rgin, &rgout1, channels, gr1, &brightness_humanized);
	convolution(&rgin, &rgout2, channels, gr2, &brightness_humanized);
	gradient_add(&rgout1, &rgout2, &rgout, channels, &brightness_humanized, &gradient_sqrt);	

	gimp_drawable_flush(dr);
	gimp_drawable_update(dr->drawable_id, x1, y1, x2-x1, y2-y1);
}













