#include <stdio.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>
#include "menu.h"
#include "card.h"

int main(int argc,char* argv[])
{
    gtk_init(&argc,&argv);
    menu();
    //mainCard();
    gtk_main();
    return 0;
}
