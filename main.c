#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PRODUCTS.h"
#include "menu_display.h"
#include "customer.h"

int main ()
{
    // Ouverture du fichier pour la liste des produits sous forme de tableaux 

    FILE *listProductsCat = fopen("products_list.txt", "r+");
    if (listProductsCat == NULL)
    {
        exit(1);
    }

    PRODUCTS tabProductsCat[255]; 

    reader(tabProductsCat, listProductsCat);

    // Ouverture du fichier [pour la liste des clients sous forme de tableaux (Principe imcomplet) idee initale abandonne]
    
    FILE *listCustomer = fopen("customer_list.txt", "a+");
    if (listCustomer == NULL)
    {
        exit(1);
    }

    int menuSelection = 0;

    while (1) //Ouverture du menu principal GESTION ou ACHAT
    {
        mainMenu();

        printf("Saissisez votre choix de menu : \n");
        scanf("%d", &menuSelection);

        switch (menuSelection) // J'ai essayé de faire un menu avec une correspondance entre la saisie User mais j'ai finalement opté pour un switch que me semble plus simple
        {
        case 1 : 
            managementMode(tabProductsCat, listProductsCat); 
        break;

        case 2 : 
            displayCustomerMode(listCustomer, tabProductsCat);
        break;

        case 3 : 
            printf("A bientot !");
            exit(1);
        break;

        default : 
            printf("Mauvaise selection mais pas de panique !\n");
        break;
        }
    }

    fclose(listProductsCat);

    fclose(listCustomer);

    return 0;
}
