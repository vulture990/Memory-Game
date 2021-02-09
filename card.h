#ifndef CARD_H
#define CARD_H

#include "login.h"


typedef struct card
{
    GtkWidget* button;
    GtkWidget* frontImage;
    GtkWidget* backImage;

    bool showing;
    void (*showCard)(struct card* self);
    void (*flip)(struct card* self);
}Card;


typedef struct pairCard   //pair of cards
{
    Card* card_1;
    Card* card_2;
    //path
    char* cardMatch1;
    char* cardMatch2;
    int numberOfclicks;
}PairCard;

/// main function
void mainCard(User* user);

/// card && pcard (pair of cards) functions
Card* newCard(void);
bool match(char *card_1,char* card_2);
void showCard(struct card *card);
void flip(struct card* card);
Card* cardconstructor(struct card* c,GtkWidget* backCard,GtkWidget* front,GtkWidget* button);
void reset();
int get_index(GtkButton* btn);
gboolean hide_pcard(gpointer data);

/// initialise the board (show the back of images)
void initBoard();

/// when the player click on any buttons
void clickButton(GtkButton*button,gpointer data);
gboolean check_wining();

/// shuflling images
void shuffling(void);

/// play again
void play_again(GtkButton*button,User* user);



#endif
