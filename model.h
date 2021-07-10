#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED
#define TAILLE_MAX 1025
/*********************************************************************************************************************************************************/
/*                                                         Declaration des structures                                                                    */
/*********************************************************************************************************************************************************/
/*la structure de l'entete*/
typedef struct
{
    int tete;
    int queu;
    int pos_libre;
    int nb_effacements;
    int nbbloc;
    int nbenreg;
    int nblectures;
    int nbecritures;

}ENTETE;
/*la structure de la date*/
typedef struct date
{
    int jour;
    int mois;
    int annee;
}date;
/*la structure  d'un enseignant*/
typedef struct enseignant
{
    int matricule;
    char nom[100];
    char prenom[100];
    date date_naissance;
    char wilaya_naissance[100];
    char sexe[100];
    char groupe_sanguin[10];
    char grade[100];
    char region[100];
    char diplome[100];
    char specialite[100];
    char etablissement_universitaire[100];
    date date_recrutement;

}ensiegnant;

/*la structure Bloc*/
typedef struct
{
    char chaine[TAILLE_MAX];
    int suivant;
    int numero;
}BLOC;
/*********************************************************************************************************************************************************/
/*                                                         les entetes des fonctions utilisées                                                           */
/*********************************************************************************************************************************************************/
/*la machine abstraite*/
FILE *ouvrir(char mode);
void  allocbloc(FILE *f,int i,BLOC *B);
int entete_f(FILE *f,int i);
void aff_entete(FILE *f,int i,int j);
void liredir(FILE *f,int i,BLOC *B);
void ecriredir(FILE *f,int i,BLOC *B);
void fermer(FILE *f);
/*traitement de generation aléatoire*/
int alea_int(int a, int b);
char  *Aleachaine ( int N );
date alea_date(int annee);
date alea_date_recrutement(int annee);
int recherche_doublon(struct enseignant  TAB[40000],int taille,int j);
/*fonctions generales*/
int calcul_date(char chaine1[256],char chaine2[256]);
void saisie_chaine(char mot[256]);
int saisit_entier(int a );
void turn_to_string(char chaine[], int n, int longueur);
void recuperer_chaine(FILE *f,int n , int *i, int *j, char chaine[],BLOC *B1);
void recuperer_champs(char chaine[1024],int i,char champs[1024]);
void recuperer_date(char chaine[1024],int i,char champs[1024]);
/*traitement sur le fichier*/
int generation_alea( struct enseignant TAB[100000]);
void chargement(FILE *f,struct enseignant TAB[2000],int nbenreg);
void afficher_fichier(FILE *f);
void afficher_supp(FILE *f);
void recherche_fichier(FILE *f,char cle[1024],int nb,int *trouve,int *a,int *b);
int suppression_logique(FILE *f,char cle[1024],int nb);
void insertion(FILE *f);
void afficher_region(FILE *f);
void supprim_specialite(FILE *f);
void requete_interval(FILE *f);
void modification_etablissement(FILE *f);
void insertion_modifie(FILE *f,char enreg[1024]);
void reorganisation(FILE *f);
void afficher_entete(FILE*f);
void afficher_bloc(FILE*f);
/*fonctions d'affichage*/
void Color(int couleurDuTexte,int couleurDeFond);
#endif // MODEL_H_INCLUDED
