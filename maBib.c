#include "Bib.h"
#include <time.h>


    int Duree_Sejour(DATE d) {
    int jours = 0;
    int j1 = 0;
    int j2 = 0;
    DATE date_actuelle;
    int Mjours[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    time_t t = time(NULL);
    struct tm *tm_now = localtime(&t);

    date_actuelle.jour = tm_now->tm_mday;
    date_actuelle.mois = tm_now->tm_mon + 1;
    date_actuelle.annee = tm_now->tm_year + 1900;


    if (d.annee < date_actuelle.annee) {
        j1 = (date_actuelle.annee - d.annee) * 365;

        for (int i = d.annee; i < date_actuelle.annee; i++) {
            if (estBissextile(i)) {
                j1++;
            }
        }

        for (int i = 0; i < d.mois - 1; i++) {
            j1 -= Mjours[i];
        }

        if (d.mois > 2 && estBissextile(d.annee)) {
            j1--;
        }

        j1 = j1 - d.jour + 1;

        for (int i = 0; i < date_actuelle.mois; i++) {
            j2 += Mjours[i];
        }
        if (date_actuelle.mois > 2 && estBissextile(date_actuelle.annee)) {
            j2++;
        }

        j2 = j2 - (Mjours[date_actuelle.mois - 1] - date_actuelle.jour);

        jours = j1 + j2;
    }
    else if (d.annee == date_actuelle.annee) {
        if (d.mois < date_actuelle.mois) {
            for (int i = d.mois - 1; i < date_actuelle.mois; i++) {
                jours += Mjours[i];
            }
            if (date_actuelle.mois > 2 && estBissextile(date_actuelle.annee)) {
                jours++;
            }
            jours = jours - date_actuelle.jour - d.jour;
        }
        else if (d.mois == date_actuelle.mois) {
            jours = date_actuelle.jour - d.jour;
        }
    }
    return jours;
}



    void Resultat(CENTRE C , RESULTAT **R){
    int i,k;

    R = (RESULTAT**)malloc(C.nb_service * sizeof(RESULTAT*));
    if (!R) exit(-4);

    for (i = 0; i < C.nb_service; i++) {
        *(R + i) = (RESULTAT*)malloc(sizeof(RESULTAT));
        if (!*(R + i)) exit(-5);

        int maxHt =  ((C.services + i)->employees + 0)->ht;
        int maxCode =  ((C.services + i)->employees + 0)->code;

        for (k = 1; k < (C.services + i)->nb_employees; k++) {
            if ( ((C.services + i)->employees + k)->ht > maxHt) {
                maxHt = ((C.services + i)->employees + k)->ht;
                maxCode =  ((C.services + i)->employees + k)->code;
            }
        }

        (*(R + i))->code = maxCode;
        (*(R + i))->ht = maxHt;
    }

    printf("Affichage du resultat du traitement :\n");
    for (i = 0; i < C.nb_service; i++) {
        printf("Service %d: Code employe avec max heures de travail: %d, Heures: %d\n", i + 1, (*(R + i))->code, (*(R + i))->ht);
    }}




    void EmployeeMeilleurRendementCentre(CENTRE C) {
    EMPLOYEE *max = (C.services)->employees;

    for (int i = 0; i < C.nb_service; i++) {
        for (int j = 0; j < (C.services + i)->nb_employees; j++) {
            if (((C.services + i)->employees + j)->ht > max->ht) {
                max = (C.services + i)->employees + j;
            }
        }
    }

    printf("Employe avec meilleur rendement dans le centre est %s %s\n", max->nom, max->prenom);
    }


    void EmployeeMeilleurRendementService(SERVICE *S) {
    EMPLOYEE *max = S->employees;

    for (int i = 0; i < S->nb_employees; i++) {
            if ((S->employees + i)->ht > max->ht)
                max = S->employees + i;
    }
    printf("Employe avec meilleur rendement dans le service %s est %s %s\n", S->libelle ,max->nom, max->prenom);
    }





    void ServicePlusDemandee(CENTRE C) {
    SERVICE *max = C.services;

    for (int i = 1; i < C.nb_service; i++) {
        if ((C.services + i)->nb_personnes > max->nb_personnes) {
            max = C.services + i;
        }
    }
    printf("Le service le plus demande est : %s avec le pourcentage de %.2f%%\n", max->libelle , max->pourcentage_personne);
    }


    void ServicePlusCouteux(CENTRE C)
    {
    SERVICE* max=C.services;
    for(int i=0;i<C.nb_service;i++)
    {
        if (((C.services+i)->budget)>max->budget)
           max=C.services+i ;
    }
    printf("Le service le plus couteux est %s",max->libelle);
    }

    void PersonnePlusAncienneService(SERVICE *S) {
    PERSONNE *max = S->personnes;

    for (int i = 1; i < S->nb_personnes; i++) {
        if ((S->personnes + i)->duree_sejour > max->duree_sejour) {
            max = S->personnes + i;
        }
    }

    printf("La personne avec la plus longue duree de sejour dans le service %s est %s %s avec %d jours \n", S->libelle, max->nom, max->prenom ,max->duree_sejour);
    }



    int menu(){
    int choix =0 ;
    while(choix < 1 || choix >9 ){

        printf("Menu \n");
        printf(" 1: Remplissage du fichier \n");
        printf(" 2: Affichage de toute les informations du fichier\n");
        printf(" 3: Afficher l'employe avec le meilleur rendement dans  le centre \n");
        printf(" 4: Afficher l'employe avec le meilleur rendement dans  le service  \n");
        printf(" 5: Afficher le service le plus demandee  \n");
        printf(" 6: Afficher le service le plus couteux  \n");
        printf(" 7: Afficher la personne la plus ancienne dans le service \n");
        printf(" 8: Afficher la structure resultat \n");
        printf(" 9: Quitter \n");

        printf("Votre choix ?");
        scanf("%d" ,&choix);
    }
    return choix;}




void creerfichier(FILE**f)
    {
      *f=fopen("d:\\fichiercentre","wb+");
      if(!*f) exit(-1);
}


void remplirFichier(CENTRE* C) {
    FILE *f = fopen("d:\\fichiercentre", "wb");

    SaisirCentre(C);


    fwrite(C->libelle, sizeof(char), 50, f);
    fwrite(&C->nb_service, sizeof(int), 1, f);
    fwrite(&C->nb_chambre, sizeof(int), 1, f);
    fwrite(&C->budget_totale, sizeof(float), 1, f);

    for (int i = 0; i < C->nb_service; i++) {
    SERVICE* s = (C->services + i);

    fwrite(&s->code, sizeof(int), 1, f);
    fwrite(s->libelle, sizeof(char), 50, f);
    fwrite(&s->nb_employees, sizeof(int), 1, f);
    fwrite(&s->nb_personnes, sizeof(int), 1, f);
    fwrite(&s->budget, sizeof(float), 1, f);
    fwrite(&s->nb_max, sizeof(int), 1, f);

    fwrite(s->employees, sizeof(EMPLOYEE), s->nb_employees, f);
    fwrite(s->personnes, sizeof(PERSONNE), s->nb_personnes, f);
}

    printf("Donnees ecrites dans le fichier avec succes.\n");
    fclose(f);
}

CENTRE* afficherFichier() {
    FILE *f = fopen("d:\\fichiercentre", "rb");


    CENTRE* C = (CENTRE*)malloc(sizeof(CENTRE));

    fread(C->libelle, sizeof(char), 50, f);
    fread(&C->nb_service, sizeof(int), 1, f);
    fread(&C->nb_chambre, sizeof(int), 1, f);
    fread(&C->budget_totale, sizeof(float), 1, f);

    AllocationService(C);

    for (int i = 0; i < C->nb_service; i++) {
        fread(&((C->services + i)->code), sizeof(int), 1, f);
        fread((C->services + i)->libelle, sizeof(char), 50, f);
        (C->services + i)->libelle[49] = '\0';
        fread(&((C->services + i)->nb_employees), sizeof(int), 1, f);
        fread(&((C->services + i)->nb_personnes), sizeof(int), 1, f);
        fread(&((C->services + i)->budget), sizeof(float), 1, f);
        fread(&((C->services + i)->nb_max), sizeof(int), 1, f);

        AllocationEmployee(C, i);

        for (int j = 0; j < C->services[i].nb_employees; j++) {
             fread((((C->services + i)->employees) + j), sizeof(EMPLOYEE), 1, f);
        }

        AllocationPersonne(C, i);

        for (int j = 0; j < C->services[i].nb_personnes; j++) {
            fread((((C->services + i)->personnes) + j), sizeof(PERSONNE), 1, f);
        }
    }

    fclose(f);
    return C;
}


int estBissextile(int annee) {
return (annee % 4 == 0 && annee % 100 != 0) || (annee % 400 == 0);
}

int estDateValide(int jour, int mois, int annee) {
    if (mois < 1 || mois > 12) {
         printf("\nErreur : Le mois doit etre compris entre 1 et 12.\n");
        return 0;
    }

    int joursParMois[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (mois == 2 && estBissextile(annee)) {
        joursParMois[2] = 29;
    }

    if (jour < 1 || jour > joursParMois[mois]) {
        printf("\nErreur : Le jour %d est invalide pour le mois %d en %d.\n", jour, mois, annee);
        return 0;
    }

    if (annee < 1) {
        printf("\nErreur : L'année doit etre un entier positif.\n");
        return 0;
    }

    time_t t = time(NULL);
    struct tm *dateActuelle = localtime(&t);

    int jourAuj = dateActuelle->tm_mday;
    int moisAuj = dateActuelle->tm_mon + 1;
    int anneeAuj = dateActuelle->tm_year + 1900;


    if (annee > anneeAuj || (annee == anneeAuj && mois > moisAuj) || (annee == anneeAuj && mois == moisAuj && jour > jourAuj)) {
        printf("\nErreur : La date saisie (%02d/%02d/%04d) est superieure a aujourd'hui (%02d/%02d/%04d).\n",
                jour, mois, annee, jourAuj, moisAuj, anneeAuj);
        return 0;
    }

    return 1;
    }

DATE SaisirDate(){
    DATE d;
    int valide = 0;

    while (!valide) {
    printf("Jour  : ");
    scanf("%d", &d.jour);

    printf("Mois : ");
    scanf("%d", &d.mois);

    printf("Annee  : ");
    scanf("%d", &d.annee);

    if (estDateValide(d.jour, d.mois, d.annee)) {
            valide = 1;
    } else {
            printf("Date invalide. Veuillez reessayer.\n");
    }}

    return d;

}

void AllocationService(CENTRE * C){
    C->services = (SERVICE *)malloc(C->nb_service * sizeof(SERVICE));
    if (!C->services) exit(-1);
}


void ReallocService(CENTRE * C){
    C->services = (SERVICE *)realloc(C->services, C->nb_service  * sizeof(SERVICE));
    if (!C->services) exit(-1);
}



void AllocationPersonne(CENTRE *C ,int s){
    (C->services + s)->personnes = (PERSONNE*)malloc((C->services + s)->nb_personnes * sizeof(PERSONNE));
    if (!(C->services + s)->personnes) exit(-2);
    }

void AllocationEmployee(CENTRE * C , int s){
    (C->services + s)->employees = (EMPLOYEE*)malloc((C->services + s)->nb_employees * sizeof(EMPLOYEE));
    if (!(C->services + s)->employees) exit(-3);
    }


void SaisirService(CENTRE* C, int i) {
    float budget;
    int nb_max;
    int valid = 0;



    (C->services + i)->code = i + 1;

    printf("Donner le libelle du service %d :\n", i + 1);
    scanf("%49s", (C->services + i)->libelle);
    printf("Donnez le budget pour le service %d : ", i + 1);
    scanf("%f", &budget);

    while (!valid) {
        if (budget < 0) {
            printf("Erreur : Le budget ne peut pas etre negatif.\n");
            printf("Redonnez le budget pour le service %d : ", i + 1);
            scanf("%f", &budget);
        } else {
            valid = 1;
        }
    }
    (C->services + i)->budget = budget;

    valid = 0;
    printf("Donner le nombre maximum de personnes pouvant profiter du service %d : ", i + 1);
    scanf("%d", &nb_max);

    while (!valid) {
        if (nb_max <= 0) {
            printf("Erreur : Le nombre maximum de personnes doit etre superieur a 0.\n");
            printf("Redonnez le nombre maximum de personnes pour le service %d : ", i + 1);
            scanf("%d", &nb_max);
        } else {
            valid = 1;
        }
    }
    (C->services + i)->nb_max = nb_max;

    printf("Donner le nombre de personnes dans le service %d : ", i + 1);
    scanf("%d", &(C->services + i)->nb_personnes);
    while ((C->services + i)->nb_personnes > (C->services + i)->nb_max) {
        printf("Erreur : Le nombre de personnes ne peut pas depasser le maximum (%d). Reessayez : ", (C->services + i)->nb_max);
        scanf("%d", &(C->services + i)->nb_personnes);
    }

    (C->services + i)->pourcentage_personne = ((float)(C->services + i)->nb_personnes / (float)(C->services + i)->nb_max) * 100;
    AllocationPersonne(C, i);

    for (int p = 0; p < (C->services + i)->nb_personnes; p++) {
        SaisirPersonne(C, i, p);
    }

    valid = 0;
    printf("Donner le nombre d'employes dans ce service : ");
    scanf("%d", &(C->services + i)->nb_employees);
    while (!valid) {
        if ((C->services + i)->nb_employees <= 0) {
            printf("Erreur : Le nombre d'employes dans ce service doit etre superieur a 0.\n");
            printf("Redonnez le nombre d'employes dans le service %d : ", i + 1);
            scanf("%d", &(C->services + i)->nb_employees);
        } else {
            valid = 1;
        }
    }

    AllocationEmployee(C, i);

    for (int e = 0; e < (C->services + i)->nb_employees; e++) {
        SaisirEmploye(C, i, e, 20);
    }
}


void SaisirPersonne(CENTRE *C , int s ,int p){
    ((C->services + s)->personnes + p)->code = p + 1;

                printf("Donner le nom de la personne %d dans le service %d : ", p + 1, s + 1);
                scanf("%s", ((C->services + s)->personnes + p)->nom);

                printf("Donner le prenom de la personne %d dans le service %d : ", p + 1, s + 1);
                scanf("%s", ((C->services + s)->personnes + p)->prenom);

                printf("Donner la difficulte de la personne %d dans le service %d : ", p + 1, s + 1);
                scanf("%s", ((C->services + s)->personnes + p)->difficulte);

                printf("Donner la date d'inscription (jour mois annee) de la personne %d dans le service %d : ", p + 1, s + 1);
                DATE d=SaisirDate();
                ((C->services + s)->personnes + p)->inscription.jour=d.jour;
                ((C->services + s)->personnes + p)->inscription.mois=d.mois;
                ((C->services + s)->personnes + p)->inscription.annee=d.annee;


                int c=Duree_Sejour(((C->services + s)->personnes + p)->inscription);
                ((C->services + s)->personnes + p)->duree_sejour=c;

    }


void SaisirCentre(CENTRE *C){
    int valid = 0;

    printf("Donner libelle du centre : \n");
    scanf("%s", C->libelle);

    printf("Donner le nombre de chambres : \n");
    scanf("%d", &C->nb_chambre);
    while (!valid) {

     if (C->nb_chambre < 0) {
        printf("Erreur : Le nombre de chambres ne peut pas etre negatif.\n");
        printf("Redonnez le nombre de chambres : \n ");
        scanf("%d", &C->nb_chambre);

    } else {
        valid = 1;
    }
}
    valid=0;

        printf("Donner le nombre de services : \n");
        scanf("%d", &C->nb_service);
    while (!valid) {

     if (C->nb_service < 0) {
        printf("Erreur : Le nombre de services ne peut pas etre negatif.\n");
        printf("Redonnez le nombre de services : \n ");
        scanf("%d", &C->nb_service);

    } else {
        valid = 1;
    }
}
        AllocationService(C);
    for (int s = 0; s < C->nb_service; s++) {
        SaisirService(C, s);
    }
    SommeBudget(C);

    }

void SaisirEmploye(CENTRE * C ,int s, int e , float cout){
    int valid = 0;

    ((C->services + s)->employees + e)->code = e + 1;

    printf("Donner le nom de l'employe %d dans le service %d : ", e + 1, s + 1);
    scanf("%s", ((C->services + s)->employees + e)->nom);

    printf("Donner le prenom de l'employe %d dans le service %d : ", e + 1, s + 1);
    scanf("%s", &((C->services + s)->employees + e)->prenom);

    printf("Donner le nombre d'heures travailleees pour l'employe %d dans le service %d : ", e + 1, s + 1);
    scanf("%d", &((C->services + s)->employees + e)->ht);

    while (!valid) {

    if (((C->services + s)->employees + e)->ht < 0) {
        printf("Erreur : Le nombre d'heures travaillees ne peut pas etre negatif.\n");
        printf("Redonnez le nombre d'heures travaillees pour l'employe %d dans le service %d : \n", e + 1, s + 1);
        scanf("%d", &((C->services + s)->employees + e)->ht);

    } else {
        valid = 1;
    }
    }
    printf("\nSaisir la date de debut de travail (jour mois annee) pour l'employe %d dans le service %d : ", e + 1, s + 1);
    DATE d = SaisirDate();

    ((C->services + s)->employees + e)->db.jour=d.jour;
    ((C->services + s)->employees + e)->db.mois=d.mois;
    ((C->services + s)->employees + e)->db.annee=d.annee;
    ((C->services + s)->employees + e)->salaire = ((C->services + s)->employees + e)->ht * cout;

    }

 void SommeBudget(CENTRE *C){
    float budget=0.0;
    for (int i = 0; i < C->nb_service; i++) {
    budget=budget+(C->services + i)->budget;
    }
    C->budget_totale=budget;

 }


void AfficherPersonne (CENTRE C ,int i ,int j){

printf("  Code: %d, Nom: %s %s, Difficulte: %s, Date d'inscription: %d/%d/%d, Duree du sejour: %d\n",
    ((C.services + i)->personnes + j)->code,
    ((C.services + i)->personnes + j)->nom,
    ((C.services + i)->personnes + j)->prenom,
    ((C.services + i)->personnes + j)->difficulte,
    ((C.services + i)->personnes + j)->inscription.jour,
    ((C.services + i)->personnes + j)->inscription.mois,
    ((C.services + i)->personnes + j)->inscription.annee,
    ((C.services + i)->personnes + j)->duree_sejour);


}

void AfficherEmployee (CENTRE C ,int i ,int j){

printf("  Code: %d, Nom: %s %s, Heure de travail: %d, Salaire: %.2f, Date de debut: %d/%d/%d\n",
((C.services + i)->employees + j)->code, ((C.services + i)->employees + j)->prenom, ((C.services + i)->employees + j)->nom, ((C.services + i)->employees + j)->ht, ((C.services + i)->employees + j)->salaire,
((C.services + i)->employees + j)->db.jour, ((C.services + i)->employees + j)->db.mois, ((C.services + i)->employees + j)->db.annee);


}



void AfficherService(CENTRE C, int s) {

    printf("Service %d: %s\n", (C.services + s)->code, (C.services + s)->libelle);
    printf("Nombre d'employes: %d\n", (C.services + s)->nb_employees);
    printf("Budget: %.2f\n", (C.services + s)->budget);
    printf("Nombre de personnes: %d\n", (C.services + s)->nb_personnes);
    printf("Nombre maximum de personnes: %d\n", (C.services + s)->nb_max);
    printf("Pourcentage de personnes dans le service: %.2f%%\n", ((float)(C.services + s)->nb_personnes / (float)(C.services + s)->nb_max) * 100);
    printf("===================================\n");



    printf("Employes:\n");
    for (int j = 0; j < (C.services + s)->nb_employees; j++) {
        AfficherEmployee(C, s, j);
        printf("===================================\n");
    }


    printf("Personnes:\n");
    for (int j = 0; j < (C.services + s)->nb_personnes; j++) {
        AfficherPersonne(C, s, j);
    }
    printf("-----------------------------------\n");
}


 void AfficherCentre(CENTRE C){

printf("===================================\n");
        printf("Centre: %s\n", C.libelle);
        printf("Nombre de services: %d\n", C.nb_service);
        printf("Nombre de chambres: %d\n", C.nb_chambre);
        printf("Budget total: %.2f%\n", C.budget_totale);

        printf("===================================\n");
if (C.nb_service > 0) {
        for (int i = 0; i < C.nb_service; i++) {
            AfficherService(C, i);
        }
    } else {
        printf("Aucun service disponible pour ce centre.\n");
    }
}




