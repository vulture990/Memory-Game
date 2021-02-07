#ifndef CARD_H
#define CARD_H
// #include <stdio.h>
// #include <gtk/gtk.h>
// #include <stdlib.h>
// #include <string.h>
// #include<stdbool.h>

// extern GtkBuilder* builder;
// extern const char* cardID[16] = {"btn1","btn2","btn3","btn4","btn5","btn6","btn7","btn8","btn9","btn10","btn11","btn12","btn13","btn14","btn15","btn16"};
// extern const char* backCardImagePath[16]={"rsc/img1.png","rsc/img2.png","rsc/img3.png","rsc/img1.png4","rsc/img5.png","rsc/img6.png","rsc/img7.png","rsc/img8.png","rsc/img1.png","rsc/img2.png","rsc/img3.png","rsc/img1.png4","rsc/img5.png","rsc/img6.png","rsc/img7.png","rsc/img8.png"};

typedef struct card
{

    GtkWidget* button;
    GtkWidget* frontImage;
    GtkWidget* backImage;

    bool showing;
    void (*showCard)(struct card* self);
    void (*flip)(struct card* self);
}Card;
typedef struct pairCard
{
    Card* card_1;
    Card* card_2;
    //path
    char* cardMatch1;
    char* cardMatch2;
    int numberOfclicks;
}PairCard;

typedef struct{
    char username[30];
    char password[30];
}User_t;

bool match(char *card_1,char* card_2);
Card* newCard(void);
void showCard(struct card *card);
void flip(struct card* card);
Card* cardconstructor(struct card* c,GtkWidget* backCard,GtkWidget* front,GtkWidget* button);
void reset();
void initBoard();
void mainCard(User_t* user);
int get_index(GtkButton* btn);
gboolean hide_pcard(gpointer data);
void shuffling(void);
gboolean check_wining();
void play_again(GtkButton*button,User_t* user);



#endif
