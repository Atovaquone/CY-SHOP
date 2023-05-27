#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu_display.h"

void mainMenu() // Affichage du menu principal : choix GESTION ou ACHAT
{
	printf("\n-------------------------------------------------\n");
	printf("[Menu principal]\n");
	printf("Bienvenue chez CY-PETS\n                          Choississez votre menu : \n \n");
	printf("(1) Mode gestion : Le mode permet une gestion des stocks de CY-PETS\n");
	printf("(2) Mode achat : Le mode permet d'effectuer vos a-chats\n");
	printf("(3) Quitter\n");
	printf("\n-------------------------------------------------\n");
}

void managementModeSelection ()
{
	printf("\n-------------------------------------------------\n");
	printf("\n[MODE GESTION]\n");
	printf("(1) Recherche stock : La selection permet de rechercher le stock d'un produit\n");
	printf("(2) Augmention du stock : La selection permet d'augmenter la quantité de votre stock pour satisfaire vos clients à 4 pattes\n");
	printf("(3) Retourner au menu principal");
	printf("\n-------------------------------------------------\n");
}

void managementModeSelectionSearch (PRODUCTS productsX[])
{
	printf("\n-------------------------------------------------\n");
	searchNameOrInventory(productsX);
}

void managementModeSelectionIncrease (PRODUCTS productsX[], FILE *listProductsCat)
{
	printf("\n-------------------------------------------------\n");
	printf("[MODE GESTION - AUGMENTION STOCK]\n");
	addQuantity(productsX, listProductsCat);
}

void managementMode (PRODUCTS productsX[], FILE *listProductsCat) // Affichage pour le mode gestion
{
	printf("\n[MODE GESTION]\n");
	printf("\nVous avez selectionne le mode gestion; que souhaitez-vous faire : \n");

	int menuSelectionManagementMode = 0;

	while (1)
    {
    	displayInventoryCatZero(productsX);
    	managementModeSelection();

        printf("\nSaissisez votre choix pour le mode gestion : \n");
        scanf("%d", &menuSelectionManagementMode);

        printf("\n-------------------------------------------------\n");
        
        switch (menuSelectionManagementMode) 
        {
        case 1 : 
        	managementModeSelectionSearch(productsX); 
        break;

        case 2 : 
        	managementModeSelectionIncrease(productsX, listProductsCat);
        break;

    	case 3 : 
    		return;

        default : 
        	printf("Mauvaise selection mais pas de panique !\n");
        break;
        }

    }
}

void displayCustomerMode (CUSTOMER customerX[], FILE *fichier)
{
	int selectionCustomer;
	printf("[MODE ACHAT]\n");
	printf("Avant toute chose, etes vous client ?\n (1) Oui, je suis client \n(2) Non mais j'aimerais beaucoup\n");
	scanf("%d", &selectionCustomer);

	switch(selectionCustomer)
	{
	case 1 :
		client(customerX, fichier);
		break;

	case 2 : 
		newClient(customerX, fichier);
		break;

	default : 
        	printf("Mauvaise selection mais pas de panique !\n");
        break;
	}

}

