#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PRODUCTS.h"

// Réorganisation des fonctions

// Fonction qui lit le fichier des produits pour les attribuer au tableau 

void reader (PRODUCTS productsX[], FILE *fichier)
{
	int i = 0;

	while (fscanf(fichier, "%s %s %s %s %u %f %s", productsX[i].referenceProducts, productsX[i].markProcucts, productsX[i].typeProcucts, productsX[i].flavorProducts, &productsX[i].inventoryProducts, &productsX[i].priceProducts, productsX[i].sizeProducts) != EOF)
    {
        i++;
    } 
}


// Fonction stock 0 

void displayInventoryCatZero(PRODUCTS produitX[]) // Fonction qui remplit les conditions : produits dont les stocks sont à 0 && 5 produits dont les stocks sont les plus faibles (!= 0) && la place restante du magasin
{
	int counter = 0; 
	printf("\n-------------------------------------------------\n");

	printf("Affichage des stocks faibles :\n");

	for (int i = 0; i <= 29; i++)
	{
		if (produitX[i].inventoryProducts == 0)
		{
			printf("Les %s de la marque %s saveur %s\n", produitX[i].typeProcucts, produitX[i].markProcucts, produitX[i].flavorProducts);
			counter++;
		}
	}

	if (counter == 0)
	{
		printf("Les chats ont renouvelé tout les stocks !\n");
	}

	printf("\n-------------------------------------------------\n");
}


// Partie MODE GESTION : La recherche du stock 

void searchWithName (PRODUCTS productsX[]) //Lié à searchWithName mais pour une recherche avec un nom 
{
	char varMark[20], varType[20], varFlavor[20], varRefUser[7];
	char varRefOrName[10];
	printf("Format de la recherche : [(Marque de votre produit) (Type d'aliment) (Gout)]\n Nom : \n");
		scanf("%s %s %s", varMark, varType, varFlavor);

			for (int i = 0; i <= 29; i++)
			{
				if ((strcmp(productsX[i].markProcucts, varMark) == 0) && (strcmp(productsX[i].typeProcucts, varType) == 0) && (strcmp(productsX[i].flavorProducts, varFlavor) == 0))
				{
				printf("Quantité en stock : %u\n", productsX[i].inventoryProducts);
				}
			}
	return;
}


void searchWithRef (PRODUCTS productsX[]) // Lié à searchWithName mais pour une recherche avec une référence
{
	char varRefUser[7]; // Sachant que l'on connait le format des références

		printf("Reference : \n");
		scanf("%s", varRefUser);

		for (int i = 0; i <= 29; i++)
		{
			if (strcmp(productsX[i].referenceProducts , varRefUser) == 0)
			{
			printf("Vous avez sélectionné les %s de la marque %s saveur %s\n", productsX[i].typeProcucts, productsX[i].markProcucts, productsX[i].flavorProducts);
			printf("Quantité en stock : %u\n", productsX[i].inventoryProducts);
			printf("Retour au menu gestion");
			}
		}
	return;
}

void searchNameOrInventory (PRODUCTS productsX[]) // Affichage du stock pour une référence ou un nom 
{
	int i = 0;
	int refOrName;

	printf("[MODE GESTION - Recherche produit]\n");
	printf("Vous souhaitez effectuer votre recherche à partir de :\n (1) La reference\n (2) Le nom \n");
	scanf("%d", &refOrName);

	switch (refOrName)
	{
	case 1 : // Cas avec la ref
		searchWithRef(productsX);
		return;
	break;

	case 2 : // Cas avec le nom
		searchWithName(productsX);
		return;
	break;

 	default : 
 		printf("Erreur de selection");
 	break;
	}
}

// Fonction qui permet d'augmenter la quantite d'un produit voulu à ce jour le format des produits n'est pas prise en compte

void addQuantity(PRODUCTS productsX[], FILE* listCat) 
{
    char userSelectionRef[20];

    printf("[Onglet] Modification de stock sélectionné\n");
    printf("Vous souhaitez augmenter le stock d'un produit, quelle est sa référence : \n");
    scanf("%s", userSelectionRef);

    int size = 30; 

    for (int i = 0; i < size; i++) 
    {
        if (strcmp(productsX[i].referenceProducts, userSelectionRef) == 0) 
        {
            unsigned int varAddingQuantity = 0;
            printf("Quantité en stock : %u\n", productsX[i].inventoryProducts);
            printf("Quelle quantité souhaitez-vous ajouter ?");
            scanf("%u", &varAddingQuantity);

            productsX[i].inventoryProducts += varAddingQuantity;

            fseek(listCat, 0, SEEK_SET); 
            rewrite(productsX, listCat, size);

            fseek(listCat, 0, SEEK_SET);
            reader(productsX, listCat);

            return; 
        }
    	else
    	{
			printf("Pas de correspondance\n");
		}
	}
	return;
}

// Fonction obligatoire pour réécrire et actualiser le fichier

void rewrite(PRODUCTS produitX[], FILE* fichier, int size) 
{
    fseek(fichier, 0, SEEK_SET); 

    for (int i = 0; i < size; i++) 
    {
        fprintf(fichier, "%s %s %s %s %u %f %s\n", produitX[i].referenceProducts, produitX[i].markProcucts, produitX[i].typeProcucts, produitX[i].flavorProducts, produitX[i].inventoryProducts, produitX[i].priceProducts, produitX[i].sizeProducts);
    }
}