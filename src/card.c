#include <stdio.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>

#include "card.h"

const gchar*  cardID[16] = {"btn1","btn2","btn3","btn4","btn5","btn6","btn7","btn8","btn9","btn10","btn11","btn12","btn13","btn14","btn15","btn16"};
gchar*  backCardImagePath[16]={"rsc/img1.png","rsc/img2.png","rsc/img3.png","rsc/img4.png","rsc/img5.png","rsc/img6.png","rsc/img7.png","rsc/img9.png","rsc/img1.png","rsc/img2.png","rsc/img3.png","rsc/img4.png","rsc/img5.png","rsc/img6.png","rsc/img7.png","rsc/img9.png"};
GtkWidget* buttons[16];
GtkWidget* images[16];
GtkWidget* imagesFront[16];
struct pairCard* pcard=(struct pairCard *)calloc(1,sizeof(struct pairCard));
Card* card=newCard();


Card* newCard(void)//always remeber to release the memory space after you are done
{
    Card* a=(Card* )malloc(sizeof(Card));
    return a;
}


void showCard(Card *card)
{
    if(card->showing)
    {

        gtk_button_set_always_show_image (GTK_BUTTON(card->button),TRUE);
        gtk_button_set_image(GTK_BUTTON(card->button),card->backImage);
        //gtk_widget_show(card->backImage);
        
    }
    else
    {
        gtk_button_set_always_show_image (GTK_BUTTON(card->button),TRUE);
        gtk_button_set_image(GTK_BUTTON(card->button),card->frontImage);
        //gtk_widget_show(card->frontImage);

    }
}

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

Card* cardconstructor(struct card* card,GtkWidget *BACKCARD,GtkWidget *FRONT,GtkWidget* BUTTON)
{
    card->button=BUTTON;
    card->frontImage=FRONT;
    card->backImage=BACKCARD;
    //card->showing=true;//which simply means all cards are turned down by default
    // card->showCard=showCard;
    // card->flip=flipCard;
    return card;

}

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
        
        //gtk_widget_show(imagesFront[i]);

    }
}

bool match(char *card_1,char* card_2)
{
    int res;
    res=strcmp(card_1,card_2);
    if(res)
    {
        return false;
    }
    else
    {
        return true;
    }
}

gboolean hide_pcard(gpointer data)//resets the pair of  cards if they are unmatched
{   //
    int index1 = get_index(GTK_BUTTON(pcard->card_1->button));
    int index2 = get_index(GTK_BUTTON(pcard->card_2->button));
    //pcard->card_1->showing=false;
    //pcard->card_2->showing=false; 
   // showCard(pcard->card_1);  ///show front
  //  showCard(pcard->card_2);    /// show front
    flip(pcard->card_1);
    flip(pcard->card_2);
    printf("time to hide image 1\n");
    gtk_widget_hide(images[index1]);

    gtk_button_set_always_show_image(GTK_BUTTON(buttons[index1]),TRUE);
     GtkWidget* img1=gtk_image_new_from_file("rsc/pokemon.png");
     GtkWidget* img2=gtk_image_new_from_file("rsc/pokemon.png");
    gtk_button_set_image(GTK_BUTTON(buttons[index1]),img1);
    printf("time to hide image 2\n");
    gtk_widget_hide(images[index2]);
    //gtk_widget_destroy(images[index2]);
    gtk_button_set_always_show_image (GTK_BUTTON(buttons[index2]),TRUE);
    gtk_button_set_image(GTK_BUTTON(buttons[index2]),img2);
    

    return G_SOURCE_REMOVE;
}
void reset()
{
    free(pcard);
    pcard=(struct pairCard *)calloc(1,sizeof(struct pairCard));
    pcard->cardMatch1 = NULL;
    pcard->cardMatch2 = NULL;
    pcard->card_1 = NULL;
	pcard->card_2 = NULL;
}
static void clickButton(GtkButton*button,gpointer data)// we r gonna pass address nta3 card
{
    int id;
    int i=get_index(button);
    card=newCard();
    card=cardconstructor(card,images[i],imagesFront[i],GTK_WIDGET(button));
    if(	pcard->cardMatch1 != NULL && pcard->cardMatch2 != NULL)
    {
        // free(pcard);
        // pcard=(struct pairCard *)malloc(sizeof(struct pairCard));

        reset();
    }
    if(pcard->cardMatch1==NULL)//if an empty 1rst button do the following
    {
        
        card=cardconstructor(card,images[i],imagesFront[i],GTK_WIDGET(button));//initializing card
        card->showing=true;
        pcard->cardMatch1=backCardImagePath[i];
	    pcard->card_1->frontImage = images[i];           ///
	    pcard->card_1->button =GTK_WIDGET(button);   ///
        showCard(card);
        return;
    }
        card=cardconstructor(card,images[i],imagesFront[i],GTK_WIDGET(button));
        card->showing=true;
        pcard->cardMatch2=backCardImagePath[i];
	    pcard->card_2->frontImage = images[i];  ///
	    pcard->card_2->button =GTK_WIDGET(button);   ///
        showCard(card);
        //now it s time to compare the two cards
        if(match(pcard->cardMatch1,pcard->cardMatch2))
        {   ///
	      printf("they matched\n");
        //  free(pcard);
        //  pcard=(struct pairCard *)malloc(sizeof(struct pairCard));

         reset();
         return;
	          ///
	    }
	    else
        {      ///

            printf("they didn't\n");
            g_timeout_add(750, hide_pcard,NULL); ///
            printf("i passed the tst");


            reset();
        
	        
            printf("time to reset\n");
            printf("reseted \n");
        }
    
    
}
void mainCard(void)
{

    GtkBuilder* builder;
   // card=cardconstructor(card,,"./rsc/pokemon.p);
    // we must first click the button then show

    // flipCard(card);
    pcard->cardMatch1=(char *)malloc(50*sizeof(char));
    pcard->cardMatch2=(char *)malloc(50*sizeof(char));
    pcard->cardMatch1=NULL;
    pcard->cardMatch2=NULL;
    pcard->card_1=newCard();
    pcard->card_2=newCard();
    GtkWidget* window;
    builder=gtk_builder_new_from_file ("./src/gameboard.glade");
    window=GTK_WIDGET(gtk_builder_get_object(builder,"gameWindow"));
    for(int i=0;i<16;i++)
    {
        buttons[i]=GTK_WIDGET(gtk_builder_get_object(builder,cardID[i]));
    }
    for(int i=0;i<16;i++)
    {
        images[i]=gtk_image_new_from_file(backCardImagePath[i]);
    }
    for(int i=0;i<16;i++)
    {
        imagesFront[i]=gtk_image_new_from_file("rsc/pokemon.png");
    }

    initBoard();
    for(int i=0;i<16;i++)
    {
         g_signal_connect(buttons[i],"clicked",G_CALLBACK(clickButton),NULL);
    }

    gtk_widget_show_all (window);

}


// typedef struct card
// {
//     int front;     
//     char* backCard;
//     bool showing;
//     void (*showCard)(struct card* self);
//     void (*flip)(struct card* self);
// }Card;
// typedef struct memoryGame
// { 
//     const char* words[8]={"Bleuu","Bleuu","Yellow","Yellow","Black","Black","White","White"}; 
//     Card borad[4][4];//4x4 matrice
//     int r=rand();
//     void (*setCells)(struct memoryGame* m);
//     void (*printCells)(struct memoryGame* m);
//     void (*shuffle)(struct memoryGame* m);
//     void (*matchingPairs)(struct memoryGame* m);

// }MemoryGame;

// Card* newCard();
// Card* cardConstructor(struct card* card,char* BACKCARD,int FRONT);
// void showCard(struct card *card);
// void flipCard(struct card* card);
// void memoryGameConstr(struct memoryGame* m);
// void shuffle(struct memoryGame* m);
// void setCells(struct memoryGame* m);
// void printCells(struct memoryGame*m);
// void matching (struct memoryGame* m);
// Card* newCard2(struct card c);


// int main(void)
// {
//     struct memoryGame* m=(struct memoryGame*)malloc(sizeof(MemoryGame));
//     memoryGameConstr(m);
//     return 0;
// }

// Card* newCard2(struct card c)
// {
//         Card* a=newCard();
//         a=&c;
//         return a;
// }


// Card* newCard()
// {
//     Card* a=(Card* )malloc((sizeof(Card)));
//     return a;
// }

// void showCard(Card *card)
// {
//     if(card->showing)
//     {
//         printf("%s ",card->backCard);
//     }
//     else
//     {
//         printf(" [ %d ] ",card->front);
//     }
// }

// void flipCard(Card* card)
// {
//     if(card->showing)
//     {
//         card->showing=false;
//     }
//     else
//     {
//         card->showing=true;
//     }
// }


// Card* cardConstructor(struct card* card,char* BACKCARD,int FRONT)
// {
//     card->front=FRONT;
//     card->backCard=BACKCARD;
//     card->showing=false;//which simply means all cards are turned down by default
//     // card->showCard=showCard;
//     // card->flip=flipCard;
//     return card;
// } 

// void setCells(MemoryGame* m)
// {
//     Card* c=newCard();

         
//     int i =0;
//     for(int row=0;row<4;row++)
//     {
//         for(int col=0;col<4;col++)
//         {
//             char*s;
//             strcpy(s,m->words[i])
//             c=cardConstructor(newCard2(m->borad[row][col]),s,i);
//             m->borad[row][col]=*c;
                
//             i++;
//         }
//     }
// }

// void printCells(MemoryGame* m)
// {
//     Card a;
//     for(int row=0;row<4;row++)
//     {
//         for(int col=0;col<4;col++)
//         {
//             a=m->borad[row][col];
//             showCard(&a);
//         }
//         printf("\n");
//     }

// }


// void shuffle(struct memoryGame*m)
// {
//     for(int i=0;i<8;i++)
//     {
//         int pos=(m->r)%8;
//         char* temp;
//         strcpy(temp,m->words[i]);
//         strcpy(m->words[i],m->words[pos]);
//         strcpy(m-words[pos],temp);
//     }
    
// }

// void matching(MemoryGame* m)
// {
//     int cardChoice,row1,col1,row2,col2;
//     printf("enter the number of card.");
//     printf("\nFirst Card Choice?");

//     scanf("%d",&cardChoice);
//     row1=cardChoice/4;
//     col1=cardChoice%4;
//     flipCard(newCard2(m->borad[row1][col1]));
//     printf("pick an other number?");
//     printf("\nSecond Card Choice");
//     scanf("%d",&cardChoice);
//     row2=cardChoice/4;
//     col2=cardChoice%4;
//     flipCard(newCard2(m->borad[row2][col2]));
//     getchar();
//     printCells(m);
    
// }
// void memoryGameConstr(struct memoryGame* m)
// {
//     for(int i=0;i<4;i++)
//     {  
//         for(int j=0;j<4;j++)
//         {
//              Card* c=newCard();
//              Card cc=*c;
//              (m->borad[i][j])=cc;
//              free(c);
//         }

//     }
//     // shuffle and setcells and printcells  last but not least play the game
//     shuffle(m);
//     setCells(m);
//     printCells(m);
//     matching(m);
// }



















































