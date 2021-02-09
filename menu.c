
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "login.h"
#include "menu.h"

// main window
GtkWidget* window_t;
void menu(){
    //  create and get builder from 'glade' files
    GtkBuilder* builder = gtk_builder_new_from_file ("rsc/glade/menu.glade");

    //  create and get other widjets from 'glade' files
    window_t = GTK_WIDGET(gtk_builder_get_object(builder,"window"));
    GtkWidget* window_s = GTK_WIDGET(gtk_builder_get_object(builder,"window_about_us"));
    GtkWidget* btn_login_signup=GTK_WIDGET(gtk_builder_get_object(builder,"btn_login_signup"));
    GtkWidget* btn_about_us=GTK_WIDGET(gtk_builder_get_object(builder,"btn_about_us"));
    GtkWidget* btn_back_to_menu=GTK_WIDGET(gtk_builder_get_object(builder,"btn_back_to_menu"));

    //connect signals
    g_signal_connect(btn_login_signup,"clicked",G_CALLBACK(login_signup),window_t);
    g_signal_connect(btn_about_us,"clicked",G_CALLBACK(about_us),window_s);
    g_signal_connect(btn_back_to_menu,"clicked",G_CALLBACK(back_menu),window_s);

    //show what was made
    gtk_widget_show_all(window_t);
}
/// go to "login | sign up"
void login_signup(GtkButton* btn, GtkWidget* window_t){
    gtk_widget_destroy(window_t);
    login();
}
/// go to "about us"
void about_us(GtkButton* btn, GtkWidget* window_s){
    gtk_widget_hide(window_t);
    gtk_widget_show(window_s);
}

///back to menu
void back_menu(GtkButton* btn, GtkWidget* window_s){
    gtk_widget_hide(window_s);
    gtk_widget_show(window_t);
}
