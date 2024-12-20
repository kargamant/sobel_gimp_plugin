#include <libgimp/gimp.h>
#include <libgimp/gimpui.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include "widget.h"

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

	multiplier_label = gtk_label_new_with_mnemonic ("_Multiplier:");
	gtk_widget_show (multiplier_label);
	gtk_box_pack_start (GTK_BOX (main_hbox), multiplier_label, FALSE, FALSE, 6);
	gtk_label_set_justify (GTK_LABEL (multiplier_label), GTK_JUSTIFY_RIGHT);

	/*spinbutton_adj_multiplier = gtk_adjustment_new (3, 1, 1000, 1, 5, 5);
	spinbutton_multiplier = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton_adj_multiplier), 1, 0);
	gtk_widget_show (spinbutton_multiplier);
	gtk_box_pack_start (GTK_BOX (main_hbox), spinbutton_multiplier, FALSE, FALSE, 6);
	gtk_spin_button_set_numeric (GTK_SPIN_BUTTON (spinbutton_multiplier), TRUE);

	g_signal_connect (spinbutton_adj_multiplier, "value_changed",
								  G_CALLBACK (gimp_int_adjustment_update),
												  &params->multiplier);*/
	GtkWidget *float_entry = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(float_entry), "0.0");
	gtk_widget_show(float_entry);
	gtk_box_pack_start (GTK_BOX (main_hbox), float_entry, FALSE, FALSE, 6);

	gtk_widget_show (dialog);

	run = (gimp_dialog_run (GIMP_DIALOG (dialog)) == GTK_RESPONSE_OK);

	const gchar *text = gtk_entry_get_text(GTK_ENTRY(float_entry));
	char *endptr;
	params->multiplier = strtof(text, &endptr);
	
	printf("params: %f\n", params->multiplier);

	gtk_widget_destroy (dialog);

	return run;
}

