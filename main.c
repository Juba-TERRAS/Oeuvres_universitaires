#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "model.c"
#include "model.h"
#include "conio.h"
#include "conio.c"
#include "affichage.c"

int main()
{
    system("COLOR F0");
    FILE *f=NULL;
    int choix;
    char inter[256]="";
/*affichage du l'introduction ainsi que de logo*/
    struct enseignant *TAB=malloc(sizeof(struct enseignant)*100000);
    grand_cadre();
    logo_esi();
    getche();
/*le switch pour les choix*/
do{
system("cls");
menu();
scanf("%d",&choix);
Color(0,15);
switch(choix)
{
/*******************************************************************************************/
     case 1:
     system("cls");
     f=ouvrir('N');
     chargement(f,TAB,generation_alea(TAB));
     fermer(f);
     break;
/*******************************************************************************************/
     case 2:
     f=ouvrir('A');
     afficher_fichier(f);
     fermer(f);
     break;
/*******************************************************************************************/
     case 3:
     f=ouvrir('A');
     afficher_supp(f);
     fermer(f);
     break;
/*******************************************************************************************/
     case 4:
     f=ouvrir('A');
     insertion(f);
     fermer(f);
     break;
/*******************************************************************************************/
     case 5:
     f=ouvrir('A');
     system("cls");
     Color(0,15);
     printf("+=====================================================================================================================+\n");
     Color(05,15);
     printf("|                                   Suppression d'un enseignant avec sa cle                                           |\n");
     Color(0,15);
     printf("+=====================================================================================================================+\n");
     printf("\nIntroduisez la cle de l enseignant a supprimer :  ");
     saisie_chaine(inter);
     printf("\n");
     int sup=suppression_logique(f,inter,0);
     fermer(f);
     if(sup==1)
     {
     printf("\n\n+=====================================================================================================================+\n");
     Color(2,15);
     printf("|                               Operation terminee . Suppression effectue avec succee                                 |\n");
     Color(0,15);
     printf("+=====================================================================================================================+\n\n");
     Color(1,15);
     printf("                                        Appuyez sur n import quelle touche pour continuer !!!!!!!!   ");
     getche();
     }
     sup=0;
     break;
/*******************************************************************************************/
     case 6:
     f=ouvrir('A');
     afficher_region(f);
     fermer(f);
     break;
/*******************************************************************************************/
     case 7:
     f=ouvrir('A');
     supprim_specialite(f);
     fermer(f);
     break;
/*******************************************************************************************/
     case 9:
     f=ouvrir('A');
     modification_etablissement(f);
     fermer(f);
     break;
/*******************************************************************************************/
     case 10 :
     f=ouvrir('A');
     reorganisation(f);
     fermer(f);
     break;
/*******************************************************************************************/
     case 8:
     f=ouvrir('A');
     requete_interval(f);
     fermer(f);
     break;
/*******************************************************************************************/
     case 11:
     f=ouvrir('A');
     afficher_entete(f);
     fermer(f);
     break;
/*******************************************************************************************/
     case 12:
     f=ouvrir('A');
     afficher_bloc(f);
     fclose(f);
     break;
/*******************************************************************************************/
     case 13:
     system("cls");
     thanks();
     break;
/*******************************************************************************************/
     default :
     affichage_erreur_switch();
     break;
/*******************************************************************************************/
}

}while(choix!=13);
return 0;
}
