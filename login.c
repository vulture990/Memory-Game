#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<gtk/gtk.h>
#include <stdbool.h>
#include "card.h"
#include "login.h"

/// login | signUp page widjets

//  Sign In widgets
GtkWidget      *entry_password;
GtkWidget      *entry_username;
GtkWidget      *lbl_incorrect_login;

//  Sign Up widgets
GtkWidget      *entry_email;
GtkWidget      *entry_username2;
GtkWidget      *entry_password2;
GtkWidget      *lbl_successful_signingup;

//  main window widget
GtkWidget      *window_;

/// main function
void login(){

    //  create and get builder from 'glade' files
    GtkBuilder      *builder;
    builder = gtk_builder_new_from_file("rsc/glade/login.glade");

    //  Sign In widgets
    GtkWidget      *btn_login;

    //  Sign Up widgets
    GtkWidget      *btn_signup;

    window_ = GTK_WIDGET(gtk_builder_get_object(builder,"main_window"));
    //  Get Sign In widgets
    lbl_incorrect_login = GTK_WIDGET(gtk_builder_get_object(builder,"lbl_incorrect_login"));
    entry_password = GTK_WIDGET(gtk_builder_get_object(builder,"entry_password"));
    entry_username = GTK_WIDGET(gtk_builder_get_object(builder,"entry_username"));
    btn_login = GTK_WIDGET(gtk_builder_get_object(builder,"btn_login"));

    //  Get Sign Up widgets
    entry_email = GTK_WIDGET(gtk_builder_get_object(builder,"entry_email"));
    entry_username2 = GTK_WIDGET(gtk_builder_get_object(builder,"entry_username2"));
    entry_password2 = GTK_WIDGET(gtk_builder_get_object(builder,"entry_password2"));
    lbl_successful_signingup = GTK_WIDGET(gtk_builder_get_object(builder,"lbl_successful_signingup"));
    btn_signup = GTK_WIDGET(gtk_builder_get_object(builder,"btn_signup"));

    //  make passwords invisibles
    gtk_entry_set_visibility (GTK_ENTRY(entry_password),FALSE);
    gtk_entry_set_invisible_char (GTK_ENTRY(entry_password),'*');
    gtk_entry_set_visibility (GTK_ENTRY(entry_password2),FALSE);
    gtk_entry_set_invisible_char (GTK_ENTRY(entry_password2),'*');

    //  Struct of a (new) user
    User* user ;
    NewUser* new_user = g_slice_new(NewUser);

    //  connect signals
    g_signal_connect(btn_login,"clicked",G_CALLBACK(log_in),user);
    g_signal_connect(btn_signup,"clicked",G_CALLBACK(sign_up),new_user);

    //  Show what was created
    gtk_widget_show_all(window_);
    g_object_unref(builder);
}

void log_in(GtkButton* btn,User* user){
    strcpy(user->username,gtk_entry_get_text(GTK_ENTRY(entry_username)));
    strcpy(user->password,gtk_entry_get_text(GTK_ENTRY(entry_password)));

    check_user_data(user);
    //clear entries
    gtk_entry_set_text(GTK_ENTRY(entry_username),"");
    gtk_entry_set_text(GTK_ENTRY(entry_password),"");
    return ;
}

void sign_up(GtkButton* btn,NewUser* new_user){
    strcpy(new_user->email,gtk_entry_get_text(GTK_ENTRY(entry_email)));
    strcpy(new_user->username,gtk_entry_get_text(GTK_ENTRY(entry_username2)));
    strcpy(new_user->password,gtk_entry_get_text(GTK_ENTRY(entry_password2)));
    FILE* file = fopen("rsc/users.txt","a");
    fprintf(file,"%s,%s,%s\n",new_user->username,new_user->password,new_user->email);
    fclose(file);
    const gchar* msg = "Successful registration, thank you for signing up.";

    gtk_label_set_text(GTK_LABEL(lbl_successful_signingup),msg);

    //clear entries
    gtk_entry_set_text(GTK_ENTRY(entry_username2),"");
    gtk_entry_set_text(GTK_ENTRY(entry_password2),"");
    gtk_entry_set_text(GTK_ENTRY(entry_email),"");

}

void check_user_data(User* user_t){
    printf("%s",user_t->username);
    gchar username[30];
    gchar password[30];
    gchar user_data_str[70];
    gchar ln[100];
    strcpy(username,user_t->username);
    strcpy(password,user_t->password);
    sprintf(user_data_str,"%s,%s",username,password);
    FILE* file = fopen("rsc/users.txt","r");
    char* found = fgets(ln,100,file);
    while(found!=NULL){
        char* result = g_strrstr(ln,user_data_str);
        if(result!=NULL){
            gtk_label_set_text(GTK_LABEL(lbl_incorrect_login),"");
            g_print("\nuser Found\n");
            mainCard(user_t);     /// login correct -> start game
            gtk_widget_hide(window_);
            break;
        }
        found=fgets(ln,100,file);
    }

    const gchar* msg = "Incorrect password or username.";

    if(found==NULL){           ///  login incorrect -> display an error message
        gtk_label_set_text(GTK_LABEL(lbl_incorrect_login),msg);
    }

    fclose(file);
}

