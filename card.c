#include <stdio.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>
#include "login.h"
#include "card.h"

// runing state variables
struct pairCard* pcard;
Card* card;
const gchar*  cardID[16] = {"btn1","btn2","btn3","btn4","btn5","btn6","btn7","btn8","btn9","btn10","btn11","btn12","btn13","btn14","btn15","btn16"};
gchar*  backCardImagePath[16]={"rsc/img1.png","rsc/img2.png","rsc/img3.png","rsc/img4.png","rsc/img5.png","rsc/img6.png","rsc/img7.png","rsc/img9.png","rsc/img1.png","rsc/img2.png","rsc/img3.png","rsc/img4.png","rsc/img5.png","rsc/img6.png","rsc/img7.png","rsc/img9.png"};
int j=0;
int score_int = 0;
int wining_counter=0;

// runing state widgets
GtkWidget* buttons[16];
GtkWidget* images[16];
GtkWidget* imagesFront[16];
GtkWidget* window;
GtkWidget* lbl_player;
GtkWidget* lbl_score;
// wining state widgets
GtkWidget* window_win;
GtkWidget* lbl_win_score;
// game over state widgets
GtkWidget* window_lose;
GtkWidget* lbl_lose_score;
GtkWidget* btn_play_again;

/// main function

void mainCard(User* user)

{
    //create and get builder from 'glade' files
    GtkBuilder* builder;
    builder=gtk_builder_new_from_file ("rsc/glade/gameboard.glade");

    //runing state widgets
    window=GTK_WIDGET(gtk_builder_get_object(builder,"gameWindow"));
    lbl_score = GTK_WIDGET(gtk_builder_get_object(builder,"lbl_score"));
    lbl_player = GTK_WIDGET(gtk_builder_get_object(builder,"lbl_player"));
    gtk_label_set_text(GTK_LABEL(lbl_player),user->username);

    //wining state widgets
    window_win=GTK_WIDGET(gtk_builder_get_object(builder,"window_win"));
    lbl_win_score=GTK_WIDGET(gtk_builder_get_object(builder,"lbl_win_score"));

    //game over state widgets
    window_lose = GTK_WIDGET(gtk_builder_get_object(builder,"window_lose"));
    lbl_lose_score = GTK_WIDGET(gtk_builder_get_object(builder,"lbl_lose_score"));
    btn_play_again = GTK_WIDGET(gtk_builder_get_object(builder,"btn_play_again"));
    // allocate memory to pcard (pair of cards)
    pcard=(struct pairCard *)malloc(sizeof(struct pairCard));
    pcard->cardMatch1=(char *)malloc(50*sizeof(char));
    pcard->cardMatch2=(char *)malloc(50*sizeof(char));
    pcard->cardMatch1=NULL;
    pcard->cardMatch2=NULL;
    pcard->card_1=newCard();
    pcard->card_2=newCard();

    // get images and there buttons
    for(int i=0;i<16;i++)
    {
        buttons[i]=GTK_WIDGET(gtk_builder_get_object(builder,cardID[i]));
    }

    // shuffle images
    shuffling();

    for(int i=0;i<16;i++)
    {
        images[i]=gtk_image_new_from_file(backCardImagePath[i]);
    }
    for(int i=0;i<16;i++)
    {
        imagesFront[i]=gtk_image_new_from_file("rsc/pokemon.png");
    }

    // initialise board
    initBoard();

    //connect signals
    for(int i=0;i<16;i++)
    {
         g_signal_connect(buttons[i],"clicked",G_CALLBACK(clickButton),NULL);
    }
    g_signal_connect(btn_play_again,"clicked",G_CALLBACK(play_again),user);

    // show what was made
    gtk_widget_show_all (window);

}




/// card functions

//alocate memory to card
Card* newCard(void)
{
    Card* a=(Card* )malloc(sizeof(Card));
    return a;
}

//showing card
void showCard(Card *card)
{
    if(card->showing)
    {

        gtk_button_set_always_show_image (GTK_BUTTON(card->button),TRUE);
        g_object_ref(card->backImage);

        gtk_button_set_image(GTK_BUTTON(card->button),card->backImage);
        gtk_widget_show(card->backImage);

    }
    else
    {
        gtk_button_set_always_show_image (GTK_BUTTON(card->button),TRUE);
        g_object_ref(card->frontImage);
        gtk_button_set_image(GTK_BUTTON(card->button),card->frontImage);

    }
}

//fliping card
void flip(Card* card)
{
    if(card->showing)
    {
        card->showing=false;
    }
    else
    {
        card->showing=true;
    }
}

 //Construire une card
Card* cardconstructor(struct card* card,GtkWidget *BACKCARD,GtkWidget *FRONT,GtkWidget* BUTTON)
{
    card->button=BUTTON;
    card->frontImage=FRONT;
    card->backImage=BACKCARD;
    return card;

}

//get the index of any button
int get_index(GtkButton* btn)//getter
{
    int i,index;
    for(i=0;i<16;i++)
    {
        if(GTK_BUTTON(buttons[i]) == btn) index = i;
    }
    return index;
}

void initBoard()
{
    for(int i=0;i<16;i++)
    {
         gtk_button_set_image(GTK_BUTTON(buttons[i]),imagesFront[i]);

    }
}

//matching cards
bool match(char *card_1,char* card_2)
{
    int res;
    res=g_strcmp0(card_1,card_2);
    if(res)
    {
        return false;
    }
    else
    {
        return true;
    }
}

/// pcard (pair of cards) functions

//resets (by showing the back of those images) the pair of  cards if they are unmatched
gboolean hide_pcard(gpointer data)
{
    int index1 = get_index(GTK_BUTTON(pcard->card_1->button));
    int index2 = get_index(GTK_BUTTON(pcard->card_2->button));
    GtkWidget* img1 = gtk_image_new_from_file("rsc/pokemon.png");
    GtkWidget* img2 = gtk_image_new_from_file("rsc/pokemon.png");

    printf("time to hide image 1\n");
    gtk_widget_hide(images[index1]);
    gtk_button_set_always_show_image(GTK_BUTTON(buttons[index1]),TRUE);
    g_object_ref(img1);
    g_object_ref(img2);
    gtk_button_set_image(GTK_BUTTON(buttons[index1]),img1);

    printf("time to hide image 2\n");
    gtk_widget_hide(images[index2]);
    gtk_button_set_always_show_image (GTK_BUTTON(buttons[index2]),TRUE);
    gtk_button_set_image(GTK_BUTTON(buttons[index2]),img2);

    printf("reseted\n");

    return G_SOURCE_REMOVE;
}

//rest cards after any two clicks
void reset()
{
    pcard->cardMatch1 = NULL;
    pcard->cardMatch2 = NULL;
    pcard->numberOfclicks=0;

}

/// when the player click on any buttons

void clickButton(GtkButton*button,gpointer data)
{

    char* score_str = (char*)malloc(10*sizeof(char));
    static int trying = 0;
    int i = get_index(button);
    card = newCard();
    card = cardconstructor(card,images[i],imagesFront[i],GTK_WIDGET(button));

    //if it is the third click do this
    if(	pcard->cardMatch1 != NULL && pcard->cardMatch2 != NULL)
    {
        reset();
    }

    //if an empty 1rst button do the following
    if(pcard->cardMatch1==NULL)
    {
            card=cardconstructor(card,images[i],imagesFront[i],GTK_WIDGET(button));//initializing card
            pcard->numberOfclicks++;
            card->showing=true;
            pcard->cardMatch1=backCardImagePath[i];
	        pcard->card_1->backImage =images[i];
	        pcard->card_1->button =GTK_WIDGET(button);
            showCard(card);
            return;
    }
    do
    {
        // if it's not the 1st click so it's the 2nd click...
        card=cardconstructor(card,images[i],imagesFront[i],GTK_WIDGET(button));
        card->showing=true;
        pcard->cardMatch2=backCardImagePath[i];
	    pcard->card_2->backImage = images[i];
	    pcard->card_2->button =GTK_WIDGET(button);
        pcard->numberOfclicks++;  //to fix the probleme of clicking two time in the same buttom
        showCard(card);

        //now it s time to compare the two cards

        //if it's the correcte pair of cards
        if(match(pcard->cardMatch1,pcard->cardMatch2))
        {
            //if the buttons are not the same,Ok
            if(pcard->card_1->button != pcard->card_2->button)
            {
                printf("they matched\n");
                reset();
                 if(pcard->numberOfclicks<=1)
                {
                    pcard->numberOfclicks=1;
                    score_int = score_int + 10;
                    sprintf(score_str,"%d",score_int);
                    gtk_label_set_text(GTK_LABEL(lbl_score),score_str);
                    if(check_wining()){   // check if the player win
                        printf("you win\n");
                        gtk_widget_destroy(window);
                        gtk_label_set_text(GTK_LABEL(lbl_win_score),score_str);
                        gtk_widget_show(window_win);   // show another window and mention the score
                    }

                    return ;
                }
            }
            //so the buttons here are the same,it's not Ok. The 2nd button still empty
            else
            {
                printf("I pressed twice on same image\n");
                pcard->cardMatch2 = NULL;
                printf("i reseted\n ");
            }

        }

        // if the two buttons are not the same
	    else
        {
            //counting the number of tries
            trying++;
            if(trying % 20 == 0){    // if it's 20 tries , you lose
                sprintf(score_str,"%d",score_int);
                gtk_widget_destroy(window);
                gtk_label_set_text(GTK_LABEL(lbl_lose_score),score_str);
                gtk_widget_show(window_lose);
            }

            //
            do
            {
            //reset the two images
            printf("they didn't\n");
	        g_timeout_add(500, hide_pcard,NULL); ///
            printf("i passed the tst");
            pcard->numberOfclicks=1;
            }while (j!=0);
        }
    }while(!pcard->numberOfclicks);

}

// check if the player win
gboolean check_wining()
{

    wining_counter++;
    if(wining_counter%8 == 0) return TRUE;
    return FALSE;
}

///when the player click on the "play again" button

void play_again(GtkButton*button,User* user)
{
    wining_counter = 0;
    score_int = 0;
    gtk_widget_hide(window_lose);
    mainCard(user);

}

/// shuffling the images

void shuffling()
{
    int i=0;
    // create a random numbers generator
    GRand * generator;
    generator = g_rand_new ();
    int random1,random2;
    for (i=0;i<200;i++)
    {
        random1 = g_rand_int_range(generator,0,12);
        random2 = g_rand_int_range(generator,0,12);
        gchar* inter2 = backCardImagePath[random1];
        backCardImagePath[random1] = backCardImagePath[random2];
        backCardImagePath[random2] = inter2;
    }
}

