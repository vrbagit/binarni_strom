#include <stdio.h>
#include <stdlib.h>
#include "binarni_strom.h"

void vycistiBuffer() {
    while (getchar() != '\n');
}

void vypisMenu() {
    printf("\n=== VIZUALIZACE BINARNIHO STROMU ===\n");
    printf("1. Vlozit novou hodnotu\n");
    printf("2. Smazat hodnotu\n");
    printf("3. Vytisknout strom (In-order)\n");
    printf("4. Ulozit strom do souboru\n");
    printf("5. Nacist strom ze souboru\n");
    printf("6. Smazat cely strom\n");
    printf("0. Ukoncit\n");
    printf("====================================\n");
    printf("Vase volba: ");
}

int main() {
    t_uzel* koren = NULL;

    int volba;
    int hodnota;
    char nazevSouboru[50];

    do {
        vypisMenu();

        if (scanf_s("%d", &volba) != 1) {
            printf("Chyba: Zadejte prosim cislo.\n");
            vycistiBuffer();
            continue;
        }

        switch (volba) {
        case 1:
            printf("Zadejte hodnotu (int) pro vlozeni: ");
            scanf_s("%d", &hodnota);
            koren = vloz(koren, hodnota);
            printf("Hodnota %d byla vlozena.\n", hodnota);
            break;

        case 2:
            printf("Zadejte hodnotu (int) ke smazani: ");
            scanf_s("%d", &hodnota);
            koren = smaz(koren, hodnota);
            printf("Pokud hodnota %d existovala, byla smazana.\n", hodnota);
            break;

        case 3:
            printf("\n--- Obsah stromu (serazeny) ---\n");
            if (koren == NULL) {
                printf("Strom je prazdny.\n");
            }
            else {
                tiskInOrder(koren);
                printf("\n");
            }
            break;

        case 4:
            printf("Zadejte nazev souboru pro ulozeni (bez mezer): ");
            scanf_s("%s", nazevSouboru, (unsigned)_countof(nazevSouboru));
            ulozStrom(koren, nazevSouboru);
            break;

        case 5:
            printf("VAROVANI: Nacteni prepise aktualni strom.\n");
            printf("Zadejte nazev souboru pro nacteni: ");
            scanf_s("%s", nazevSouboru, (unsigned)_countof(nazevSouboru));

            uvolniStrom(koren);

            koren = nactiStrom(nazevSouboru);
            break;

        case 6:
            uvolniStrom(koren);
            koren = NULL;
            printf("Strom byl kompletne vymazan.\n");
            break;

        case 0:
            printf("Ukoncuji aplikaci...\n");
            uvolniStrom(koren);
            break;

        default:
            printf("Neplatna volba, zkuste to znovu.\n");
            break;
        }

    } while (volba != 0);

    return 0;
}