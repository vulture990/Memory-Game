
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "login.h"
#include "menu.h"

GtkWidget* window_t;
void menu(){
    GtkBuilder* builder = gtk_builder_new_from_file ("rsc/glade/menu.glade");
    window_t = GTK_WIDGET(gtk_builder_get_object(builder,"window"));

    GtkWidget* btn_login_signup=GTK_WIDGET(gtk_builder_get_object(builder,"btn_login_signup"));
    //GtkWidget* btn_about_us=GTK_WIDGET(gtk_builder_get_object(builder,"btn_about_us"));

    g_signal_connect(btn_login_signup,"clicked",G_CALLBACK(login_signup),NULL);
    //g_signal_connect(btn_about_us,"clicked",G_CALLBACK(SignUpp),NULL)


    gtk_widget_show_all(window_t);
}

void login_signup(GtkButton* btn, gpointer data){
    gtk_widget_destroy(window_t);
    login();
}


