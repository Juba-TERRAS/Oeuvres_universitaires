/*********************************************************************************************************************************************************/
/*                                                 Les fonctions d affichage                                                                             */
/*********************************************************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "model.c"
#include "model.h"
#include "conio.h"
#include "conio.c"
#include "affichage.c"


void Color(int couleurDuTexte,int couleurDeFond) /* fonction d'affichage de couleurs*/
{
        HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}
/*********************************************************************************************************************************************************/
   void loading()/*procedure pour afficher un loading*/
        {
            int l;
            gotoxy(11,12);
            delline();
            Color(1,15);
            printf("       LOADING ");
            for(l=0;l<35;l++)
            {
            Sleep(1);
            Color(10,15);
            printf("%c ",254);}
        }
/*********************************************************************************************************************************************************/
void affichage_erreur_ouverture(){/*affichage erreur d'ouverture d'un fichier*/
    system("cls");
    cadre();
    Color(0,15);
    gotoxy(18,5);
    printf("         @@ ");
    printf("\n");gotoxy(18,6);
    printf("        @  @ ");
    printf("\n");gotoxy(18,7);
    printf("       @    @ ");
    printf("\n");gotoxy(18,8);
    printf("      @      @ ");
    printf("\n");gotoxy(18,9);
    printf("     @        @ ");
    printf("\n");gotoxy(18,10);
    printf("    @          @ ");
    printf("\n");gotoxy(18,11);
    printf("   @            @ ");
    printf("\n");gotoxy(18,12);
    printf("  @              @ ");
    printf("\n");gotoxy(18,13);
    printf(" @                @ ");
    printf("\n");gotoxy(18,14);
    printf("@@@@@@@@@@@@@@@@@@@@");
    Color(6,15);
    gotoxy(28,7);printf("%c ",254);
    gotoxy(28,8);printf("%c ",254);gotoxy(28,9);printf("%c ",254);gotoxy(28,10);printf("%c ",254);gotoxy(28,11);printf("%c ",254);
    gotoxy(28,13);printf("%c ",254);
    message_erreur(40,12);
    erreur_ouverture_fichier(35,13);
    gotoxy(15,20);
    Color(0,15);
    Color(0,15);
    printf("²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²");
    gotoxy(17,21);
    printf("                 Appuyez sur n'import quelle touche pour continuer   ");
    Color(0,15);
    char c=getch();
}
/*********************************************************************************************************************************************************/
void affichage_erreur_vide(){/*affichage erreur de fichier vide*/
    system("cls");
    cadre();
    Color(0,15);
    gotoxy(18,5);
    printf("         @@ ");
    printf("\n");gotoxy(18,6);
    printf("        @  @ ");
    printf("\n");gotoxy(18,7);
    printf("       @    @ ");
    printf("\n");gotoxy(18,8);
    printf("      @      @ ");
    printf("\n");gotoxy(18,9);
    printf("     @        @ ");
    printf("\n");gotoxy(18,10);
    printf("    @          @ ");
    printf("\n");gotoxy(18,11);
    printf("   @            @ ");
    printf("\n");gotoxy(18,12);
    printf("  @              @ ");
    printf("\n");gotoxy(18,13);
    printf(" @                @ ");
    printf("\n");gotoxy(18,14);
    printf("@@@@@@@@@@@@@@@@@@@@");
    Color(6,15);
    gotoxy(28,7);printf("%c ",254);
    gotoxy(28,8);printf("%c ",254);gotoxy(28,9);printf("%c ",254);gotoxy(28,10);printf("%c ",254);gotoxy(28,11);printf("%c ",254);
    gotoxy(28,13);printf("%c ",254);
    message_erreur(40,12);
    erreur_fichier_vide(35,13);
    gotoxy(15,20);
    Color(0,15);
    Color(0,15);
    printf("²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²");
    gotoxy(17,21);
    printf("                 Appuyez sur n'import quelle touche pour continuer   ");
    Color(0,15);
    char c=getch();
    system("cls");
}
/*********************************************************************************************************************************************************/
void affichage_erreur_cle_inexistante(){/*affichage erreur clé introuvable*/
    system("cls");
    cadre();
    Color(0,15);
    gotoxy(18,5);
    printf("         @@ ");
    printf("\n");gotoxy(18,6);
    printf("        @  @ ");
    printf("\n");gotoxy(18,7);
    printf("       @    @ ");
    printf("\n");gotoxy(18,8);
    printf("      @      @ ");
    printf("\n");gotoxy(18,9);
    printf("     @        @ ");
    printf("\n");gotoxy(18,10);
    printf("    @          @ ");
    printf("\n");gotoxy(18,11);
    printf("   @            @ ");
    printf("\n");gotoxy(18,12);
    printf("  @              @ ");
    printf("\n");gotoxy(18,13);
    printf(" @                @ ");
    printf("\n");gotoxy(18,14);
    printf("@@@@@@@@@@@@@@@@@@@@");
    Color(6,15);
    gotoxy(28,7);printf("%c ",254);
    gotoxy(28,8);printf("%c ",254);gotoxy(28,9);printf("%c ",254);gotoxy(28,10);printf("%c ",254);gotoxy(28,11);printf("%c ",254);
    gotoxy(28,13);printf("%c ",254);
    message_erreur(40,12);
    erreur_cle_inexistante(35,13);
    gotoxy(15,20);
    Color(0,15);
    Color(0,15);
    printf("²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²");
    gotoxy(17,21);
    printf("                 Appuyez sur n'import quelle touche pour continuer   ");
    Color(0,15);
    char c=getch();
    system("cls");
}
/*********************************************************************************************************************************************************/
void affichage_erreur_aucun_enreg(){/*affichage erreur aucun enregistrement supprimé logiquement  trouvé*/
    system("cls");
    cadre();
    Color(0,15);
    gotoxy(18,5);
    printf("         @@ ");
    printf("\n");gotoxy(18,6);
    printf("        @  @ ");
    printf("\n");gotoxy(18,7);
    printf("       @    @ ");
    printf("\n");gotoxy(18,8);
    printf("      @      @ ");
    printf("\n");gotoxy(18,9);
    printf("     @        @ ");
    printf("\n");gotoxy(18,10);
    printf("    @          @ ");
    printf("\n");gotoxy(18,11);
    printf("   @            @ ");
    printf("\n");gotoxy(18,12);
    printf("  @              @ ");
    printf("\n");gotoxy(18,13);
    printf(" @                @ ");
    printf("\n");gotoxy(18,14);
    printf("@@@@@@@@@@@@@@@@@@@@");
    Color(6,15);
    gotoxy(28,7);printf("%c ",254);
    gotoxy(28,8);printf("%c ",254);gotoxy(28,9);printf("%c ",254);gotoxy(28,10);printf("%c ",254);gotoxy(28,11);printf("%c ",254);
    gotoxy(28,13);printf("%c ",254);
    message_erreur(40,12);
    erreur_aucun_enreg(35,13);
    gotoxy(15,20);
    Color(0,15);
    Color(0,15);
    printf("²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²");
    gotoxy(17,21);
    printf("                 Appuyez sur n'import quelle touche pour continuer   ");
    Color(0,15);
    char c=getch();
    system("cls");
}
/*********************************************************************************************************************************************************/
void affichage_erreur_trouve(){/*affichage erreur clé introuvable*/
    system("COLOR F0");
    system("cls");
    cadre();
    Color(0,15);
    gotoxy(18,5);
    printf("         @@ ");
    printf("\n");gotoxy(18,6);
    printf("        @  @ ");
    printf("\n");gotoxy(18,7);
    printf("       @    @ ");
    printf("\n");gotoxy(18,8);
    printf("      @      @ ");
    printf("\n");gotoxy(18,9);
    printf("     @        @ ");
    printf("\n");gotoxy(18,10);
    printf("    @          @ ");
    printf("\n");gotoxy(18,11);
    printf("   @            @ ");
    printf("\n");gotoxy(18,12);
    printf("  @              @ ");
    printf("\n");gotoxy(18,13);
    printf(" @                @ ");
    printf("\n");gotoxy(18,14);
    printf("@@@@@@@@@@@@@@@@@@@@");
    Color(6,15);
    gotoxy(28,7);printf("%c ",254);
    gotoxy(28,8);printf("%c ",254);gotoxy(28,9);printf("%c ",254);gotoxy(28,10);printf("%c ",254);gotoxy(28,11);printf("%c ",254);
    gotoxy(28,13);printf("%c ",254);
    message_erreur(40,12);
    erreur_trouve(35,13);
    gotoxy(15,20);
    Color(0,15);
    printf("²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²");
    gotoxy(17,21);
    printf("                 Appuyez sur n'import quelle touche pour continuer   ");
    Color(0,15);
    char c=getch();
    system("cls");
}
/*********************************************************************************************************************************************************/
void affichage_erreur_existe(){/*affichage erreur cle existe deja*/
    system("cls");
    cadre();
    Color(0,15);
    gotoxy(18,5);
    printf("         @@ ");
    printf("\n");gotoxy(18,6);
    printf("        @  @ ");
    printf("\n");gotoxy(18,7);
    printf("       @    @ ");
    printf("\n");gotoxy(18,8);
    printf("      @      @ ");
    printf("\n");gotoxy(18,9);
    printf("     @        @ ");
    printf("\n");gotoxy(18,10);
    printf("    @          @ ");
    printf("\n");gotoxy(18,11);
    printf("   @            @ ");
    printf("\n");gotoxy(18,12);
    printf("  @              @ ");
    printf("\n");gotoxy(18,13);
    printf(" @                @ ");
    printf("\n");gotoxy(18,14);
    printf("@@@@@@@@@@@@@@@@@@@@");
    Color(6,15);
    gotoxy(28,7);printf("%c ",254);
    gotoxy(28,8);printf("%c ",254);gotoxy(28,9);printf("%c ",254);gotoxy(28,10);printf("%c ",254);gotoxy(28,11);printf("%c ",254);
    gotoxy(28,13);printf("%c ",254);
    message_erreur(40,12);
    erreur_cle_existe(35,13);
    gotoxy(15,20);
    Color(0,15);
    printf("²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²");
    gotoxy(17,21);
    printf("                 Appuyez sur n'import quelle touche pour continuer   ");
    Color(0,15);
    char c=getch();
    system("cls");
}
/*********************************************************************************************************************************************************/
void affichage_erreur_switch(){/*affichage erreur de choix invalid de switch*/
    system("cls");
    cadre();
    Color(0,15);
    gotoxy(18,5);
    printf("         @@ ");
    printf("\n");gotoxy(18,6);
    printf("        @  @ ");
    printf("\n");gotoxy(18,7);
    printf("       @    @ ");
    printf("\n");gotoxy(18,8);
    printf("      @      @ ");
    printf("\n");gotoxy(18,9);
    printf("     @        @ ");
    printf("\n");gotoxy(18,10);
    printf("    @          @ ");
    printf("\n");gotoxy(18,11);
    printf("   @            @ ");
    printf("\n");gotoxy(18,12);
    printf("  @              @ ");
    printf("\n");gotoxy(18,13);
    printf(" @                @ ");
    printf("\n");gotoxy(18,14);
    printf("@@@@@@@@@@@@@@@@@@@@");
    Color(6,15);
    gotoxy(28,7);printf("%c ",254);
    gotoxy(28,8);printf("%c ",254);gotoxy(28,9);printf("%c ",254);gotoxy(28,10);printf("%c ",254);gotoxy(28,11);printf("%c ",254);
    gotoxy(28,13);printf("%c ",254);
    message_erreur(40,12);
    erreur_switch(35,13);
    gotoxy(15,20);
    Color(0,15);
    printf("²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²");
    gotoxy(17,21);
    printf("                 Appuyez sur n'import quelle touche pour continuer   ");
    Color(0,15);
    char c=getch();
    system("cls");
}
/*********************************************************************************************************************************************************/
void message_erreur(int x,int y){/*Les differents messgae d'erreur*/
Color(0,15);
gotoxy(x,y);
printf("+============================+");
gotoxy(x,y+1);
Color(4,15);
printf("|");
printf("    ----    ERREUR     ---- |");
gotoxy(x,y+2);
Color(0,15);
printf("+============================+\n");
}
/*********************************************************************************************************************************************************/
void erreur_ouverture_fichier(int x,int y){
Color(0,15);
gotoxy(x-10,y+2);
printf("+============================================================+");
gotoxy(x-10,y+3);
Color(1,15);
printf("|");
printf("---- Le nom du fichier que vous avez saisie n existe pas----|");
gotoxy(x-10,y+4);
Color(0,15);
printf("+============================================================+\n");
}
/*********************************************************************************************************************************************************/
void erreur_fichier_vide(int x,int y){
Color(0,15);
gotoxy(x-10,y+2);
printf("+============================================================+\n");
gotoxy(x-10,y+3);
Color(1,15);
printf("|");
printf("--Il semble que le fichier ou vous voulez acceder est vide--|");
gotoxy(x-10,y+4);
Color(0,15);
printf("+============================================================+\n");
}
/*********************************************************************************************************************************************************/
void erreur_cle_inexistante(int x,int y){
Color(0,15);
gotoxy(x-10,y+2);
printf("+============================================================+\n");
gotoxy(x-10,y+3);
Color(1,15);
printf("|");
printf("--        la cle que vous avez saisie n existe pas        --|");
gotoxy(x-10,y+4);
Color(0,15);
printf("+============================================================+\n");
}
/*********************************************************************************************************************************************************/
void erreur_cle_existe(int x,int y){
Color(0,15);
gotoxy(x-10,y+2);
printf("+============================================================+\n");
gotoxy(x-10,y+3);
Color(1,15);
printf("|");
printf("--       la cle que vous avez saisie existe deja          --|");
gotoxy(x-10,y+4);
Color(0,15);
printf("+============================================================+\n");
}
/*********************************************************************************************************************************************************/
void erreur_aucun_enreg(int x,int y){
Color(0,15);
gotoxy(x-10,y+2);
printf("+============================================================+\n");
gotoxy(x-10,y+3);
Color(1,15);
printf("|");
printf("--  Il existe aucun enregistrement supprime logiquement   --|");
gotoxy(x-10,y+4);
Color(0,15);
printf("+============================================================+\n");
}
/*********************************************************************************************************************************************************/
void erreur_trouve(int x,int y){
Color(0,15);
gotoxy(x-10,y+2);
printf("+============================================================+\n");
gotoxy(x-10,y+3);
Color(1,15);
printf("|");
printf("--  Aucun enregistrement correspond a vos specifications  --|");
gotoxy(x-10,y+4);
Color(0,15);
printf("+============================================================+\n");
}
/*********************************************************************************************************************************************************/
void erreur_switch(int x,int y){
Color(0,15);
gotoxy(x-10,y+2);
printf("+============================================================+\n");
gotoxy(x-10,y+3);
Color(1,15);
printf("|");
printf("--                Votre choix est invalide                --|");
gotoxy(x-10,y+4);
Color(0,15);
printf("+============================================================+\n");

}
/*********************************************************************************************************************************************************/
void cadre(){/*affichage d'un cadre*/
    gotoxy(15,3);
for(int i=15;i<101;i++){
    printf("²");
}
for(int i=4;i<23;i++){
    gotoxy(15,i);
    printf("²²");
    gotoxy(99,i);
    printf("²²");
}
gotoxy(15,23);
for(int i=15;i<101;i++){
    printf("²");
}
}
/*********************************************************************************************************************************************************/
void grand_cadre(){/*affichage d'un grand cadre*/
    gotoxy(0,0);
    Color(3,15);
for(int i=0;i<120;i++){
    Sleep(5);
    printf("²");
}
for(int i=1;i<30;i++){
    gotoxy(120,i);
    Sleep(5);
    printf("²");
}
for(int i=0;i<120;i++){
    gotoxy(120-i,30);
    Sleep(5);
    printf("²");
}
for(int i=1;i<30;i++){
    gotoxy(1,30-i);
    Sleep(5);
    printf("²");
}
}
/*********************************************************************************************************************************************************/
void tres_grand_cadre(){/*affichage d'un tres grand cadre*/
    gotoxy(0,0);
    Color(3,15);
for(int i=0;i<120;i++){
    Sleep(5);
    printf("²");
}
for(int i=1;i<43;i++){
    gotoxy(1,i);
    Sleep(5);
    printf("²");
    gotoxy(120,i);
    Sleep(5);
    printf("²");
}
}
/*********************************************************************************************************************************************************/
void logo_esi(){/*affichage de l'introduction*/
 Color(13,15);
 gotoxy(2,2);Sleep(50);
 printf("REPEBLIQUE ALGERIENNE                                                                     MINISTERE DE L'ENSEIGNEMENT");
 gotoxy(2,3);Sleep(50);
 printf("DEMOCRATIQUE ET                                                                                   SUPERIEURE ET DE LA");
 gotoxy(2,4);Sleep(50);
 printf("POPULAIRE                                                                                      RECHERCHE SCIENTIFIQUE");
 gotoxy(50,3);
 Sleep(10);
 Color(2,15);
 printf("²²²²²²²  ²²²²²²²   ²²");
 gotoxy(50,4);
 Sleep(10);
 printf("²        ²         ²²");
 gotoxy(50,5);
 Sleep(10);
 printf("²²²²²²²  ²²²²²²²   ²²");
 gotoxy(50,6);
 Sleep(10);
 printf("²              ²   ²²");
gotoxy(50,7);
 Sleep(10);
 printf("²²²²²²²  ²²²²²²²   ²²");
 int i=0;
 gotoxy(1,10);
 for(i=1;i<=60;i++)
 {
     Color(3,15);
     gotoxy(i,10);
     Sleep(10);
     printf("²");
     gotoxy(120-i,10);
     Sleep(10);
     printf("²");
 }
 Color(11,15);
 gotoxy(10,13);Sleep(20);
 printf("²²²²²²²²²²²²²");
 gotoxy(10,14);Sleep(10);
 printf("      ²");Sleep(20);
 gotoxy(10,15);
 printf("      ²");Sleep(20);
 gotoxy(10,16);
 printf("      ²");Sleep(20);
 gotoxy(10,17);
 printf("      ²");Sleep(20);
 gotoxy(10,18);
 printf("      ²");Sleep(20);
 gotoxy(10,19);
 printf("      ²");Sleep(20);
 gotoxy(10,20);
 printf("      ²");Sleep(20);
 gotoxy(10,21);
 printf("      ²");Sleep(20);
/******/
 gotoxy(24,13);
 printf("²²²²²²²²²");Sleep(20);
 gotoxy(24,14);
 printf("²       ²");Sleep(20);
 gotoxy(24,15);
 printf("²       ²");Sleep(20);
 gotoxy(24,16);
 printf("²²²²²²²²²");Sleep(20);
 gotoxy(24,17);
 printf("²");Sleep(20);
 gotoxy(24,18);
 printf("²");Sleep(20);
 gotoxy(24,19);
 printf("²");Sleep(20);
 gotoxy(24,20);
 printf("²");Sleep(20);
 gotoxy(24,21);
 printf("²");Sleep(20);
/*********/
 gotoxy(45,13),Sleep(20);
 printf("²²²²²²²");
 gotoxy(45,14),Sleep(20);
 printf("²     ");
 gotoxy(45,15),Sleep(20);
 printf("²     ");
 gotoxy(45,16),Sleep(20);
 printf("²     ");
 gotoxy(45,17),Sleep(20);
 printf("²²²²²²²²");
 gotoxy(45,18),Sleep(20);
 printf("       ²");
 gotoxy(45,19),Sleep(20);
 printf("       ²");
 gotoxy(45,20),Sleep(20);
 printf("       ²");
 gotoxy(45,21),Sleep(20);
 printf("²²²²²²²²");
/******/
 gotoxy(57,13);
 printf("²²²²²²²²²");Sleep(20);
 gotoxy(57,14);
 printf("²       ");Sleep(20);
 gotoxy(57,15);
 printf("²       ");Sleep(20);
 gotoxy(57,16);
 printf("²²²²²²²²²");Sleep(20);
 gotoxy(57,17);
 printf("²");Sleep(20);
 gotoxy(57,18);
 printf("²");Sleep(20);
 gotoxy(57,19);
 printf("²");Sleep(20);
 gotoxy(57,20);
 printf("²");Sleep(20);
 gotoxy(57,21);
 printf("²");Sleep(20);
/*********/
 gotoxy(69,13),Sleep(20);
 printf("²²²²²²²");
 gotoxy(69,14),Sleep(20);
 printf("²     ");
 gotoxy(69,15),Sleep(20);
 printf("²     ");
 gotoxy(69,16),Sleep(20);
 printf("²     ");
 gotoxy(69,17),Sleep(20);
 printf("²²²²²²²²");
 gotoxy(69,18),Sleep(20);
 printf("       ²");
 gotoxy(69,19),Sleep(20);
 printf("       ²");
 gotoxy(69,20),Sleep(20);
 printf("       ²");
 gotoxy(69,21),Sleep(20);
 printf("²²²²²²²²");
/*********/
 gotoxy(81,13),Sleep(20);
 printf("²²²²²²²²²");
 gotoxy(81,14),Sleep(20);
 printf("²       ²");
 gotoxy(81,15),Sleep(20);
 printf("²       ²");
 gotoxy(81,16),Sleep(20);
 printf("²       ²");
 gotoxy(81,17),Sleep(20);
 printf("²       ²");
 gotoxy(81,18),Sleep(20);
 printf("²       ²");
 gotoxy(81,19),Sleep(20);
 printf("²       ²");
 gotoxy(81,20),Sleep(20);
 printf("²       ²");
 gotoxy(81,21),Sleep(20);
 printf("²²²²²²²²²");
/******/
 Color(3,15);
 for(i=1;i<=60;i++)
 {
     Color(3,15);
     gotoxy(i,23);
     Sleep(10);
     printf("²");
     gotoxy(120-i,23);
     Sleep(10);
     printf("²");
 }
 Color(5,15);
 gotoxy(25,24);Sleep(60);
 printf("+=====================================================================+");
 gotoxy(25,25);Sleep(60);
 printf("|      Realise par :|                TERRAS Juba                      |");
 gotoxy(25,26);Sleep(60);
 printf("|                   |                    &&                           |");
 gotoxy(25,27);Sleep(60);
 printf("|                   |                SAHI Kenza                       |");
 gotoxy(25,28);Sleep(60);
 printf("+=====================================================================+");
 gotoxy(100,28);
 Color(3,15);
 Sleep(100);
 printf("Debut   --->  ");
}
/*********************************************************************************************************************************************************/
void menu(){/*affichage du menu*/
    int i;
    grand_cadre();
    Color(5,15);
    gotoxy(35,3);Sleep(100);
    printf("²²²²²²²²²²²²²  ²²²²²²²²    ²        ²   ²       ²");
    gotoxy(35,4);Sleep(100);
    printf("²     ²     ²  ²           ²  ²     ²   ²       ²");
    gotoxy(35,5);Sleep(100);
    printf("²     ²     ²  ²²²²²²²²    ²    ²   ²   ²       ²");
    gotoxy(35,6);Sleep(100);
    printf("²     ²     ²  ²           ²      ² ²   ²       ²");
    gotoxy(35,7);Sleep(100);
    printf("²     ²     ²  ²²²²²²²²    ²        ²   ²²²²²²²²²");
    for(i=1;i<=60;i++)
 {
     Color(3,15);
     gotoxy(i,9);
     Sleep(5);
     printf("²");
     gotoxy(120-i,9);
     Sleep(5);
     printf("²");
 }
 for(i=10;i<30;i++){
    gotoxy(20,i);
    Sleep(10);
    printf("²");
    gotoxy(100,i);
    Sleep(10);
    printf("²");
 }
 Color(0,15);
 gotoxy(25,11);
 printf("1)-Creer un nouveau fichier");
 gotoxy(25,12);
 printf("2)-Afficher le contenu d'un ancien fichier");
 gotoxy(25,13);
 printf("3)-Afficher les enseignants supprimes logiquement dans un fichier");
 gotoxy(25,14);
 printf("4)-Insertion d'un nouvel enseignant dans un fichier");
 gotoxy(25,15);
 printf("5)-Suppression d'un enseignant par sa cle dans un fichier");
 gotoxy(25,16);
 printf("6)-Consultation des enseignants d'une region donnee");
 gotoxy(25,17);
 printf("7)-Suppression des enseigants d'une specialite donnee");
 gotoxy(25,18);
 printf("8)-Lancer une requette a interval");
 gotoxy(25,19);
 printf("9)-Modifier l'etablissement d'un enseigant en raison de sa mutation");
 gotoxy(25,20);
 printf("10)-Reorganisation d'un fichier");
 gotoxy(25,21);
 printf("11)-Afficher l'entete d'un fichier");
 gotoxy(25,22);
 printf("12)-Affichage de la disposition des 3 premiere blocs");
 gotoxy(25,23);
 printf("13)-Quitter");
 Color(3,15);
 for(i=20;i<100;i++){
    gotoxy(i,25);
    Sleep(10);
    printf("²");
 }
 gotoxy(25,27);
 Color(5,15);
 printf("       Veillez introduire votre choix Svp :  ");
}
/*********************************************************************************************************************************************************/
void thanks()/*une procedure pour afficher un merci*/
      {
            system("cls");
            grand_cadre();
            Color(3,15);
            Sleep(100);
            gotoxy(15,7);
            printf("                                                                           @@                  ");Sleep(60);
            gotoxy(15,8);
            printf("                                                                          @@@@                 ");Sleep(60);
            gotoxy(15,9);
            printf("          @@@@@@@@@@  @@@@@@        @@@@@@      @@@@@@@@@@    @@@@@@@@    @@@@                 ");Sleep(60);
            gotoxy(15,10);
            printf("          @@    @@@@      @@    @@@@    @@      @@    @@  @@@@    @@      @@                  ");Sleep(60);
            gotoxy(15,11);
            printf("          @@      @@      @@    @@      @@@@    @@        @@              @@                  ");Sleep(60);
            gotoxy(15,12);
            printf("          @@      @@      @@    @@@@@@@@@@@@    @@        @@              @@                  ");Sleep(60);
            gotoxy(15,13);
            printf("          @@      @@      @@    @@              @@        @@              @@                  ");Sleep(60);
            gotoxy(15,14);
            printf("          @@      @@      @@    @@@@      @@    @@        @@@@    @@      @@                  ");Sleep(60);
            gotoxy(15,15);
            printf("        @@@@@@  @@@@@@  @@@@@@    @@@@@@@@    @@@@@@        @@@@@@      @@@@@I                ");Sleep(60);
            gotoxy(15,18);

            Color(5,15);
            printf("                             REALISE PAR TERRAS Juba && SAHI Kenza");
            gotoxy(15,20);
            Color(1,15);
            printf("                                     Appuyez sur n'importe quelle touche pour quitter  ");
            getch();
      }
/*******************************************************************************************************************************************************************/
