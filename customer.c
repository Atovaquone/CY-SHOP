#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "customer.h"

// Historique d'achat prévu et en cours 

void clientVersion2 (PRODUCTS productsX[]) // Procédure dont l'objectif de trouver dans le fichier la correspondance
{
    char name[25];
    char firstName[25];
    char varName[25];
    char varFirstName[25];

    printf("Vous comptez parmi nos fideles clients\n Saississez votre nom : \n");
    scanf("%24s", name);

    printf("Saississez votre prenom :\n"); 
    scanf("%24s", firstName);


    printf("Nous allons rechercher vous rechercher avec l'identité %s %s\n", name, firstName);


    FILE *listCustomer = fopen("customer_list.txt", "a+"); 
    if (listCustomer == NULL)
    {
        exit(1);
    }

    int k = 0;

    while (fscanf(listCustomer, "%24s %24s", varName, varFirstName) == 2) 
    {
        if (strcmp(varName, name) == 0 && strcmp(varFirstName, firstName) == 0) 
        {
            printf("Bienvenue %s %s\n", name, firstName);
            k++; 
            buyClientVersion2(productsX);
        }
    }

    if (k) 
    {
        printf("Vous êtes bien authentifie\n");

    } 

    else 
    {
        printf("Vous n'etes pas dans nos fichiers\n");
    }

    fclose(listCustomer);

}

void newClientVersion2 () // Inscription dans le fichier pour un nouveau client
{
    char name[25];
    char firstName[25];

    printf("Vous souhaitez devenir un fidèle client\n");
    printf("Saississez votre nom");
    scanf("%24s", name);
    printf("Saississez votre prenom");
    scanf("%24s", firstName);

    FILE *listCustomer = fopen("customer_list.txt", "a+");
    if (listCustomer == NULL)
    {
        exit(1);
    }

    rewind(listCustomer);

    fprintf(listCustomer, "%s %s", name, firstName);

    fprintf(listCustomer, "\n");

    fflush(listCustomer);

    fclose(listCustomer);
}

void buyClientVersion2(PRODUCTS productsX[]) // Achat d'un produit selon sa ref ou name 
{
    float priceTotal = 0;
    int choiseUser;

    printf("Vous souhaitez acheter un de nos produits, vous etes au bon endroit !\n");

menu:
    printf("Vous souhaitez le rechercher avec :\n (1) La reference\n (2) Le nom (3) Quitter le menu et valider le panier\n");
    scanf("%d", &choiseUser);

    switch (choiseUser)
    {
    case 1:
        priceTotal += buyClientWithRef(productsX); // Cas avec la ref
        printf("Prix total actuel : %f\n", priceTotal);
        break;

    case 2:
    {
        priceTotal += buyClientWithName(productsX); // Cas avec le nom
        printf("Prix total actuel : %f\n", priceTotal);
        break;
    }

    case 3:
        return; // Quitter le menu

    default:
        printf("Choix invalide\n");
        goto menu;
    }

    goto menu;
}

float buyClientWithRef(PRODUCTS productsX[]) // Achat ref et deleteclient si mecontent
{
    char varRefUser[8];
    float price = 0;

    printf("Vous recherchez un produit parmi notre gamme\n");
    printf("Votre reference : ");
    scanf("%10s", varRefUser);

    for (int i = 0; i < 30; i++)
    {
        if (strcmp(productsX[i].referenceProducts, varRefUser) == 0)
        {
            printf("\nVous avez sélectionné les %s de la marque %s saveur %s\n", productsX[i].typeProcucts, productsX[i].markProcucts, productsX[i].flavorProducts);
            printf("Quantité en stock : %u\n", productsX[i].inventoryProducts);
            if (productsX[i].inventoryProducts == 0)
            {
                deleteClient(); //SI produit indisponible
            }
            price = productsX[i].priceProducts;
            productsX[i].inventoryProducts -= 1;
            printf("Quantité après achat : %u\n", productsX[i].inventoryProducts);
            break;
        }
    }
    return price;
}

float buyClientWithName(PRODUCTS productsX[]) // Achat name et deleteclient si mecontent
{
    char varMark[25], varType[25], varFlavor[25];
    float price = 0;
    printf("\n");
    printf("\nVous recherchez un produit parmi notre gamme\n");
    
    printf("La marque : \n");
    scanf("%15s", varMark);

    printf("Le type d'aliment : \n");
    scanf("%15s", varType);

    printf("Le gout : \n");
    scanf("%15s", varFlavor);

    for (int i = 0; i < 30; i++)
    {
        if (strcmp(productsX[i].markProcucts, varMark) == 0 && strcmp(productsX[i].typeProcucts, varType) == 0 && strcmp(productsX[i].flavorProducts, varFlavor) == 0)
        {
            printf("\nVous avez sélectionné les %s de la marque %s saveur %s\n", productsX[i].typeProcucts, productsX[i].markProcucts, productsX[i].flavorProducts);
            printf("Quantité en stock : %u\n", productsX[i].inventoryProducts);
            if (productsX[i].inventoryProducts == 0)
            {
                deleteClient(); //SI produit indisponible
            }
            price = productsX[i].priceProducts;
            productsX[i].inventoryProducts -= 1;
            printf("Quantité après achat : %u\n", productsX[i].inventoryProducts);
            break;
        }
    }
    return price;
}

void deleteClient() // Le client est mecontent il se deinscrit lecture dans le fichier dans un premier temps avec sauvegarde de tout sauf le client en question puis reecriture du fichier
{
    char name[25];
    char firstName[25];

    FILE *fichier = fopen("customer_list.txt", "r+");
    FILE *copyFile = tmpfile();

    printf("Nous comprenons votre déception et espérons votre retour.\n");

    printf("Saisissez votre nom : ");
    scanf("%s", name);

    printf("Saisissez votre prénom : ");
    scanf("%s", firstName);

    char line[100];

    while (fgets(line, sizeof(line), fichier) != NULL)
    {
        if (strstr(line, name) == NULL || strstr(line, firstName) == NULL)
        {
            fputs(line, copyFile);
        }
    }

    fclose(fichier);
    rewind(copyFile);

    fichier = fopen("customer_list.txt", "w");

    int ch;
    while ((ch = fgetc(copyFile)) != EOF)
    {
        fputc(ch, fichier);
    }

    fclose(fichier);
    fclose(copyFile);

    printf("En esperant vous revoir bientot ! \n");

    exit(1);
}