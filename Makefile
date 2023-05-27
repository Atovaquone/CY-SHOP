all : prog

prog : main.o PRODUCTS.o menu_display.o customer.o
	gcc -o prog main.o PRODUCTS.o menu_display.o customer.o

main.o : main.c
	gcc -o main.o -c main.c

PRODUCTS.o : PRODUCTS.c
	gcc -o PRODUCTS.o -c PRODUCTS.c 

menu_display.o : menu_display.c
	gcc -o menu_display.o -c menu_display.c 

customer.o : customer.c 
	gcc -o customer.o -c customer.c