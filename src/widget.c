#include <libgimp/gimp.h>
#include <libgimp/gimpui.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include "widget.h"
#include <string.h>

gboolean sobel_dialogue(SobelParams* params)
{
	GtkWidget *dialog;
	GtkWidget *main_vbox;
	GtkWidget *main_hbox;
	GtkWidget *frame;
	GtkWidget *multiplier_label;
	GtkWidget *shift_label;
	GtkWidget *alignment;
	GtkWidget *spinbutton_multiplier;
	GtkObject *spinbutton_adj_multiplier;
	GtkWidget *spinbutton_shift;
	GtkObject *spinbutton_adj_shift;
	GtkWidget *frame_label;
	gboolean   run;

	gimp_ui_init ("sobel", FALSE);

	dialog = gimp_dialog_new ("Sobel", "sobel",
							NULL, 0,
							gimp_standard_help_func, "plug-in-sobel",
							GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
							GTK_STOCK_OK, GTK_RESPONSE_OK,
							NULL);
	main_vbox = gtk_vbox_new (FALSE, 6);
	gtk_container_add (GTK_CONTAINER (GTK_DIALOG (dialog)->vbox), main_vbox);
	gtk_widget_show (main_vbox);

	frame = gtk_frame_new (NULL);
	gtk_widget_show (frame);
	gtk_box_pack_start (GTK_BOX (main_vbox), frame, TRUE, TRUE, 0);
	gtk_container_set_border_width (GTK_CONTAINER (frame), 6);

	alignment = gtk_alignment_new (0.5, 0.5, 1, 1);
	gtk_widget_show (alignment);
	gtk_container_add (GTK_CONTAINER (frame), alignment);
	gtk_alignment_set_padding (GTK_ALIGNMENT (alignment), 6, 6, 6, 6);

	main_hbox = gtk_hbox_new (FALSE, 0);
	gtk_widget_show (main_hbox);
	gtk_container_add (GTK_CONTAINER (alignment), main_hbox);

	// multiplier field
	multiplier_label = gtk_label_new_with_mnemonic ("_Multiplier:");
	gtk_widget_show (multiplier_label);
	gtk_box_pack_start (GTK_BOX (main_hbox), multiplier_label, FALSE, FALSE, 6);
	gtk_label_set_justify (GTK_LABEL (multiplier_label), GTK_JUSTIFY_RIGHT);

	GtkWidget *multiplier_entry = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(multiplier_entry), "0.0");
	gtk_widget_show(multiplier_entry);
	gtk_box_pack_start (GTK_BOX (main_hbox), multiplier_entry, FALSE, FALSE, 6);

	// brightness metric choice
	GtkWidget *brightness_combo = gtk_combo_box_text_new();
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (brightness_combo), "brightness_average");
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (brightness_combo), "brightness_humanized");
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (brightness_combo), "none");
	gtk_combo_box_set_active (GTK_COMBO_BOX (brightness_combo), 0);
	gtk_widget_show(brightness_combo);
	gtk_box_pack_start (GTK_BOX (main_hbox), brightness_combo, FALSE, FALSE, 6);

	// gradient metric choice
	GtkWidget *gradient_combo = gtk_combo_box_text_new();
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (gradient_combo), "gradient_abs");
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (gradient_combo), "gradient_sqrt");
	gtk_combo_box_set_active (GTK_COMBO_BOX (gradient_combo), 0);
	gtk_widget_show(gradient_combo);
	gtk_box_pack_start (GTK_BOX (main_hbox), gradient_combo, FALSE, FALSE, 6);

	gtk_widget_show (dialog);

	run = (gimp_dialog_run (GIMP_DIALOG (dialog)) == GTK_RESPONSE_OK);

	const gchar *text = gtk_entry_get_text(GTK_ENTRY(multiplier_entry));
	char *endptr;
	params->multiplier = strtof(text, &endptr);
	
	gchar *selected_brightness = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(brightness_combo));
	if(strcmp(selected_brightness, "brightness_average") == 0)
		params->brightness = AVERAGE;
	else if(strcmp(selected_brightness, "brightness_humanized") == 0)
		params->brightness = HUMANIZED;
	else
		params->brightness = NONE;

	gchar *selected_gradient = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(gradient_combo));
	if(strcmp(selected_gradient, "gradient_abs") == 0)
		params->gradient = ABS;
	else
		params->gradient = SQRT;

	printf("params: %f, %d, %d\n", params->multiplier, params->brightness, params->gradient);

	gtk_widget_destroy (dialog);

	return run;
}

