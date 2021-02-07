#ifndef LOGIN_H
#define LOGIN_H

 typedef struct{
    char username[30];
    char password[30];
}User;

typedef struct{
    char email[40];
    char username[15];
    char password[15];
}NewUser;

void login();
void log_in(GtkButton* btn,User* user);
void sign_up(GtkButton* btn,NewUser* new_user);
void check_user_data(User* user_t);
//void gameloop(User* user,GtkButton* btn_login);

#endif
