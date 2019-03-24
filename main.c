/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 23 March 2019, 10:27
 */

#include <stdio.h>
#include <stdlib.h>

#include <gtk-3.0/gtk/gtk.h>

GtkWidget		*g_lbl_hello;
GtkWidget		*g_lbl_count;
	
int main(int argc, char *argv[])
{
    GtkBuilder      *builder; 
    GtkWidget       *window;

	GError			*err = NULL;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "glade/main.glade", &err);
	
	if (err != NULL) {
        fprintf (stderr, "Unable to read file: %s\n", err->message);
        g_error_free(err);
        return 1;
    }

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));

	if (window == NULL || !GTK_IS_WINDOW(window)) {
        fprintf (stderr, "Unable to get window. (window == NULL || window != GtkWindow)\n");
        return 1;
    }
    gtk_builder_connect_signals(builder, NULL);
	
	g_lbl_hello = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_hello"));
	g_lbl_count = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_count"));

    g_object_unref(builder);

    gtk_widget_show(window);                
    gtk_main();

    return 0;
}

void on_btn_hello_clicked()
{
	static unsigned int count = 0;
	char str_count[30] = {0};

	gtk_label_set_text(GTK_LABEL(g_lbl_hello), "Hello, world!");
	count++;
	sprintf(str_count, "%d", count);
	gtk_label_set_text(GTK_LABEL(g_lbl_count), str_count);
}

// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}