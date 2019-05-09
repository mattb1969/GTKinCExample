/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   textView.c
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 11 April 2019, 15:07
 * 
 * Program to test the functionality of the text view feature of GTK.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <gtk-3.0/gtk/gtk.h>
#include <glib/gprintf.h>

 
/*****************************************************************************
 Global Constant and Type Definitions
*****************************************************************************/

#define WINWIDTH 600
#define WINHEIGHT 600

typedef struct AppState {
	GtkWidget *window ;
	GtkWidget *text_view ;
	GtkWidget *open_button ;
	GtkWidget *print_button ; 
 }  AppState ;
  
/*****************************************************************************
 Callback Function Prototypes
*****************************************************************************/

void on_open_button ( GtkWidget *button , AppState *app_state ); 
void on_print_button ( GtkWidget *button , AppState *app_state );

/*****************************************************************************
 Main program
*****************************************************************************/

int main(int argc, char *argv[]) {
	
	GtkWidget	*scrolled_window ; 
	GtkWidget	*vbox;
	GtkWidget	*hbox;
	AppState	app_state ;

	gtk_init (&argc , &argv );
	
	/* Create the top−level window */ 
	app_state.window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (app_state.window), "Text Viewer ");
	
	/* Set a decent default size for the window. */ 
	gtk_window_set_default_size (GTK_WINDOW (app_state.window), WINWIDTH, WINHEIGHT ) ;
	g_signal_connect (G_OBJECT (app_state.window), "destroy",
						G_CALLBACK (gtk_main_quit), NULL);
	
	//vbox = gtk_vbox_new (FALSE, 2);
	vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 2);
	gtk_container_add (GTK_CONTAINER ( app_state.window ) , vbox ) ;
	
	/* Create the textview and give it some margins. */
	app_state.text_view = gtk_text_view_new ( ) ; 
	gtk_text_view_set_left_margin (GTK_TEXT_VIEW (app_state.text_view), 10); 
	gtk_text_view_set_right_margin (GTK_TEXT_VIEW ( app_state.text_view ) , 10 ) ;

	scrolled_window = gtk_scrolled_window_new (NULL, NULL) ;
	gtk_container_add (GTK_CONTAINER ( scrolled_window ) , app_state.text_view ) ; 
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW ( scrolled_window ) ,
										GTK_POLICY_AUTOMATIC,
										GTK_POLICY_ALWAYS) ; 
	gtk_box_pack_start (GTK_BOX ( vbox ) , scrolled_window , 1 , 1 , 0 ) ;
	
	/* Put an hbox below the textview to store the buttons */
	//hbox = gtk_hbox_new (FALSE, 2);
	hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 2);
	gtk_box_pack_start (GTK_BOX (vbox), hbox, 0, 0, 0);
	
	/* Create the open and print buttons, pack them into the hbox, and attach to their callbacks .*/
	app_state.open_button = gtk_button_new_with_label ("Open File ");
	gtk_box_pack_start (GTK_BOX ( hbox ) , app_state.open_button , 0 , 0, 0);
	g_signal_connect (G_OBJECT (app_state.open_button), "clicked",
						G_CALLBACK (on_open_button), &app_state ) ;

	app_state.print_button = gtk_button_new_with_label (" Print to Terminal");
	gtk_box_pack_start (GTK_BOX ( hbox ) , app_state.print_button , 0 , 0, 0);
	g_signal_connect (G_OBJECT (app_state.print_button), "clicked",
						G_CALLBACK (on_print_button), &app_state ) ;

	gtk_widget_set_sensitive(app_state.open_button, TRUE); 
	gtk_widget_set_sensitive(app_state.print_button , FALSE); 
	gtk_widget_show_all ( app_state.window ) ;

	gtk_main ( ) ; 
	return 0;
}

/*****************************************************************************
 Callback Function Definitions
*****************************************************************************/

/*****************************************************************************
 on_open_button
*****************************************************************************/

void on_open_button ( GtkWidget *button , AppState *app_state){
	
	GtkTextBuffer	*buffer ;
	GtkFileFilter	*filter;
	GtkWidget		*dialog ;
	int				result;
	gchar			*filename ;
	GError			*error = NULL;
	guint			nBytesInBuf ;
	gchar			*contents ;

	//dialog = gtk_file_chooser_dialog_new ("Select File ..." , 
	//										GTK_WINDOW (app_state->window),
	//										GTK_FILE_CHOOSER_ACTION_OPEN, 
	//										GTK_STOCK_OK, GTK_RESPONSE_ACCEPT, 
	//										GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);

	dialog = gtk_file_chooser_dialog_new ("Select File ..." , 
											GTK_WINDOW (app_state->window),
											GTK_FILE_CHOOSER_ACTION_OPEN, 
											("_Ok"), GTK_RESPONSE_ACCEPT, 
											("_Cancel"), GTK_RESPONSE_CANCEL, 
											NULL);	
	filter = gtk_file_filter_new ();
	gtk_file_filter_set_name( filter , "Text Files "); 
	//gtk_file_filter_add_mime_type( filter , "text /*");
	gtk_file_filter_add_pattern (filter, "*.*");
	gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter); 
	gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER ( dialog ) ,g_get_home_dir ( ) ) ;
  
	/* Run the dialog modally and get the user response */ 
	result = gtk_dialog_run (GTK_DIALOG (dialog));
    
	switch ( result ) {
		case GTK_RESPONSE_ACCEPT:
			filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER ( dialog )); 
			gtk_widget_destroy ( dialog );
			break ;
		case GTK_RESPONSE_DELETE_EVENT: 
		case GTK_RESPONSE_CANCEL:
		case GTK_RESPONSE_NONE:
			gtk_widget_destroy ( dialog ); 
		return ;
	}
	
	/* This should not happen, but to be safe .. */ 
	if (NULL== filename) {
		GtkWidget *msg ;
		msg = gtk_message_dialog_new (GTK_WINDOW (app_state->window),
										GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK,
										"Failed to get file "); 
		gtk_dialog_run (GTK_DIALOG (msg ) ) ;
		gtk_widget_destroy (msg); 
		return ;
	}
	
	/* Obtaining the buffer associated with the widget. */
	buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (app_state->text_view ));
	
	/* Use the filename to read its contents into a gchar* string contents */ 
	if (! g_file_get_contents( filename , &contents , &nBytesInBuf , &error )) {
		g_printf(error->message) ; 
		g_clear_error(&error ); 
		g_free(filename );
		exit (1);
	}
	
	/* Success, so copy contents into buffer and free the contents and filename strings */
	gtk_text_buffer_set_text ( buffer , contents , -1); 
	g_free(filename );
	g_free(contents );
	gtk_widget_set_sensitive(app_state->print_button, TRUE); 
	gtk_widget_show_all(app_state->window);

}

/*****************************************************************************
 on_print_button
*****************************************************************************/

void on_print_button ( GtkWidget *button , AppState *app_state) {
	
	GtkTextIter start ; 
	GtkTextIter end ;
	gchar *text ; 
	GtkTextBuffer *buffer ;
	
	buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(app_state->text_view )); 
	if ( NULL != buffer ) {
		/* Obtain iters for the start and end of points of the buffer */ 
		gtk_text_buffer_get_bounds ( buffer , &start , &end );
		/* Get the entire buffer text. */
		text = gtk_text_buffer_get_slice ( buffer , &start , &end , FALSE);
		/* Print the text */ g_print ("%s", text ); 
		g_free (text);
	}
}
	
