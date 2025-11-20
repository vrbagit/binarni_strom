#include "binarni_strom.h"
#include <stdio.h>

int main() {
	t_uzel* koren = NULL;
	
	printf("Vkladam hodnoty do stromu...\n");
	
	koren = vloz(koren, 10);
	koren = vloz(koren, 5);
	koren = vloz(koren, 15);
	koren = vloz(koren, 3);
	koren = vloz(koren, 7);
	
	printf("Vkladani dokonceno.\n");
	
	printf("\n--- Vypis stromu (In-Order) ---\n");
	tiskInOrder(koren);
	printf("\n-------------------------------\n");

	printf("Mazu uzel 5...\n");
	koren = smaz(koren, 5);

	printf("\n--- Vypis stromu po smazani ---\n");
	tiskInOrder(koren);
	printf("\n-------------------------------\n");

	printf("Uvolnuji cely strom...\n");
	uvolniStrom(koren);

	koren = NULL;

	printf("Program bezpecne ukoncen.\n");

	return 0;
}