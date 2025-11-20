#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct t_uzel {
	int data;
	struct t_uzel* levy;
	struct t_uzel* pravy;
} t_uzel;

t_uzel* vytvorUzel(int data);

t_uzel* vloz(t_uzel* koren, int data);

void tiskInOrder(t_uzel* koren);

t_uzel* najdiMin(t_uzel* uzel);

t_uzel* smaz(t_uzel* koren, int data);

void uvolniStrom(t_uzel* koren);

int ulozStrom(t_uzel* koren, const char* nazevSouboru);

void ulozStrom_rekurze(t_uzel* koren, FILE* soubor);