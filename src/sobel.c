#include <stdio.h>
#include "config.h"
#include "utils.h"
#include "widget.h"
#include "metrics.h"

SobelParams params;

static void
run (const gchar *name, gint nparams, const GimpParam  *param, gint *nreturn_vals, GimpParam **return_vals)
{
	static GimpParam  values[1];
	*nreturn_vals = 1;
	*return_vals  = values;
	values[0].type = GIMP_PDB_STATUS;
	values[0].data.d_status = GIMP_PDB_SUCCESS;

	if(!sobel_dialogue(&params))
		return;

	GimpDrawable* drawable = gimp_drawable_get(param[2].data.d_drawable);
	
	int matr1[3][3];
	matr1[0][0]=-1;
	matr1[0][1]=-2;
	matr1[0][2]=-1;
	matr1[1][0]=0;
	matr1[1][1]=0;
	matr1[1][2]=0;
	matr1[2][0]=1;
	matr1[2][1]=2;
	matr1[2][2]=1;

	int matr2[3][3];
	matr2[0][0]=1;
	matr2[0][1]=0;
	matr2[0][2]=-1;
	matr2[1][0]=2;
	matr2[1][1]=0;
	matr2[1][2]=-2;
	matr2[2][0]=1;
	matr2[2][1]=0;
	matr2[2][2]=-1;
	
	float (*br)(int, int, int);
	switch(params.brightness)
	{
		case NONE:
			br=NULL;
			break;
		case AVERAGE:
			br=&brightness_average;
			break;
		case HUMANIZED:
			br=&brightness_humanized;
			break;
	}
	float (*gr)(int, int);
	switch(params.gradient)
	{
		case ABS:
			gr=&gradient_abs;
			break;
		case SQRT:
			gr=&gradient_sqrt;
			break;
	}

	sobel(drawable, matr1, matr2, params.multiplier, br, gr);

	gimp_displays_flush();
	gimp_drawable_detach(drawable);
}

GimpPlugInInfo PLUG_IN_INFO = {
	NULL,
	NULL,
	query,
	run
};

MAIN();
