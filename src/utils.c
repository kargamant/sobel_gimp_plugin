#include "utils.h"
#include <stdlib.h>
#include "buff.h"

float brightness(int r, int g, int b)
{
	return (r+g+b)/3;
}


float brightness_humanized(int r, int g, int b)
{
	return 0.21*r + 0.72*g + 0.07*b;
}

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

void sobel(GimpDrawable* dr, int gr1[3][3], int gr2[3][3])
{
	gint x1, y1, x2, y2;
	gimp_drawable_mask_bounds(dr->drawable_id, &x1, &y1, &x2, &y2);
	int channels = gimp_drawable_bpp(dr->drawable_id);

	GimpPixelRgn rgin, rgout;
	gimp_pixel_rgn_init(&rgin, dr, 0, 0, x2-x1, y2-y1, FALSE, FALSE);
	gimp_pixel_rgn_init(&rgout, dr, 0, 0, x2-x1, y2-y1, TRUE, FALSE);
	
	convolution(&rgin, &rgout, channels, gr1, NULL);
	gimp_drawable_flush(dr);
	gimp_drawable_update(dr->drawable_id, x1, y1, x2-x1, y2-y1);
}














