/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   stacks.c
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 11 April 2019, 15:07
 * 
 * Program to test the functionality of the stack feature of GTK.
 */

#include <stdio.h>
#include <stdlib.h>

#include <gtk-3.0/gtk/gtk.h>


typedef struct {
	// All the widgets on the form go into here
	GtkWidget *w_lbl_box_view_data;
	GtkWidget *w_txt_enter_data_pg1;
	GtkWidget *w_btn_update_text_pg1;
} app_widgets;

/*
 * 
 */
int main(int argc, char** argv) {

	GtkBuilder      *builder; 
    GtkWidget       *window;
	
	GError			*err = NULL;	// holds any error that occurs within GTK
	
    // instantiate structure, allocating memory for it
    app_widgets        *widgets = g_slice_new(app_widgets);
	
	// initialize GTK library and pass it in command line parameters
	gtk_init(&argc, &argv);

	// build the gui
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "gui_files/stacks.glade", &err);
	
	// check if the gui has opened.
	if (err != NULL) {
        fprintf (stderr, "Unable to read file: %s\n", err->message);
        g_error_free(err);
        return 1;
    }
	
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
	
	// build the structure of widget pointers
	widgets->w_lbl_box_view_data  = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_box_view_data"));
	widgets->w_txt_enter_data_pg1  = GTK_WIDGET(gtk_builder_get_object(builder, "txt_enter_data_pg1"));
	widgets->w_btn_update_text_pg1  = GTK_WIDGET(gtk_builder_get_object(builder, "btn_update_text_pg1"));
    
	// connect the widgets to the signal handler
	gtk_builder_connect_signals(builder, widgets);    // note: second parameter points to widgets
    g_object_unref(builder);
 
	// setup the entry field
	gtk_entry_set_text(GTK_ENTRY(widgets->w_txt_enter_data_pg1), "edit me");

    gtk_widget_show(window);                
    gtk_main();
    // free up memory used by widget structure, probably not necessary as OS will
    // reclaim memory from application after it exits
    g_slice_free(app_widgets, widgets);
	
	return 0;
}

// called when window is closed
void on_window_main_destroy()
{
    printf("In on window main destroy\n");
    gtk_main_quit();
    
    exit(0);
}

// called when the button is pressed
// *button is the object that received the signal
// the second parameter is the user data passed back from the signal handler that was defined above
void on_btn_update_text_pg1_clicked(GtkButton *button, app_widgets *app_wdgts)
{
	const gchar		*lbl_data;			// holder for the data being viewed / edited
	
	printf("Button has been clicked!\n");
	// get the value from page 1 text field
	lbl_data = gtk_entry_get_text(GTK_ENTRY(app_wdgts->w_txt_enter_data_pg1));
	printf("label data retreived:%s\n", lbl_data);
	// populate the page 0 label with the new value
	gtk_label_set_text(GTK_LABEL(app_wdgts->w_lbl_box_view_data), lbl_data);
}
