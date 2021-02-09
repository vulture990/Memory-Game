#include <stdio.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>
#include "menu.h"

void load_css(void);

int main(int argc,char* argv[])
{
    gtk_init(&argc,&argv);

    /// loading css
    load_css();

    /// go to menu
    menu();

    ///looping
    gtk_main();
    return 0;
}


/// loading css fuction

void load_css(void)
{
    GtkCssProvider *provider;
    GdkDisplay     *display;
    GdkScreen      *screen;
    //
    const gchar *css_style_file = "login.css";
    GFile       *css_fp         = g_file_new_for_path(css_style_file);
    GError      *error          = 0;
    //
    provider = gtk_css_provider_new();
    display  = gdk_display_get_default();
    screen   = gdk_display_get_default_screen(display);
    //
    gtk_style_context_add_provider_for_screen(screen,GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gtk_css_provider_load_from_file(provider,css_fp,&error);
    //
    g_object_unref(provider);
}
