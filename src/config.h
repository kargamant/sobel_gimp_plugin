#pragma once
#include <libgimp/gimp.h>

static void
query (void)
{
	static GimpParamDef args[] = {
	{
	       GIMP_PDB_INT32,
	       "run-mode",
	       "Run mode"						    
	},
	{
		GIMP_PDB_IMAGE,
		"image",
		"Input image"
	},
	{
		GIMP_PDB_DRAWABLE,
		"drawable",
		"Input drawable"
	}
	};
	gimp_install_procedure (
	"plug-in-sobel",
	"Sobel",
	"Applies sobel operator to image",
    	"Egor Deriglazov",
        "Copyright Egor Deriglazov",
	"2024",
	"sobel",
	"RGB*, GRAY*",
	GIMP_PLUGIN,
	G_N_ELEMENTS (args), 0,
	args, NULL);

	gimp_plugin_menu_register ("plug-in-sobel", "<Image>/Filters/MyFilters"); 
}

typedef struct
{
	float multiplier;
	short brightness;
	short gradient_abs;
}SobelParams;
