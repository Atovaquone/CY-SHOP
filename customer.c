#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "customer.h"

// Historique d'achat prévu et en cours 

void readerCustomer(CUSTOMER customerX[], FILE *fichier) // Permet de collecter les donnees afin de le mettre dans le tableau et pouvoir travailler dessus
{
	int i = 0;

	while (fscanf(fichier, "%s %s %u %u %u", customerX[i].name, customerX[i].firstName, &customerX[i].purchaseHistory.day, &customerX[i].purchaseHistory.month, &customerX[i].purchaseHistory.year) != EOF);
    {
        i++;
    } 
}

void newClient(CUSTOMER customerX[], FILE *fichier) // La fonction permet de devenir un fidèle client de CY-PETS, nom, prenom et le tour est joué 
{
    char* nameClient = (char*)malloc(sizeof(char) * 25); // 25 me semble un juste nombre
    char* firstNameClient = (char*)malloc(sizeof(char) * 25);
    int number;

    printf("Vous n'êtes pas encore un client, c'est l'occasion d'y remédier\n");
    printf("Quel est votre nom : ");
    scanf("%s", nameClient);

    printf("Quel est votre prénom : ");
    scanf("%s", firstNameClient);

    // A FAIRE REVOIR LA STRUCTURE POUR L HISTORIQUE D ACHAT ET AJOUTER POUR NEW CLIENT !!!

    number = numberClient(customerX, fichier);




    free(nameClient);
    free(firstNameClient);

}

int numberClient(CUSTOMER customerX[], FILE *fichier) // Fonction peut etre pas essentiel mais tester pour l'instant pour compter le nombre de client (je me suis basé sur la fonction reader)
{
    int i = 0;

    while (fscanf(fichier, "%s %s %u %u %u", customerX[i].name, customerX[i].firstName, &customerX[i].purchaseHistory.day, &customerX[i].purchaseHistory.month, &customerX[i].purchaseHistory.year) != EOF);
    {
        i++;
    } 

    return i;
}

void client(CUSTOMER customerX[], FILE *fichier)
{
    char* nameClient = (char*)malloc(sizeof(char) * 25); // 25 me semble un juste nombre
    char* firstNameClient = (char*)malloc(sizeof(char) * 25);
    int number;

    printf("Quel est votre nom ?\n");
    scanf("%s", nameClient);
    printf("Quel est votre prénom ?");
    scanf("%s", firstNameClient);

    number = numberClient(customerX, fichier);


    for (int i = 0; i <= number; i++)
    {
        if (strcmp(customerX[i].name, nameClient) == 0 && strcmp(customerX[i].firstName, firstNameClient) == 0)  
            {
                printf("Bienvenue %s %s \n", customerX[i].name, customerX[i].firstName);
                
            }
    }

    free(nameClient);
    free(firstNameClient);

}