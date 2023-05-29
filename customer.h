#ifndef CUSTOMER_H
#define CUSTOMER_H
	
#include "PRODUCTS.h" // <-- Pour la struct PRODUITS

typedef struct  
{
	char name[25];
	char firstName[25];
}CUSTOMER;

void clientVersion2 (PRODUCTS productsX[]);

void newClientVersion2 ();

void buyClientVersion2 (PRODUCTS productsX[]);

float buyClientWithRef (PRODUCTS productsX[]);

float buyClientWithName (PRODUCTS productsX[]);

void deleteClient();

#endif