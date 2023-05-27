#ifndef PRODUCTS_H
#define PRODUCTS_H

typedef struct // Structure pour les produits 
{
	char referenceProducts[7];
	char markProcucts[20];
	char typeProcucts[20];
	char flavorProducts[20];
	unsigned int inventoryProducts;
	float priceProducts;
	char sizeProducts[8];

}PRODUCTS;


void reader (PRODUCTS productsX[], FILE *fichier);

void displayInventoryCatZero(PRODUCTS produitX[]);

void searchWithName (PRODUCTS productsX[]);

void searchWithRef (PRODUCTS productsX[]);

void searchNameOrInventory (PRODUCTS productsX[]);

void addQuantity (PRODUCTS productsX[], FILE* listCat); 

void rewrite(PRODUCTS produitX[], FILE* fichier, int size);

#endif