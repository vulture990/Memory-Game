/******************************************************************************

       
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>
#define maxSTRING 10

typedef struct card
{
    int front;     
    char* backCard;
    bool showing;
    void (*showCard)(struct card* self);
    void (*flip)(struct card* self);
}Card;
typedef struct memoryGame
{ 
    const char* words[8]={"Bleuu","Bleuu","Yellow","Yellow","Black","Black","White","White"}; 
    Card borad[4][4];//4x4 matrice
    int r=rand();
    void (*setCells)(struct memoryGame* m);
    void (*printCells)(struct memoryGame* m);
    void (*shuffle)(struct memoryGame* m);
    void (*matchingPairs)(struct memoryGame* m);

}MemoryGame;

Card* newCard();
Card* cardConstructor(struct card* card,char* BACKCARD,int FRONT);
void showCard(struct card *card);
void flipCard(struct card* card);
void memoryGameConstr(struct memoryGame* m);
void shuffle(struct memoryGame* m);
void setCells(struct memoryGame* m);
void printCells(struct memoryGame*m);
void matching (struct memoryGame* m);
Card* newCard2(struct card c);


int main(void)
{
    struct memoryGame* m=(struct memoryGame*)malloc(sizeof(MemoryGame));
    memoryGameConstr(m);
    return 0;
}

Card* newCard2(struct card c)
{
        Card* a=newCard();
        a=&c;
        return a;
}


Card* newCard()
{
    Card* a=(Card* )malloc((sizeof(Card)));
    return a;
}

void showCard(Card *card)
{
    if(card->showing)
    {
        printf("%s ",card->backCard);
    }
    else
    {
        printf(" [ %d ] ",card->front);
    }
}

void flipCard(Card* card)
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


Card* cardConstructor(struct card* card,char* BACKCARD,int FRONT)
{
    card->front=FRONT;
    card->backCard=BACKCARD;
    card->showing=false;//which simply means all cards are turned down by default
    // card->showCard=showCard;
    // card->flip=flipCard;
    return card;
} 

void setCells(MemoryGame* m)
{
    Card* c=newCard();

         
    int i =0;
    for(int row=0;row<4;row++)
    {
        for(int col=0;col<4;col++)
        {
            char*s;
            strcpy(s,m->words[i])
            c=cardConstructor(newCard2(m->borad[row][col]),s,i);
            m->borad[row][col]=*c;
                
            i++;
        }
    }
}

void printCells(MemoryGame* m)
{
    Card a;
    for(int row=0;row<4;row++)
    {
        for(int col=0;col<4;col++)
        {
            a=m->borad[row][col];
            showCard(&a);
        }
        printf("\n");
    }

}


void shuffle(struct memoryGame*m)
{
    for(int i=0;i<8;i++)
    {
        int pos=(m->r)%8;
        char* temp;
        strcpy(temp,m->words[i]);
        strcpy(m->words[i],m->words[pos]);
        strcpy(m-words[pos],temp);
    }
    
}

void matching(MemoryGame* m)
{
    int cardChoice,row1,col1,row2,col2;
    printf("enter the number of card.");
    printf("\nFirst Card Choice?");

    scanf("%d",&cardChoice);
    row1=cardChoice/4;
    col1=cardChoice%4;
    flipCard(newCard2(m->borad[row1][col1]));
    printf("pick an other number?");
    printf("\nSecond Card Choice");
    scanf("%d",&cardChoice);
    row2=cardChoice/4;
    col2=cardChoice%4;
    flipCard(newCard2(m->borad[row2][col2]));
    getchar();
    printCells(m);
    
}
void memoryGameConstr(struct memoryGame* m)
{
    for(int i=0;i<4;i++)
    {  
        for(int j=0;j<4;j++)
        {
             Card* c=newCard();
             Card cc=*c;
             (m->borad[i][j])=cc;
             free(c);
        }

    }
    // shuffle and setcells and printcells  last but not least play the game
    shuffle(m);
    setCells(m);
    printCells(m);
    matching(m);
}



















































