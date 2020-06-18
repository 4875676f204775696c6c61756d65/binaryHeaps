//
//  main.c
//  Projet SDD 2 : Tas binaires
//
//  Created by Hugo GUILLAUME on 08/12/2019.
//  Copyright © 2019 Hugo GUILLAUME. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/timeb.h>

#define N 10

typedef struct S_tableau{
    int *tab;
    int length;
}Tableau;

Tableau * init_tab(int lengh){
    Tableau * new  = malloc(sizeof(Tableau));
    new->tab = calloc(lengh, sizeof(*new->tab));   // initialiser le tableau
    new->length = 0;
    return new;
}

void aff_tas(Tableau * T_binaire){
    
    if(T_binaire->length > 0){
        printf("\n");
        for (int i = 0; i < T_binaire->length ; i++){
            printf("%d => ", T_binaire->tab[i]);
        }
    }else{
        printf("\nVIDE !!.");
    }
    printf("\n");
    
}

int entre_nombre(){
    
    int data = 0;
    /*
    printf("\nEntrer un nombre : ");
    scanf("%d",&data);
    getchar();
     */
    data = rand()%100;
    return data;
    
}

void wait_user(){
    char entre = '\0';
    printf("\n\nAppuyer sur entrer pour continuer...");
    do{
        entre = getchar();
    }while (entre != '\n');
}

Tableau * creer_tab(int lengh){
    
    Tableau * new = init_tab(lengh);
    for (int i = 0; i < lengh ; i++) {
        new->tab[i] = entre_nombre();
        new->length ++;
    }
    if (new->length == lengh){
        printf("\nUn tableau utilisateur avec %d valeur a bien ete genere.",lengh);
    }else{
        printf("--> %d", new->length);
    }
    return new;
}

Tableau * creer_tableau_alea(int taille){
    
    Tableau * new = init_tab(taille);
    new->length = taille;
    
    for (int i = 0; i < taille ; i++) {
        new->tab[i] = rand()%100;
    }
    
    return new;
}

Tableau * copier_tab(Tableau * envoyeur, Tableau * receveur){
    
    for (int i = 0; i < envoyeur->length; i++) {
        receveur->tab[i] = envoyeur->tab[i];
        receveur->length ++;
    }
    return receveur;
}

Tableau * ajouter_nb_T_binaire(Tableau * T_binaire, Tableau * TAB){
    
    if (T_binaire != NULL){
        if (TAB != NULL){
            if (TAB->length == 0){
                printf("Ce tableau est vide.");
            }else{
                int x = T_binaire->length;
                int ajout = TAB->tab[TAB->length-1];
                while (x > 0 && ajout > T_binaire->tab[(x-1)/2]){
                    
                    T_binaire->tab[x] = T_binaire->tab[(x-1)/2];
                    x = ((x-1)/2);
                }
                T_binaire->tab[x] = ajout;
                TAB->length = TAB->length - 1;
                T_binaire->length = T_binaire->length + 1;
            }
        }else{
            printf("Erreur : Le tableau d'utilisateur n'existe pas creer le.");
        }
    }else{
        printf("Erreur : Le tas n'existe pas initialise le. CREATION;");
    }
    
    return T_binaire;
}

Tableau * retirer_nb_T_binaire(Tableau * T_binaire){
    
    if (T_binaire != NULL){
        if (T_binaire->length > 0){
            int x = 0;
            int end = 1;
            int sauv = 0;
            int valeur = T_binaire->tab[T_binaire->length-1];
            int max = T_binaire->length - 1;
            T_binaire->length = T_binaire->length -1;
                while( ( (valeur < T_binaire->tab[x*2+1] && max > 2*x+1) || ( T_binaire->tab[x*2+2] > valeur && 2*x+2 < max ) ) && (end != 0) ){
                    
                    if (T_binaire->tab[2*x+1] < T_binaire->tab[x*2+2] && 2*x+2 <= max) {
                        T_binaire->tab[x] = T_binaire->tab[x*2+2];
                        x = 2 * x + 2;
                    }else {
                        T_binaire->tab[x] = T_binaire->tab[x*2+1];
                        x = 2 * x + 1;
                    }
                   if (x * 2 + 2 >= max){
                       end = 0;
                       sauv = x;
                       x = 0;
                   }else{
                       sauv = x;
                   }
                }
                T_binaire->tab[sauv] = valeur;
                
        }else{
            printf("Erreur : Le tas n'existe pas initialise le.");
        }
    }
    return T_binaire;
}

Tableau * trier_tasBinaire(Tableau * tas){
    
    int temp = 0;
    
    for (int i = 0; i < tas->length-1 ; i++){
        if((2*i + 1) <= tas->length-1 && tas->tab[i] < tas->tab[2*i + 1]){
            
            int j = 2 * i + 1;
            while ( j > 0 && tas->tab[(j-1)/2] < tas->tab[j]){
                temp = tas->tab[(j-1)/2];
                tas->tab[(j-1)/2] = tas->tab[j];
                tas->tab[j] = temp;
                j = (j-1) / 2;
            }
        }
        if((2 * i + 2 <= tas->length-1) && tas->tab[i] < tas->tab[2*i + 2]){
            
            int j = 2*i + 2;
            while ( j > 0 && tas->tab[j] > tas->tab[(j-1) / 2]){
                temp = tas->tab[(j-1) / 2];
                tas->tab[(j-1) / 2] = tas->tab[j];
                tas->tab[j] = temp;
                j = (j-1) / 2;
            }
        }
    }
    return tas;
}

int renvoyer_nb_plusgrand(Tableau * T_binaire){
    if (T_binaire->length != 0){
        return T_binaire->tab[0];
    }else{
        printf("La liste est vide ");
        return -1;
    }
}

void free_tab(Tableau * tab){
    free(tab->tab);
    free(tab);
}

//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------
//Les algorithme suivant realisent les etapes demande.

void Etape_1(){
    printf("Etape 1 :\n");
    printf("Pour cette etape nous avons declarer la structure suivante:\n\n");
    printf("        typedef struct S_tableau{\n");
    printf("            int *tab;\n");
    printf("            int length;\n");
    printf("        }Tableau;\n");
}

void Etape_2(Tableau * T_binaire){
    printf("Etape 2 :\n");
    if (T_binaire->length != 0){
        printf("\nOn nous a donne en entre le tas binaire suivant :");
        aff_tas(T_binaire);
        printf("\nLe plus grand nombre du tas binaire est : %d", renvoyer_nb_plusgrand(T_binaire));
    }else{
        printf("\nLa liste est vide ");
    }
}

void Etape_3(Tableau * TAB){
    
    printf("Etapes 3 :\n");
    Tableau * T_binaire = init_tab(N);
    printf("\nOn nous a donné en entree le tableau suivant :");
    aff_tas(TAB);
    for (int i = 0; i < N; i++){
        T_binaire = ajouter_nb_T_binaire(T_binaire, TAB);
    }
    printf("A partir de ce dernier on obtient le tas binaire (tas max) ci dessous :");
    aff_tas(T_binaire);
    
}

void Etape_4(Tableau * T_binaire){
    
    printf("Etape 4 :\n");
    printf("\nOn nous a donné en entree le tas binaire suivant :");
    aff_tas(T_binaire);
    printf("\nOn va retirer progressivement les elements tout en conservant les proprietes du tas binaire :");
    for (int i = 0; i < N; i++){
        T_binaire = retirer_nb_T_binaire(T_binaire);
        aff_tas(T_binaire);
    }
    
}

void Etape_5(Tableau * TAB){
    
    printf("Etape 5 :\n");
    printf("\nOn nous a donne le tableau suivant en entree : ");
    aff_tas(TAB);
    printf("\nOn commence par creer un tas binaire avec les valeurs de ce tableau :");
    Tableau * T_binaire = init_tab(N);
    for (int i = 0; i < N; i++){
        T_binaire = ajouter_nb_T_binaire(T_binaire, TAB);
    }
    aff_tas(T_binaire);
    printf("\nOn va maintenant utiliser ce tas binaire pour creer un tableau trier avec les valeur du tableau donne en entree : ");
    Tableau * TAB_trier = init_tab(N);
    for (int i = 0; i < N; i++){
        TAB_trier->tab[N - 1 - i] = T_binaire->tab[0];
        TAB_trier->length ++;
        T_binaire = retirer_nb_T_binaire(T_binaire);
    }
    aff_tas(TAB_trier);
    
}

void Etape_6(Tableau * TAB){
    
    printf("Etape 6 :\n");
    printf("\nOn nous a donne le tableau suivant en entree : ");
    aff_tas(TAB);
    
    TAB = trier_tasBinaire(TAB);
    printf("\nOn commence par le transformer en tas binaire :");
    
    aff_tas(TAB);
    
    printf("\nOn va maintenant trier ce tableau en place donc sans utiliser de tableaux intermediare : ");
    
    for (int i = 0; i < N; i++){
        int temp = TAB->tab[0];
        TAB = retirer_nb_T_binaire(TAB);
        TAB->tab[N - 1 - i] = temp;
    }
    TAB->length = N;
    aff_tas(TAB);
    
}

//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------

Tableau * ajouter_nb_T_binaire_Tmin(Tableau * T_binaire, Tableau * TAB){
    
    if (T_binaire != NULL){
        if (TAB != NULL){
            if (TAB->length == 0){
                printf("Ce tableau est vide.");
            }else{
                int x = T_binaire->length;
                int ajout = TAB->tab[TAB->length-1];
                while (x > 0 && ajout < T_binaire->tab[(x-1)/2]){
                    
                    T_binaire->tab[x] = T_binaire->tab[(x-1)/2];
                    x = ((x-1)/2);
                }
                T_binaire->tab[x] = ajout;
                TAB->length = TAB->length - 1;
                T_binaire->length = T_binaire->length + 1;
            }
        }else{
            printf("Erreur : Le tableau d'utilisateur n'existe pas creer le.");
        }
    }else{
        printf("Erreur : Le tas n'existe pas initialise le. CREATION;");
    }
    
    return T_binaire;
}


Tableau * retirer_nb_T_binaire_Tmin(Tableau* T_binaire){
    
    if (T_binaire != NULL){
        if (T_binaire->length > 0){
            int x = 0;
            int valeur = T_binaire->tab[T_binaire->length-1];
            int max = T_binaire->length - 1;
            T_binaire->length = T_binaire->length -1;
            while( (valeur > T_binaire->tab[x*2+1] && max >= 2*x+1) || ( T_binaire->tab[x*2+2] < valeur && 2*x+2 < max )){
                
                if (T_binaire->tab[2*x+1] > T_binaire->tab[x*2+2] && 2*x+2 <= max) {
                    T_binaire->tab[x] = T_binaire->tab[x*2+2];
                    x = 2*x+2;
                }else {
                    T_binaire->tab[x] = T_binaire->tab[x*2+1];
                    x = 2 * x + 1;
                }
            }
            T_binaire->tab[x] = valeur;
            
        }else{
            printf("Erreur : Le tas n'existe pas initialise le.");
        }
    }
    return T_binaire;
}

int renvoyer_nb_pluspetit(Tableau * T_binaire){
    if (T_binaire->length != 0){
        printf("\nLe plus petit nombre du tas binaire est : %d", T_binaire->tab[0]);
        return T_binaire->tab[0];
    }else{
        printf("La liste est vide ");
        return -1;
    }
}

Tableau * trier_tasBinaire_Tmin(Tableau * tas){
    
    int temp = 0;
    
    for (int i = 0; i < tas->length-1 ; i++){
        if((2*i + 1) <= tas->length-1 && tas->tab[i] > tas->tab[2*i + 1]){
            
            int j = 2 * i + 1;
            while ( j > 0 && tas->tab[(j-1)/2] > tas->tab[j]){
                temp = tas->tab[(j-1)/2];
                tas->tab[(j-1)/2] = tas->tab[j];
                tas->tab[j] = temp;
                j = (j-1) / 2;
            }
        }
        if((2 * i + 2 <= tas->length-1) && tas->tab[i] > tas->tab[2*i + 2]){
            
            int j = 2*i + 2;
            while ( j > 0 && tas->tab[j] < tas->tab[(j-1) / 2]){
                temp = tas->tab[(j-1) / 2];
                tas->tab[(j-1) / 2] = tas->tab[j];
                tas->tab[j] = temp;
                j = (j-1) / 2;
            }
        }
    }
    return tas;
}

//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------

void calcul_mediane(){
    
    printf("\nCe programme permet de calculer de facon optimale la mediane des nombres entres.");
    int end = 0;
    Tableau * MIN = init_tab(N);
    Tableau * MAX = init_tab(N);
    Tableau * stockage = init_tab(N);
    int Mediane = 0;
    int compt = 0;
    while (end == 0 && compt != N) {
        stockage->tab[0] = entre_nombre();
        stockage->length = 1;
        printf("\n nouveaux nb = %d", stockage->tab[0]);
        if (stockage->tab[0] < 100 && stockage->tab[0] >= 0) {
            if (compt == 0){
                Mediane = stockage->tab[0];
            }else{
                if (stockage->tab[0] == Mediane){
                    if (MIN->length <= MAX->length) {
                        MIN = ajouter_nb_T_binaire_Tmin(MIN, stockage);
                    }else{
                        MAX = ajouter_nb_T_binaire(MAX, stockage);
                    }
                }else if (stockage->tab[0] < Mediane){
                    
                    MAX = ajouter_nb_T_binaire(MAX, stockage);
                    
                    if (MAX->length > MIN->length + 1) {
                        stockage->tab[0] = Mediane;
                        stockage->length = 1;
                        Mediane = MAX->tab[0];
                        MAX = retirer_nb_T_binaire(MAX);
                        MIN = ajouter_nb_T_binaire_Tmin(MIN, stockage);
                    }
                    
                }else if (stockage->tab[0] > Mediane){
                    
                    MIN = ajouter_nb_T_binaire_Tmin(MIN, stockage);
                    
                    if (MIN->length > MAX->length + 1) {
                        stockage->tab[0] = Mediane;
                        stockage->length = 1;
                        Mediane = MIN->tab[0];
                        MIN = retirer_nb_T_binaire_Tmin(MIN);
                        MAX = ajouter_nb_T_binaire(MAX, stockage);
                    }
                    
                }else{
                    printf("\nPutain de bug de merde.");
                }
            }
            
        }else{
            end = 1;
        }
        compt ++;
        printf("\nLa mediane est maintenant de %d.", Mediane);
    }
    
}

//Fin calcule de mediane.
//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------
//On va maintenant prolonger ce projet avec quelques "pour aller plus loin" :

Tableau * tri_insertion(Tableau * tab){
    
    for (int i = 1 ; i < tab->length ; i++) {
        int valeur = tab->tab[i];
        
        int curseur = i;
        
        while (curseur > 0 && tab->tab[curseur - 1] > valeur) {
            tab->tab[curseur] = tab->tab[curseur - 1];
            curseur --;
        }
        
        tab->tab[curseur] = valeur;
        
    }
    
    return tab;
}

Tableau * tri_par_tas(Tableau * TAB){
    
    TAB = trier_tasBinaire(TAB);
    
    for (int i = 0; i < N; i++){
        int temp = TAB->tab[0];
        TAB = retirer_nb_T_binaire(TAB);
        TAB->tab[N - 1 - i] = temp;
    }
    TAB->length = N;
    return TAB;
}

Tableau * tri_selection(Tableau * TAB){

    for (int i = 0; i < TAB->length - 1; i++){
        int mini = i;
        for (int j = i + 1; j < TAB->length; j++){
            if (TAB->tab[j] < TAB->tab[mini]){
                mini = j;
            }
        }
        
        int x = TAB->tab[i];
        TAB->tab[i] = TAB->tab[mini];
        TAB->tab[mini] = x;
    }
    
    return TAB;
}

void comparer_time_tri(){
    
    struct timeb debut_insertion, fin_insertion, debut_tas, fin_tas, debut_selection, fin_selection;
    
    Tableau * trier1 = creer_tableau_alea(N);
    Tableau * trier2 = init_tab(N);
    Tableau * trier3 = init_tab(N);
    trier2 = copier_tab(trier1, trier2);
    trier3 = copier_tab(trier1, trier3);
    
    printf("On a le tas ci dessous :\n");
    aff_tas(trier1);
    printf("On va le trier avec diffenrents algo et comparer les durees.\n");
    
    ftime(&debut_insertion);
    
    trier1 = tri_insertion(trier1);
    
    ftime(&fin_insertion);

    ftime(&debut_tas);
    
    trier2 = tri_par_tas(trier2);
    
    ftime(&fin_tas);
    
    ftime(&debut_selection);
    
    trier3 = tri_selection(trier3);
    
    ftime(&fin_selection);
     
    printf("\nLe tri par insertion a pris %d ms.", (int)(1000 * ( fin_insertion.time - debut_insertion.time ) + ( fin_insertion.millitm - debut_insertion.millitm )));
    printf("\nLe tri par tas a pris %d ms.", (int)(1000 * ( fin_tas.time - debut_tas.time ) + ( fin_tas.millitm - debut_tas.millitm )));
    printf("\nLe tri par selection a pris %d ms.", (int)(1000 * ( fin_selection.time - debut_selection.time ) + ( fin_selection.millitm - debut_selection.millitm )));
    
    free_tab(trier1);
    free_tab(trier2);
    free_tab(trier3);
    
}

//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------

void demonstration(){
    srand((unsigned int)time(NULL));
    
    if(N >= 0){
        Tableau * trier1 = creer_tableau_alea(N);
        Tableau * trier2 = creer_tableau_alea(N);
        Tableau * trier3 = creer_tableau_alea(N);
        Tableau * trier4 = creer_tableau_alea(N);
        
        Etape_1();
        
        wait_user();
        
        trier1 = trier_tasBinaire(trier1);
        
        printf("\n\n");
        
        Etape_2(trier1);
        
        wait_user();
        
        printf("\n\n");
        
        Etape_3(trier2);
        
        wait_user();
        
        printf("\n\n");
        
        Etape_4(trier1);
        
        wait_user();
        
        printf("\n\n");
        
        Etape_5(trier3);
        
        wait_user();
        
        printf("\n\n");
        
        Etape_6(trier4);
        
        wait_user();
        
        printf("\n\n");

        printf("On a egalement realise toute les fonctions en version 'tas min'.");
        
        printf("\n");
        
        wait_user();
        
        calcul_mediane();
        
        wait_user();
        
        printf("\n\n");
        
        comparer_time_tri();
        
        free_tab(trier1);
        free_tab(trier2);
        free_tab(trier3);
        free_tab(trier4);
    }else{
        printf("Attention la taille des tableaux est parametre sur une taille negative. Definnissez une taille positive ou nul.");
    }
}

//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------


int main() {
    
    demonstration();
    
    //comparer_time_tri();
    
    // insert code here...
    printf("\n\nWork in progress... \n");
    return 0;
}
