#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PRODUCTS.h"

// Réorganisation des fonctions

// Fonction qui lit le fichier des produits pour les attribuer au tableau produits afin de travailler dessus

void reader (PRODUCTS productsX[], FILE *fichier)
{
	int i = 0;

	while (fscanf(fichier, "%s %s %s %s %u %f %s", productsX[i].referenceProducts, productsX[i].markProcucts, productsX[i].typeProcucts, productsX[i].flavorProducts, &productsX[i].inventoryProducts, &productsX[i].priceProducts, productsX[i].sizeProducts) != EOF)
    {
        i++;
    } 
}


// Fonction stock 0 et 

void displayInventoryCatZero(PRODUCTS produitX[]) // Fonction qui remplit les conditions : produits dont les stocks sont à 0 && 5 produits dont les stocks sont les plus faibles (!= 0) && la place restante du magasin
{
	int counter = 0; 
	unsigned int stock[29];
	printf("\n-------------------------------------------------\n");

	printf("Affichage des produits manquant :\n");

	for (int i = 0; i <= 29; i++)
	{
		if (produitX[i].inventoryProducts == 0)
		{
			printf("Les %s de la marque %s saveur %s\n", produitX[i].typeProcucts, produitX[i].markProcucts, produitX[i].flavorProducts);
			counter++;
		}
	}

	for (int j = 0; j <= 29; j++)
	{
		stock[j] = produitX[j].inventoryProducts;
	}

	printf("\nAffichage des produits avec les 5 stocks les plus faibles : \n");
	displayLow(stock, 29, 5, produitX);

	unsigned int stockLocal = stockLimit(produitX);
	printf("Stock restant : %d\n", 3000-stockLocal);

	if (counter == 0)
	{
		printf("Les chats ont renouvelé tout les stocks !\n");
	}

	printf("\n-------------------------------------------------\n");
}


// Partie MODE GESTION : La recherche du stock 

void searchWithName (PRODUCTS productsX[]) // Lié à searchWithRef mais pour une recherche avec un nom 
{
	char varMark[20], varType[20], varFlavor[20], varRefUser[7]; // Recherche d'une comptatibilite avec saisie USER
	char varRefOrName[10];
	printf("Format de la recherche : [(Marque de votre produit) (Type d'aliment) (Gout)]\n Nom : \n");
		scanf("%19s %19s %19s", varMark, varType, varFlavor);

			for (int i = 0; i <= 29; i++)
			{
				if ((strcmp(productsX[i].markProcucts, varMark) == 0) && (strcmp(productsX[i].typeProcucts, varType) == 0) && (strcmp(productsX[i].flavorProducts, varFlavor) == 0))
				{
				printf("Quantité en stock : %u\n", productsX[i].inventoryProducts);
				break;
				}
			}
	return;
}

// Lié à searchWithName mais pour une recherche avec une référence

void searchWithRef (PRODUCTS productsX[]) 
{
	char varRefUser[7]; // Sachant que l'on connait le format des références

		printf("Reference : \n");
		scanf("%8s", varRefUser);

		for (int i = 0; i <= 29; i++) // Recherche d'une comptatibilite avec saisie USER
		{
			if (strcmp(productsX[i].referenceProducts , varRefUser) == 0)
			{
			printf("Vous avez sélectionné les %s de la marque %s saveur %s\n", productsX[i].typeProcucts, productsX[i].markProcucts, productsX[i].flavorProducts);
			printf("Quantité en stock : %u\n", productsX[i].inventoryProducts);
			printf("Retour au menu gestion");
			break;
			}
		}
	return;
}

// Choix user entre la recherche name or ref

void searchNameOrInventory (PRODUCTS productsX[]) // Affichage du stock pour une référence ou un nom. Menu recherche d'une maniere globale
{
	int i = 0;
	int refOrName;

	printf("\n[MODE GESTION - Recherche produit]\n");

	do 
	{
	printf("Vous souhaitez effectuer votre recherche à partir de :\n (1) La reference\n (2) Le nom \n");
	scanf("%2d", &refOrName);

		if (refOrName != 1 && refOrName != 2)
		{
			printf("Choix invalide !\n");
		}
	} while (refOrName != 1 && refOrName != 2);


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

// Fonction qui permet d'augmenter la quantite d'un produit en prenant le format et la place limite du magasin

void addQuantity(PRODUCTS productsX[], FILE* listCat) 
{
    char userSelectionRef[20];
    unsigned int stock;

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
            printf("Quelle quantité souhaitez-vous ajouter ?\n");
            scanf("%u", &varAddingQuantity);

            productsX[i].inventoryProducts += varAddingQuantity;

            fseek(listCat, 0, SEEK_SET); 
            rewrite(productsX, listCat, size);

            fseek(listCat, 0, SEEK_SET);
            reader(productsX, listCat);

            stock = stockLimit(productsX);

            if (stock > 3000) //STOCK LIMIT
            {
            	printf("\nNous sommes désolé actuellement la boutique ne peut pas commander autant de produit\n");
            	printf("Par conséquent, l'augmentation n'a pas ete prise en compte");
            	productsX[i].inventoryProducts -= varAddingQuantity;
            }
            else
            {
            	printf("L'augmentation de %s a ete effectue", productsX[i].referenceProducts);
            }
			return; 
        }
	}

	printf("----------");
	printf("Nous avons trouvé aucune correspondance, retour au menu\n");
	printf("----------");
	return;
}

// Fonction obligatoire pour réécrire et actualiser le fichier sachant que je travaille sur un tableau

void rewrite(PRODUCTS produitX[], FILE* fichier, int size) 
{
    fseek(fichier, 0, SEEK_SET); 

    for (int i = 0; i < size; i++) 
    {
        fprintf(fichier, "%s %s %s %s %u %f %s\n", produitX[i].referenceProducts, produitX[i].markProcucts, produitX[i].typeProcucts, produitX[i].flavorProducts, produitX[i].inventoryProducts, produitX[i].priceProducts, produitX[i].sizeProducts);
    }
}

// Mon objectif est d'attribuer selon la chaine de caractere PETIT MOYEN GRAND voir .txt un coefficiant

unsigned int stockLimit (PRODUCTS productsX[]) 
{
	char varPetit[] = {"PETIT"};
	char varMoyen[] = {"MOYEN"};
	char varGrand[] = {"GRAND"};
	unsigned int stock = 0;


	for (int i = 0; i <= 30; i++)
	{
		if (strcmp(productsX[i].sizeProducts, varPetit) == 0)
		{
			stock += (productsX[i].inventoryProducts) * 1;
		}
		else if (strcmp(productsX[i].sizeProducts, varMoyen) == 0)
		{
			stock += (productsX[i].inventoryProducts) * 2;
		}
		else if (strcmp(productsX[i].sizeProducts, varGrand) == 0)
		{
			stock += (productsX[i].inventoryProducts) * 4;
		}
	}

	return stock;

}

// Utilisation de la fonction qsort afin de m'afficher les 5 inventory les plus faibles
int qsortUse (const void* a, const void*b)
{
	unsigned int stockOne = *(const int*)a;
	unsigned int stockTwo = *(const int*)b;

	return stockOne - stockTwo;
}

void displayLow (unsigned int stock[], int size, int number, PRODUCTS productsX[])
{
	qsort(stock, number, sizeof(unsigned int), qsortUse);

    for (int i = 0; i < size && stock[i] != 0 && i < number; i++) 
    {
        printf("Produit : %s %s %s : Stock = %d\n", productsX[i].markProcucts, productsX[i].typeProcucts, productsX[i].flavorProducts, stock[i]);
    }
}