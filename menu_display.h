#ifndef MENU_DISPLAY_H
#define MENU_DISPLAY_H

#include "PRODUCTS.h" // <-- Pour la struct PRODUCTS 
#include "customer.h"

void mainMenu(); // Affichage du menu principal : choix GESTION ou ACHAT

void managementModeSelectionIncrease (PRODUCTS productsX[], FILE *listProductsCat); // Procédure pour le choix MAIN>GESTION>AUGMENTION STOCK

void managementModeSelectionSearch (PRODUCTS productsX[]); // Procédure pour le choix MAIN>GESTION>RECHERCHE STOCK

void managementModeSelection (); // Affichage des 2 choix pour le mode GESTION

void managementMode (PRODUCTS productsX[], FILE *listProductsCat); // Affichage pour le mode gestion 

void displayCustomerMode (CUSTOMER customerX[], FILE *fichier); // Choix du menu pour le mode achat 

#endif
