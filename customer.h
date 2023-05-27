#ifndef CUSTOMER_H
#define CUSTOMER_H
	
#include "PRODUCTS.h" // <-- Pour la struct PRODUITS

typedef struct 
{
	unsigned int day;
	unsigned int month;
	unsigned int year;
}DATE;

typedef struct  
{
	char name[25];
	char firstName[25];
	DATE purchaseHistory;
}CUSTOMER;

void readerCustomer(CUSTOMER customerX[], FILE *fichier);

void client(CUSTOMER customerX[], FILE *fichier);

void newClient(CUSTOMER customerX[], FILE *fichier);

int numberClient(CUSTOMER customerX[], FILE *fichier);


#endif