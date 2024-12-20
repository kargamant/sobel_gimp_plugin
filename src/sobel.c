#include <stdio.h>
#include "config.h"
#include "utils.h"

static void
run (const gchar *name, gint nparams, const GimpParam  *param, gint *nreturn_vals, GimpParam **return_vals)
{
	static GimpParam  values[1];
	*nreturn_vals = 1;
	*return_vals  = values;
	values[0].type = GIMP_PDB_STATUS;
	values[0].data.d_status = GIMP_PDB_SUCCESS;

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

	sobel(drawable, matr1, matr2);

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
