#include "binarni_strom.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

t_uzel* vytvorUzel(int data) {
	t_uzel* novyUzel = (t_uzel*)malloc(sizeof(t_uzel));
	if (novyUzel == NULL) {
		return NULL;
	}

	novyUzel->data = data;
	novyUzel->levy = NULL;
	novyUzel->pravy = NULL;
	return novyUzel;
}

t_uzel* vloz(t_uzel* koren, int data) {
	if (koren == NULL) {
		return vytvorUzel(data);
	}
	if (data < koren->data) {
		koren->levy = vloz(koren->levy, data);
	}
	else if (data > koren->data) {
		koren->pravy = vloz(koren->pravy, data);
	}
	return koren;
}

void tiskInOrder(t_uzel* koren) {
	if (koren == NULL) {
		return;
	}
	tiskInOrder(koren->levy);
	printf("%d ", koren->data);
	tiskInOrder(koren->pravy);
}

t_uzel* najdiMin(t_uzel* uzel) {
	if (uzel == NULL) {
		return NULL;
	}
	t_uzel* aktualni = uzel;

	while (aktualni->levy != NULL) {
		aktualni = aktualni->levy;
	}
	return aktualni;
}

t_uzel* smaz(t_uzel* koren, int data) {
    
    if (koren == NULL) {
        return koren;
    }

    if (data < koren->data) {
        koren->levy = smaz(koren->levy, data);
    }
    
    else if (data > koren->data) {
        koren->pravy = smaz(koren->pravy, data);
    }

    else {
        if (koren->levy == NULL) {
            t_uzel* temp = koren->pravy;
            free(koren);
            return temp;
        }
		else if (koren->pravy == NULL) {
			t_uzel* temp = koren->levy;
			free(koren);
			return temp;
		}
        t_uzel* temp = najdiMin(koren->pravy);

        koren->data = temp->data;

        koren->pravy = smaz(koren->pravy, temp->data);
    }

    return koren;
}

void uvolniStrom(t_uzel* koren) {
	if (koren == NULL) {
		return;
	}

	uvolniStrom(koren->levy);
	uvolniStrom(koren->pravy);
	free(koren);
}

void ulozStrom_rekurze(t_uzel* koren, FILE* soubor) {
	
	if (koren == NULL) {
		fprintf(soubor, "#\n");
		return;
	}
	
	fprintf(soubor, "%d\n", koren->data);
	ulozStrom_rekurze(koren->levy, soubor);
	ulozStrom_rekurze(koren->pravy, soubor);
}

int ulozStrom(t_uzel* koren, const char* nazevSouboru) {
	FILE* soubor;

	if (fopen_s(&soubor, nazevSouboru, "w") != 0) {
		printf("Chyba: Soubor '%s' se nepodarilo otevrit pro zapis.\n", nazevSouboru);
		return 0;
	}

	ulozStrom_rekurze(koren, soubor);
	fclose(soubor);
	printf("Strom byl uspesne ulozen do souboru '%s'\n", nazevSouboru);
	
	return 1;
}

t_uzel* nactiStrom_rekurze(FILE* soubor) {
	char buffer[100];
	
	if (fscanf_s(soubor, "%s", buffer, (unsigned)_countof(buffer)) == EOF) {
		return NULL;
	}

	if (strcmp(buffer, "#") == 0) {
		return NULL;
	}

	int data = atoi(buffer);

	t_uzel* novyUzel = vytvorUzel(data);

	if (novyUzel == NULL) {
		return NULL;
	}

	novyUzel->levy = nactiStrom_rekurze(soubor);
	novyUzel->pravy = nactiStrom_rekurze(soubor);

	return novyUzel;
}

t_uzel* nactiStrom(const char* nazevSouboru) {
	FILE* soubor;
	
	if (fopen_s(&soubor, nazevSouboru, "r") != 0) {
		printf("Chyba: Soubor '%s' se nepodarilo otevrit pro cteni.\n", nazevSouboru);
		return NULL;
	}

	t_uzel* koren = nactiStrom_rekurze(soubor);
	fclose(soubor);
	printf("Strom byl uspesne nacten ze souboru '%s'\n", nazevSouboru);
	
	return koren;
}