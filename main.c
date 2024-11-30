#include <stdio.h>
#include <stdlib.h>
#include "Bib.h"
#include "maBib.c"

int main() {
    CENTRE *C = NULL;
    RESULTAT **R;
    int i, s1, s2;
    FILE *f;
    int choix;

    do {
        choix = menu();
        switch (choix) {
            case 1:
                remplirFichier(C);
                break;
            case 2:
                C = afficherFichier();
                if (C != NULL) {
                    AfficherCentre(*C);
                } else {
                    printf("Erreur lors de l'affichage du fichier.\n");}
                break;
            case 3:
                EmployeeMeilleurRendementCentre(*C);
                break;
            case 4: {
                printf("Donnez le code du service: ");
                scanf("%d", &s1);
                if (s1 >= 1 && s1 <= C->nb_service) {
                    EmployeeMeilleurRendementService(C->services + s1 - 1);
                } else {
                    printf("Service invalide. Veuillez reessayer.\n");}
                break;
            }
            case 5:
                ServicePlusDemandee(*C);
                break;
            case 6:
                ServicePlusCouteux(*C);
                break;
            case 7: {
                printf("Donnez le code du service: ");
                scanf("%d", &s2);
                if (s2 >= 1 && s2 <= C->nb_service) {
                    PersonnePlusAncienneService(C->services + s2 - 1);
                } else {
                    printf("Service invalide. Veuillez reessayer.\n");}
                break;
            }
            case 8:
                Resultat(*C, R);
                break;
            case 9:
                printf("Merci d'avoir utilise le programme. Au revoir !\n");
                break;
            default:
                printf("Option invalide. Veuillez reessayer.\n");
                break;
        }

        printf("\n");
    } while (choix != 9);
        free(C);
    return 0;
}
