#include "utils.h"
#include <stdlib.h>
#include "buff.h"
#include "metrics.h"


void convolution(GimpPixelRgn* rgin, Buff* buff_out, int channels, int matr[3][3],  float multiplier, float (*brightness)(int, int, int))
{
	if(rgin->w!=buff_out->w || rgin->h!=buff_out->h)
		return;
	
	Buff* buff_in = buff_init(rgin, channels);

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
						output += multiplier * matr[m_i][m_j]*buff_get_pixel_brightness(buff_in, i+(m_i-1), j+(m_j-1), brightness);
					}
				}
				buff_set_pixel(buff_out, i, j, output, output, output);
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
	buff_free(buff_in);
}

void gradient_add(Buff* buff1, Buff* buff2, GimpPixelRgn* rgout,  int channels, float (*brightness)(int, int, int), float (*gradient)(int, int))
{
	if(gradient==NULL)
		gradient=&gradient_sqrt;

	Buff* buff_out = buff_init(rgout, channels);

	int w=buff1->w;
	int h=buff1->h;

	for(int i=0; i<h; i++)
	{
		for(int j=0; j<w; j++)
		{
			if(brightness)
			{
				float br1 = buff_get_pixel_brightness(buff1, i, j, brightness);
				float br2 = buff_get_pixel_brightness(buff2, i, j, brightness);

				float gr=gradient(br1, br2);
				buff_set_pixel(buff_out, i, j, gr, gr, gr);
			}
			else
			{
				for(int k=0; k<channels; k++)
				{
					guchar gr1 = buff_get_pixel_channel(buff1, i, j, k);
					guchar gr2 = buff_get_pixel_channel(buff2, i, j, k);
					buff_set_pixel_channel(buff_out, i, j, k, gradient(gr1, gr2));
				}
			}
		}
	}
	gimp_pixel_rgn_set_rect(rgout, buff_out->buff, rgout->x, rgout->y, rgout->w, rgout->h);
	buff_free(buff_out);
}

void delete_border(GimpPixelRgn* rgout, int channels)
{
	Buff* buff = buff_init(rgout, channels);

	int w=buff->w;
	int h=buff->h;
	for(int j=0; j<w-1; j++)
	{
		//printf("\nj: %d / %d\n", j, w);
		buff_set_pixel(buff, 0, j, 0, 0, 0);
		buff_set_pixel(buff, h-1, j, 0, 0, 0);
	}

	for(int i=0; i<h-1; i++)
	{
		buff_set_pixel(buff, i, 0, 0, 0, 0);
		buff_set_pixel(buff, i, w-1, 0, 0, 0);
	}
	gimp_pixel_rgn_set_rect(rgout, buff->buff, rgout->x, rgout->y, rgout->w, rgout->h);
	buff_free(buff);
}

void sobel(GimpDrawable* dr, int gr1[3][3], int gr2[3][3])
{
	gint x1, y1, x2, y2;
	gimp_drawable_mask_bounds(dr->drawable_id, &x1, &y1, &x2, &y2);
	int channels = gimp_drawable_bpp(dr->drawable_id);

	GimpPixelRgn rgin, rgout;
	gimp_pixel_rgn_init(&rgin, dr, 0, 0, x2-x1, y2-y1, FALSE, FALSE);
	gimp_pixel_rgn_init(&rgout, dr, 0, 0, x2-x1, y2-y1, TRUE, FALSE);
	
	Buff* buff_out1 = buff_init(&rgin, channels);
	Buff* buff_out2 = buff_init(&rgin, channels);
	
	convolution(&rgin, buff_out1, channels, gr1, 0.03, &brightness_humanized);
	convolution(&rgin, buff_out2, channels, gr2, 0.03, &brightness_humanized);
	gradient_add(buff_out1, buff_out2, &rgout, channels, &brightness_humanized, &gradient_abs);
	printf("\ndeleting border\n");
	delete_border(&rgout, channels);
	
	buff_free(buff_out1);
	buff_free(buff_out2);

	gimp_drawable_flush(dr);
	gimp_drawable_update(dr->drawable_id, x1, y1, x2-x1, y2-y1);
}














