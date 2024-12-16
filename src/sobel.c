#include <stdio.h>
#include "config.h"

static void
run (const gchar *name, gint nparams, const GimpParam  *param, gint *nreturn_vals, GimpParam **return_vals)
{
	static GimpParam  values[1];
	*nreturn_vals = 1;
	*return_vals  = values;
	values[0].type = GIMP_PDB_STATUS;
	values[0].data.d_status = GIMP_PDB_SUCCESS;

	printf("coool\n");

}

GimpPlugInInfo PLUG_IN_INFO = {
	NULL,
	NULL,
	query,
	run
};

MAIN();
