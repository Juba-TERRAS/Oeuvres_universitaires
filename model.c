#include "model.h"
#include <windows.h>

/*********************************************************************************************************************************************************/
/*                                                 Implementation de la machine abstraite                                                                */
/*********************************************************************************************************************************************************/
/*Ouverture dun fichier soit en mode nouveau ou ancien*/
FILE *ouvrir(char mode)
{
    system("cls");
    char nom_fichier[256];/*nom du fichier*/
    FILE *f=NULL;/*pointeur vers fichier*/
    ENTETE entete;
do
{/*une boucle do pour forcer l utilisateur a entrer un nom de fichier valide*/
    if((mode=='N') || (mode=='n'))/*on cree un nouveau fichier das le cas ou le mode est egale a N ou n*/
    {
    printf("+=====================================================================================================================+\n");
    Color(05,15);
    printf("|                                          Creation d un nouveau fichier                                             |\n");
    Color(0,15);
    printf("+=====================================================================================================================+\n");
    printf("Donnez le nom de votre nouveau fichier :  ");
    scanf("%s",nom_fichier);
    f=fopen(nom_fichier,"wb+");/*ouverture en mode ecriture binaire*/
        entete.tete=1;/*initialisation des caracteristique de lentete pour un fichier vide*/
        entete.queu=1;
        entete.pos_libre=0;
        entete.nb_effacements=0;
        entete.nbbloc=0;
        entete.nbenreg=0;
        entete.nbecritures=0;
        entete.nblectures=0;
        fwrite(&entete,sizeof(entete),1,f);/*ecriture de l entete au debut du fichier*/
        fclose(f);/*fermeture du fichier*/
        f=fopen(nom_fichier,"r+b");/*reouverture du fichier en mode lecture binaire*/
    }
    if ((mode=='a') || (mode=='A'))/*ouverture d un ancien  fichier das le cas ou le mode est egale a A ou a*/
    {
    system("cls");
    printf("+=====================================================================================================================+\n");
    Color(05,15);
    printf("|                                          Ouverture d un ancien fichier                                              |\n");
    Color(0,15);
    printf("+=====================================================================================================================+\n");
    printf("Donnez le nom de l ancien fichier  :  ");
    scanf("%s",nom_fichier);
    f=fopen(nom_fichier,"rb+");/*ouverture du fichier en mode lecture binaire*/
    }

    if(f==NULL)/*si l ouverture du fichier a echouée*/
    {
        affichage_erreur_ouverture();/*affichage d une erreur*/
    }
}while (f==NULL);/*on sort de la boucle si le nom du fichier est valide sinon on reintroduit un nouveau */
    return f;
}
/*********************************************************************************************************************************************************/
 /*procedure d allocation d un nouveau bloc en memeoire centrale*/
 void  allocbloc(FILE *f,int i,BLOC *B)
{
    BLOC *B1=malloc(sizeof(BLOC));/*allocation en memoire d un nouveau bloc*/
    B1->numero=i;/*on attribue au bloc l'indice i*/
    aff_entete(f,5,entete_f(f,5)+1);/*incrementer nbbloc de l entete*/
    B1->suivant=-1;/*initialisation du suivant du bloc a -1*/
    aff_entete(f,2,B1->numero);/*mettre l adresse du bloc dans la queu*/
    *B=*B1;

}

/*********************************************************************************************************************************************************/
/*Fonction de lecture des donnees de l entete*/
int entete_f(FILE *f,int i)
{
    ENTETE entete;
    rewind(f);
    fread(&entete,sizeof(entete),1,f);/*lecture de l entete dan le buffer*/

    switch(i)/*un switch pour les differentes informations de l entete*/
    {
    case 1:
        return(entete.tete);
        break;
    case 2:
        return(entete.queu);
        break;
    case 3 :
        return(entete.pos_libre);
        break;
    case 4:
        return(entete.nb_effacements);
        break;
    case 5:
        return(entete.nbbloc);
        break;
    case 6:
        return(entete.nbenreg);
        break;
    case 7:
        return(entete.nblectures);
        break;
    case 8 :
        return(entete.nbecritures);
        break;
    default:
        return 0;
        break;
    }

}
/*********************************************************************************************************************************************************/
/*Procedure de modification des donnees de l entete*/
void aff_entete(FILE *f,int i,int j)
{
    ENTETE entete;
    rewind(f);
    fread(&entete,sizeof(entete),1,f);/*lecture de l entete dans le buffer*/
    rewind(f);
    switch(i)/*un switch pour la modification des données de l'entete*/
    {
        case 1:
            entete.tete=j;
            break;
        case 2:
            entete.queu=j;
            break;
        case 3 :
            entete.pos_libre=j;
            break;
        case 4:
            entete.nb_effacements=j;
            break;
        case 5:
            entete.nbbloc=j;
            break;
        case 6:
            entete.nbenreg=j;
            break;
        case 7:
            entete.nblectures=j;
            break;
        case 8:
            entete.nbecritures=j;
            break;
    }
    fwrite(&entete,sizeof(entete),1,f);
}
/*********************************************************************************************************************************************************/
/*Procedure pour lire le iéme bloc du fichier*/
void liredir(FILE *f,int i,BLOC *B)
{
    rewind(f);
    fseek(f,sizeof(ENTETE)+((i-1)*sizeof(BLOC)),SEEK_SET);/*deplacement dans le fichier*/
    fread(B,sizeof(BLOC),1,f);
    aff_entete(f,7,entete_f(f,7)+1);/*incrementer le nombre de lecture de l entete*/
}
/*********************************************************************************************************************************************************/
/*Procedure pour ecrire dans  le iéme bloc du fichier*/
void ecriredir(FILE *f,int i,BLOC *B)
{
  rewind(f);
  fseek(f,sizeof(ENTETE)+((i-1)*sizeof(BLOC)),SEEK_SET);/*deplacement dans le fichier*/
  fwrite(B,sizeof(BLOC),1,f);
  aff_entete(f,8,entete_f(f,8)+1);/*inrementer le nombre d ecriture de l entete*/
}
/*********************************************************************************************************************************************************/
/*Procedure pour la fermeture d'un fichier*/
void fermer(FILE *f)
{
    fclose(f);
}
/*********************************************************************************************************************************************************/
/*                                                 Implementation des fonctions de la generation aleatoire                                               */
/*********************************************************************************************************************************************************/
/*Fonction de generation d'un entier compris entre un interval [a,b]*/
 int alea_int(int a, int b) {
    return (rand()%(b-a+1) + a);
}
/*********************************************************************************************************************************************************/
/*Fonction pour generer aleatoirement une chaine de longeur N*/
  char  *Aleachaine ( int N )
    {
      int k;
      char  * Chaine = malloc(N+1);

      char Chr1[26] = "abcdefghijklmnopqrstuvwxyz";
      char Chr2[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

      for (k=0;k<N; k++)
        switch ( rand() % 2 ){
        case 0 :  *(Chaine+k) = Chr1[rand() % 26] ; break ;
        case 1 :  *(Chaine+k) = Chr2[rand() % 26] ; break ;
        }
      Chaine[k] =  '\0' ;

      return (Chaine);
    }
/*********************************************************************************************************************************************************/
/*Fonction pour generer aleatoirement une date correcte */
date alea_date(int annee) {
    date dat;
    dat.annee = annee;
    dat.mois = alea_int(1, 12);
    if ((dat.mois == 1)||(dat.mois == 3)||(dat.mois == 5)||(dat.mois == 7)||(dat.mois == 8)||(dat.mois == 10)||(dat.mois == 12)) {/*si le mois a 31 jour*/
        dat.jour = alea_int(1, 31);/*generation d'un nombre de jour compris entre 1 et 31 jours*/
    }
    else if ((dat.mois == 4)||(dat.mois == 6)||(dat.mois == 9)||(dat.mois == 11)) {/*si le mois a 30 jours*/
        dat.jour = alea_int(1, 30);/*generation d'un nombre de jours compris entre 1 et 30*/
    } else {/*si le mois est le mois de fevrier*/
        if (dat.annee % 4 == 0) {
            dat.jour = alea_int(1, 29);
        } else {
            dat.jour = alea_int(1, 28);
        }
    }
    return dat;
}
/*********************************************************************************************************************************************************/
/*Fonction pour generer aleatoirement une date de recrutement correcte*/
date alea_date_recrutement(int annee) {
    date dat;
    dat.annee =annee;/*generer une annee comprise entre 1980 et 2019*/
    dat.mois = alea_int(1, 12);/*generer un mois entre 1 et 12*/
    if ((dat.mois == 1)||(dat.mois == 3)||(dat.mois == 5)||(dat.mois == 7)||(dat.mois == 8)||(dat.mois == 10)||(dat.mois == 12)) {
        dat.jour = alea_int(1, 31);
    }
    else if ((dat.mois == 4)||(dat.mois == 6)||(dat.mois == 9)||(dat.mois == 11)) {/*meme traitement que alea_date pour les jours*/
        dat.jour = alea_int(1, 30);
    } else {
        if (dat.annee % 4 == 0) {
            dat.jour = alea_int(1, 29);
        } else {
            dat.jour = alea_int(1, 28);
        }
    }
    return dat;
}
/*********************************************************************************************************************************************************/
/*Fonction de recherche de doublon*/
int recherche_doublon(struct enseignant  TAB[40000],int taille,int j){/*une fonction qui permet de rechercher les doublon*/
    int i=0;
    int inter=0;
while(i<taille && inter==0)/*tant que on est pas arrive a l indice de recherche ou qu on n'a pas trouve un doublon on effectue une recherche sequentielle*/
{
    if(TAB[i].matricule==j){
        inter=1;/*si on trouve un doublon fin de la recherche*/
    }
    i++;
}
return(inter);/*retourn 1 si le matricule recherché existe deja sinon retourn 0*/
}
/*********************************************************************************************************************************************************/
/*                                                 Implementation de fonctions generales                                                                 */
/*********************************************************************************************************************************************************/
int calcul_date(char chaine1[256],char chaine2[256])/*fonction qui permet de claculter le temps passé entre deux dates chaine1 et chaine2*/
{
        int j1,j2,m1,m2,a1,a2;
        int S1,S2,S3,S;
        char jour[2],mois[2],annee[4];
        recuperer_date(chaine1,1,jour);/*recuperation des jour dans la chaine jour dans la premiere date*/
        j1=atoi(jour);/*convertion des journs qui est une chaine de caractere en entier qui sera stocké dans j1*/
        recuperer_date(chaine2,1,jour);/*meme chose pour la dexieme date on recupere les journs*/
        j2=atoi(jour);
        recuperer_date(chaine1,2,mois);/*recuperation des mois*/
        m1=atoi(mois);
        recuperer_date(chaine2,2,mois);
        m2=atoi(mois);
        recuperer_date(chaine1,3,annee);/*recuperation des annees*/
        a1=atoi(annee);
        recuperer_date(chaine2,3,annee);
        a2=atoi(annee);
        S1=j1-j2;/*on soustrait de j1 j2 pour recuperer le nombre de jours*/
        if(S1<0)/*si S1 est negatif  on rejoute 30*/
        {
            S1=S1+30;
        }
        S2=m1-m2;/*on soustrait de m1 m2 pour recuperer le nombre de mois*/
        if(S2<0)/*si S2 est negatif on rajoute 12*/
        {
            S2=S2+12;
        }
        S3=a1-a2;/*on soustrait a a1 a2 pour recuperer les nombre des annees*/
        S=S1+S2*30+S3*365;/*convertion du tous en jours*/

}
/*********************************************************************************************************************************************************/
void saisie_chaine(char mot[256]){/*fonction qui va permetre de remplir une chaine de caractere en saisie*/
char c;
int i=0;
while(c!='\r')
{
    c=getche();
    if((c!='\r')&&(c!='\b'))
    {
        mot[i]=c;
        i++;
    }
    else if(c=='\b')
    {
        if(i!=0)
        {
          mot[i]='\0';
          i--;
        }
    }
    else{
        mot[i]='\0';
        i=0;
    }
}
}
/*********************************************************************************************************************************************************/
int saisit_entier(int a ){/*fonction qui permetre de lire un entier en console*/
scanf("%d",&a);
return a;
}
/*********************************************************************************************************************************************************/
/*Fonction de transformation d'un entier en chaine de caractere*/
void turn_to_string(char chaine[], int n, int longueur)
{

    int i;
    for(i=longueur-1;i>=0;i--)         /*on commence par le poids faible du nombre qui va etre mi a chaine[longueur-1]*/
    {
        chaine[i]=(n%10)+'0';          /*extraction chiffre par chiffre  grace au mod par 10 et ajout du code ascii du zero afin d'obtenir le code ascii correspondant au chiffre obtenu*/
        n=n/10;                        /*on passe au chiffre suivant*/
    }
    chaine[longueur]='\0';             /*fin de la chaine construite*/
}
/*********************************************************************************************************************************************************/
/*Fonction de recuperation d une chaine de caractere*/
void recuperer_chaine(FILE *f,int n , int *i, int *j, char chaine[],BLOC *B1) //
   {
    int l;
    int k=0;
    for(k=0;k<n;k++)                       /*boucle de k itérations correspondant a la longueur de la chaine*/
     {
        if((*j)<=1024)                     /*si le kièmem caractère de la chaine correspondant au j ime car du buffer  est toujour dans le bloc i*/
        {                                  /*le caractère 1024 correspond a la fin de la chaine dans le tableau*/
            chaine[k]=B1->chaine[(*j)];    /*recuperation du caractère dans la position k de la chaine*/
            (*j)++;                        /*incrementation du j pour passer au caractere suivant*/
        }
        else                               /* si on depasse la capcite maximale du bloc*/
        {
            l=B1->suivant;/* on passe au suivant du bloc i dans la liste*/
            liredir(f,l,B1);/*lecture du prochaine bloc*/
            *(i)=l;          /*i passage par variable recevera la nouvelle valeur de l (nouveau Bloc)*/
            chaine[k]=B1->chaine[0];/*recuperation du premier caractère du tableau de carractère correspondant au j ième car de la chaine*/
            (*j)=1;/*positionnement au dexieme caractere du bloc*/
        }
    }
   chaine[k]='\0';                        /*fin de la chaine obtenue*/
}
/*********************************************************************************************************************************************************/
/*Fonction de recuperation d un champs donné de l enregistrement*/
void recuperer_champs(char chaine[1024],int i,char champs[1024])
{
    /*chaine represente enregistrement sous la forme *champs1*champs2*champs3 ....champs12| */
    /*i pour dire le numero du champs de l enregistrment a recuperer*/
    strcpy(champs,"");/*champs pour recuperer le champs souhaite*/
    int j=0,l=0,k=0;/*j sera inialiser a 0 on suppose que le numero du champs est egale a 0*/
    while(j<i)
    {
        champs[l]=chaine[k];/*construction de champs*/
        l++;
        k++;
        if(chaine[k]=='*' || chaine[k]=='|' )/*si on arrive a l un des seperateur */
        {
            j++;/*incrementer le numero de champs */
            if(j<i)/*si j est toujours inferieure au  numero de champs souhaite c est a dire c est pas le bon champs on vide la chaine champs*/
            {
                strcpy(champs,"");
                l=0;
                k++;
            }
        }

    }
    champs[l]='\0';/*fin de construction*/
}
/*********************************************************************************************************************************************************/
/*Fonction pour recuperer les jour,mois et annee du champs date*/
void recuperer_date(char chaine[1024],int i,char champs[1024])
{
    /*chaine est un chaine de caractere sous la forme *jj/mm/annee* */
    strcpy(champs,"");/*meme traitement que recuperer_champs*/
    int j=0,l=0,k=0;
    while(j<i)
    {
        champs[l]=chaine[k];
        l++;
        k++;
        if( chaine[k]=='/' || chaine[k]=='\0' )/*si on arrive a l un des seperateurs*/
        {
            j++;
            if(j<i)
            {
                strcpy(champs,"");
                l=0;
                k++;
            }
        }

    }
    champs[l]='\0';
}
/*********************************************************************************************************************************************************/
/*                                                 1)-   Chargement du fichier                                                                           */
/*********************************************************************************************************************************************************/
/*Fonction de remplissage d un tableau avec les donnees generes aleatoirement et retourne le nombre d enregistrments generes*/
/*Ce tableau servira au remplissage du fichier avec les enregistrement*/
int generation_alea( struct enseignant TAB[100000])/*on definit comme taille maximale 100000 enseignats mais cela peut etre changer*/
{
system("cls");
    printf("+=====================================================================================================================+\n");
    Color(05,15);
    printf("|                           Generation des enregistrements et remplissage du fichier                                  |\n");
    Color(0,15);
    printf("+=====================================================================================================================+\n");
int i=0,j,nbenreg;
/*les differents tableau qui serviront a stocker les donnees de la generations aleatoire*/
char *TAB_WILAYA[]={"Adrar", "Chlef", "Laghouat", "Oum El Bouaghi", "Batna", "Bejaia", "Biskra", "Bechar",
    "Blida", "Bouira", "Tamanrasset", "Tebessa", "Tlemcen", "Tiaret", "Tizi Ouzou", "Alger",
    "Djelfa", "Jijel", "Setif", "Saida", "Skikda", "Sidi Bel Abbes", "Annaba", "Guelma", "Constantine", "Medea",
    "Mostaganem", "M'Sila", "Mascara", "Ouargla", "Oran", "El Bayadh", "Illizi", "Bordj Bou Arreridj", "Boumerdes",
    "El Tarf", "Tindouf", "Tissemsilt", "El Oued", "Khenchela", "Souk Ahras", "Tipaza", "Mila", "Ain Defla", "Naama",
    "Ain Temouchent", "Ghardaia", "Relizane", };
char *TAB_SEXE[]= {"Masculin", "Feminin"};
char *TAB_GROUPE[] = {"O+","A+","B+","O-","AB+","A-","B-","AB-"};
char *TAB_GRADE[]= {"Professeur(e)", "Maitre de conferences Rang A", "Maitre de conferences Rang B", "Maitre assistant(e) Rang A", "Maitre assistant(e) Rang B", "Assistant(e)"};
char *TAB_SPECIALITE[]={"Droit", "Sciences Politiques", "Lettres et langues etrangeres" ,"Lettres et langue arabe", "Informatique", "Mathematiques", "Chimie", "Physique", "Medecine", "Pharmacologie", "Biologie", "Sciences Commerciales", "Sciences de Gestion", "Sciences Economiques", "Electronique", "electrotechnique", "Genie Civil", "Genie des procedes", "Architecture", "Genie mecanique", "hydraulique", "Sciences Islamiques", "Sciences Humaines", "Sociologie", "Agronomie"};
char *TAB_DIPLOME[]= {"Doctorat d'Etat", "Doctorat en sciences", "PhD", "HDR", "Magistere"};
char *TAB_REGION[]= {"West", "Centre", "Est"};
char *TAB_ETABLISSEMENT[]= {  "Universite de Bechar Mohamed Tahri", "Universite  de Mascara Mustapha Stambouli", "Universite de Saida Tahar Moulay",
      "Universite  de Tlemcen Abou Bekr Belkaid", "Universite  d'Adrar Ahmed Draya", "Universite  de Tiaret Ibn Khaldoun",
      "Universite  Sidi Bel Abbes Djillali Liabes", "Universite de Mostaganem Abdelhamid Ibn Badis", "Universite d'Oran1 Ahmed Ben Bella",
      "Universite Mohamed Boudiaf  des sciences et de la technologie", "Universite  d'Oran 2 Mohamed Ben Ahmed",
      "Centre Universitaire de Tissemsilt Ahmed ben yahia el-wancharissi", "Centre Universitaire  de Ain Temouchent Belhadj Bouchaib",
      "Centre universitaire de Relizane Ahmed Zabana", "Centre universitaire   de Naama Ahmed Salhi",
      "Centre universitaire   d'El Bayadh Nour Bachir", "Centre universitaire de Tindouf  Ali Kafi",
      "Centre universitaire de Maghnia","Annexe de Sougheur ","Annexe de Ksar Chellala",
      "Ecole Nationale Polytechnique d'Oran Maurice Audin","Ecole  Superieure d'Informatique 08 Mai 1945",
      "Ecole Superieure des Sciences Appliquees de Tlemcen","Ecole Superieure d'Economie d'Oran ex EPSECG Oran",
      "Ecole Superieure de Management de Tlemcen ","Ecole Superieure en Genie Electrique et Energetique d'Oran",
      "Ecole Superieure Agronomique de Mostaganem ", "Ecole Superieure des sciences Biologiques  d' Oran",
      "Ecole Normale Superieure de Mostaganem","Ecole Normale Superieure d'Oran", "Ecole normale superieure de Bechar",
      "Universite  de Bouira Akli Mohand Oulhadj", "Universite  de Djelfa Ziane Achour", "Universite de Ghardaia",
      "Universite  de Khemis Miliana Djilali Bounaama", "Universite des sciences et de la technologie d'Alger Houari Boumediene",
      "Universite  Medea Yahia Fares", "Universite de Bejaia Abderrahmane Mira", "Universite  de Chlef Hassiba Benbouali",
      "Universite  de Boumerdes M'hamed Bougara", "Universite de Tizi Ouzou Mouloud Maameri", "Universite de Laghouat Amar Telidji",
      "Universite  Blida 1 Saad Dahlab", "Universite de Blida 2 Lounici Ali", "Universite d'Alger 1 Benyoucef Benkhedda",
      "Universite d'Alger 2 Abou el Kacem Saadallah", "Universite d'Alger 3 Brahim Soltane Chaibout", "Universite de la Formation Continue",
      "Centre universitaire  de Tamanrasset Amine Elokkal El Hadj Moussa", "Centre universitaire  de Tipaza Abdallah Morsli",
      "Centre Universitaire d'Illizi Cheikh Amoud ben Mokhtar", "Centre universitaire Aflou", "Ecole Superieure des Sciences appliquees d'Alger ",
      "Ecole Superieure des Sciences de l'Aliment et des Industries Agroalimentaires d'Alger",
      "Ecole Nationale Superieure des sciences politiques", "Ecole nationale superieure de journalisme et des sciences de l'information",
      "Ecole Nationale Superieure de Technologie", "Ecole nationale superieure de management", "Ecole nationale superieure des sciences de la mer et de l'amenagement du littoral",
      "Ecole Superieure de Commerce Mouloud Kacem Nait Belkacem", "Ecole superieure en statistique et en economie appliquee",
      "Ecole nationale superieure d'informatique ( Alger )", "Ecole des hautes etudes commerciales",
      "Ecole nationale superieure agronomique Khalef Abdellah alias Kasdi Merbah",
      "Ecole Polytechnique d'architecture et d'Urbanisme Hocine Ait Ahmed", "Ecole nationale superieure veterinaire Rabie Bouchama",
      "Ecole nationale superieure des travaux publics Francis Jeanson", "Ecole nationale superieure d'hydraulique Arbaoui Abdellah",
      "Ecole Nationale Polytechnique", "Ecole normale superieure de Laghouat Taleb Abderrahmane ", "Ecole normale superieure de Kouba Mohamed Bachir El Ibrahimi",
      "Ecole normale superieure de Bouzareah ", "Ecole preparatoire en sciences economiques commerciales et sciences de gestion",
      "Universite  de Jijel Mohammed Seddik Ben yahia", "Universite de Tebessa Larbi Tebessi",
      "Universite de Bordj Bou Arreridj Mohamed Bachir El Ibrahimi", "Universite d'El Tarf Chadli Bendjedid",
      "Universite  de Khenchela Abbas Laghrour", "Universite  de Oum El Bouaghi Larbi Ben M'hidi",
      "Universite d'El Oued Hamma Lakhdar-", "Universite de Souk Ahras Mohammed-Cherif Messaadia",
      "Universite  de Annaba Badji Mokhtar", "Universite  du 20 Aout 1955 de Skikda", "Universite  8 Mai 1945 de Guelma",
      "Universite de Batna 1 Hadj Lakhder", "Universite  de Biskra Mohamed Khider", "Universite  de M'sila Mohamed Boudiaf",
      "Universite  de Ouargla Kasdi Merbah", "Universite des sciences islamiques Emir Abdelkader de Constantine",
      "Universite  de Setif 1 Ferhat Abbas", "Universite  de Setif 2 Mohamed Lamine Debaghine",
      "Universite  de Constantine 2 Abdelhamid Mehri ", "Universite  de Constantine 1 Freres Mentouri",
      "Universite de Constantine 3 Salah Boubnider", "Universite de Batna 2 Mustapha Ben Boulaid",
      "Centre Universitaire de Mila Abdelhafid Boussouf", "Centre Universitaire de Barika Si El Haoues",
      "Ecole nationale superieure des mines et de la metallurgie Amar Laskri", "Ecole Nationale Polytechnique de Constantine Malek Bennabi",
      "Ecole Nationale Superieure de Biotechnologie de Constantine Tewfik Khaznadar", "Ecole Superieure des Sciences de Gestion de Annaba", "Ecole Superieure des Technologies Industrielles de Annaba",
      "Ecole Superieure de Comptabilite et de Finance de Constantine ", "Ecole normale superieure de Constantine Assia Djebar",
      "Ecole normale superieure d'enseignement technologique de Skikda", "Ecole normale superieure de setif Messaoud Zeghar"};
       Color(0,15);
       printf("Donnez le nombre d enrregistrmeent a generer  :   ");/*introduire le nombre d'enregistrement a generer*/
      scanf("%d",&nbenreg);
      printf("\n+=====================================================================================================================+\n\n");
while(i<nbenreg)/*generation et affections au element du chaque case du tableau*/
{
            j=alea_int(111111,999999);/*pour un matricule generé on verifie si il existe pas dans le tableau d'enregistrements*/
            if(recherche_doublon(TAB,i,j)==0)/*si il n existe pas on linsere*/
            {
            TAB[i].matricule=j;
            j=alea_int(4,30);
            strcpy(TAB[i].nom,Aleachaine(j));
            j=alea_int(4,30);
            strcpy(TAB[i].prenom,Aleachaine(j));
            j=alea_int(0,47);
            strcpy(TAB[i].wilaya_naissance,TAB_WILAYA[j]);
            j=alea_int(0,1);
            strcpy(TAB[i].sexe,TAB_SEXE[j]);
            j=alea_int(0,7);
            strcpy(TAB[i].groupe_sanguin,TAB_GROUPE[j]);
            j=alea_int(0,5);
            strcpy(TAB[i].grade,TAB_GRADE[j]);
            strcpy(TAB[i].specialite,TAB_SPECIALITE[j]);
            j=alea_int(0,4);
            strcpy(TAB[i].diplome,TAB_DIPLOME[j]);
            j=alea_int(0,2);
            strcpy(TAB[i].region,TAB_REGION[j]);
            j=alea_int(0,105);
            strcpy(TAB[i].etablissement_universitaire,TAB_ETABLISSEMENT[j]);
            j=alea_int(1953,1993);
            TAB[i].date_naissance=alea_date(j);/*generation d une date aleatoirement*/
            j=alea_int(1980,2019);
            TAB[i].date_recrutement=alea_date_recrutement(j);/*generation d une date de reccrutement aleatoirement*/
            i++;
            }
}
return(nbenreg);
}
/*********************************************************************************************************************************************************/
/*Fonction de remplissage du fichier avec les N enregistrement*/
void chargement(FILE *f,struct enseignant TAB[2000],int nbenreg)
{
    aff_entete(f,6,nbenreg);/*affecter a lentete le nombre d enregistrements*/
    BLOC B1,B2;/*deux buffers de  type bloc*/
    int i=0,j=0,k=0,l=1,taille;
    int a,b,c;
    char S[1024]="",ch[1024]="",jour[2]="",mois[2]="",annee[4]="";
    allocbloc(f,1,&B1);/*allocation du premier bloc en memoire centrale*/
    for(i=0;i<nbenreg;i++)
    {
        if(i%300==0){
            loading();/*fonction d affichage d une loading*/
        }
        k=0;
        strcpy(S,"N");/*Construction de S avec les differents champs de notre enregistrement en commancant par le caractere d effacement*/
        turn_to_string(ch,TAB[i].matricule,6);/*convertion de l imatriculation qui est de type entier en chaine de caractere qui sera stocké dans ch*/
        strcat(S,"*");/*on choisis comme separateur entre les champs le symbol '*' */
        strcat(S,ch);/*ajout du matricule a S*/
        strcat(S,"*");
        strcat(S,TAB[i].nom);/*ajout du nom et on continue jusqu a construire S avec tous les champs de l enregistrement separer avec des '*' */
        strcat(S,"*");
        strcat(S,TAB[i].prenom);
        strcat(S,"*");
        a=TAB[i].date_naissance.jour;/*recuperation du jour,mois,annee dans a,b,c*/
        b=TAB[i].date_naissance.mois;
        c=TAB[i].date_naissance.annee;
        turn_to_string(jour,a,2);/*convertion de jour de type entier en chaine de caractere */
        strcat(S,jour);
        strcat(S,"/");/*on choisis comme sperateurs entre jour,mois,et annnee le symbole '/' */
        turn_to_string(mois,b,2);/*meme chose pour mois*/
        strcat(S,mois);
        strcat(S,"/");
        turn_to_string(annee,c,4);/*meme chose pour annee*/
        strcat(S,annee);
        strcat(S,"*");
        strcat(S,TAB[i].wilaya_naissance);
        strcat(S,"*");
        strcat(S,TAB[i].sexe);
        strcat(S,"*");
        strcat(S,TAB[i].groupe_sanguin);
        strcat(S,"*");
        strcat(S,TAB[i].grade);
        strcat(S,"*");
        strcat(S,TAB[i].region);
        strcat(S,"*");
        strcat(S,TAB[i].diplome);
        strcat(S,"*");
        strcat(S,TAB[i].specialite);
        strcat(S,"*");
        strcat(S,TAB[i].etablissement_universitaire);
        strcat(S,"*");
        a=TAB[i].date_recrutement.jour;/*recuperation du jour,mois,annee de recrutement dans a,b,c*/
        b=TAB[i].date_recrutement.mois;
        c=TAB[i].date_recrutement.annee;
        turn_to_string(jour,a,2);/*convertion de jour de type entier en chaine de caractere */
        strcat(S,jour);/*ajouter jour a S meme chose pour mois et annee, sauf quon separe entre jour mois et annee avec des '/' */
        strcat(S,"/");
        turn_to_string(mois,b,2);
        strcat(S,mois);
        strcat(S,"/");
        turn_to_string(annee,c,4);
        strcat(S,annee);
        strcat(S,"|");/*on marque la fin de l enregistrement par le symbol '|' dont on va s en servir comme separateur entre les enregistrements*/
        taille=strlen(S);/*on recupere la taille de l enregistrement dans taille*/
        strcpy(ch,"");/*vider la chaine ch*/
        turn_to_string(ch,taille,3);/*convertir la taille de type entier en chaine de caractere */
        strcat(ch,"*");
        strcat(ch,S);/*concatener ch avec s pour obtenir S sous la forme 'taille*effacé*matricule*enregistrement|*/
/****************************************************************/
        while(k<strlen(ch))/*la prochaine etape est d ecrire la chaine construite dans le fichier*/
        {
            if(j<TAILLE_MAX)/*tant que j est inferieure a la taille maximale d un bloc*/
            {
                B1.chaine[j]=ch[k];/*on remplit le buffer avec les caracteres de la chaine construite*/
                B1.chaine[j+1]='\0';/*on marque la fin de la chaine avec un marqueur de fin de chaine*/
                aff_entete(f,3,j);/*on affecte a l indice libre de l entete la valeur de j*/
                j++;/*incrementer j pour avancer dans le bloc*/
                k++;/*incrementer k pour avancer dans la chaine construite*/
            }
            else/*dans le cas ou j a depasser la taille du bloc*/
            {
                j=0;/*on remet j a 0*/
                allocbloc(f,l+1,&B2);/*on alloue un nouveau bloc B2 avec lindice l+1*/
                B1.suivant=l+1;/*on affecte au champs suivant de B1 l indice du bloc B2*/
                ecriredir(f,l,&B1);/*ecrire le bloc courant B1 dans le fichier*/
                B1=B2;/*ecraser l ancien buffer B1 par B2*/
                strcpy(B1.chaine,"");/*vider le champs chaine de B1*/
                l++;/*incrementer l*/
             }
        }

    }
/*on ecrit les derniers enregistrement qui restent dans le buffer B1 pour eviter de les perdre*/
                B1.chaine[j+1]='\0';
                B1.suivant=-1;
                ecriredir(f,l,&B1);
                fermer(f);
        gotoxy(1,12);
        Color(0,15);
        printf("+=====================================================================================================================+\n");
        Color(2,15);
        printf("|                                          Operation effectue avec succes                                             |\n");
        Color(0,15);
        printf("+=====================================================================================================================+\n\n");
        Color(1,15);
        printf("                               Appuyez sur n'import quelle touche pour continuer   ");
        getche();
}

/*********************************************************************************************************************************************************/
/*                                                 2)-   Affichage du fichier                                                                            */
/*********************************************************************************************************************************************************/
/*Fonction d'affichage du contenu du fichier(enregistrement par enregistrement en montrant tous ses champs*/
void afficher_fichier(FILE *f)
{
    system("cls");
    char champs[1024]="";
    int i=entete_f(f,1);                /*positionnement a la tete du fichier*/
    int j=0,l=0;                        /*positionnement au premier caractère*/
    BLOC B1;                            /*buffer*/
    char *ch1=malloc(sizeof(char)*3);   /*recuperation de taille*/
    char *ch2=malloc(sizeof(char));     /*recuperation de marqueur dans ch2*/
    char *ch3=malloc(sizeof(char)*6);   /*matricule dans ch3*/
    char *ch4=malloc(sizeof(char)*1024);/*enregistrement dans ch4*/
    char *marque=malloc(sizeof(char));  /*separateur dans marque*/
    char *inter=malloc(sizeof(char)*1024);
    char *jour=malloc(sizeof(char)*2);  /*jours pour ecuperation des jours*/
    char *mois=malloc(sizeof(char)*2);  /*mois pour ecuperation des mois*/
    char *annee=malloc(sizeof(char)*4); /*annee pour ecuperation des annee*/
    liredir(f,i,&B1);    /*lecture du premier bloc dans B1*/
  if(entete_f(f,6)!=0)/*dans le cas ou le fichier n'est pas vide c est a dire il y a des enregistrement a afficher*/
  {
    Color(0,15);
    printf("+=====================================================================================================================+\n");
    Color(05,15);
    printf("|                                          Affichage du contenu du fichier                                           |\n");
    Color(0,15);
    printf("+=====================================================================================================================+\n");
    for(l=0;l<=entete_f(f,6);l++)/*boucle pour parcourir tous les enregistrements*/
    {
        recuperer_chaine(f,3,&i,&j,ch1,&B1); /*recuperations de taille,matricule,effacement et enregistrement*/
        recuperer_chaine(f,1,&i,&j,marque,&B1);
        recuperer_chaine(f,1,&i,&j,ch2,&B1);
        recuperer_chaine(f,1,&i,&j,marque,&B1);
        recuperer_chaine(f,6,&i,&j,ch3,&B1);
        recuperer_chaine(f,1,&i,&j,marque,&B1);
        recuperer_chaine(f,atoi(ch1)-9,&i,&j,ch4,&B1);
        if(strcmp(ch2,"N")==0)/*si le caractere d'effacement est a N c est a dire l enregistrement est non supprimé*/
        {
            /*recuperation des champs de l'enregistrement 1 a 1 et affichage*/
            printf("+=====================================================================================================================+\n");
            recuperer_champs(ch4,1,inter);/*grace a la fonction recupere champs on specifie le numero du champs de l enregistrement et on le recupere
            dans inter*/
            printf("|");
            Color(3,15);
            printf("        %s",inter);
            gotoxy(35,wherey());
            recuperer_champs(ch4,2,inter);
            Color(0,15);
            printf("|");
            Color(3,15);
            printf("        %s",inter);
            gotoxy(70,wherey());
            Color(0,15);
            printf("|");
            Color(3,15);
            printf("                   %s",ch3);
            gotoxy(119,wherey());
            Color(0,15);
            printf("|\n");
            printf("+=====================================================================================================================+\n");
            printf("|");
            Color(10,15);
            printf("          Informations personnelles ");
            gotoxy(55,wherey());
            Color(0,15);
            printf("|");
            printf("       ");
            Color(10,15);
            printf("           Parcours professionel ");
            gotoxy(119,wherey());
            Color(0,15);
            printf("|\n");
            printf("+---------------------------------------------------------------------------------------------------------------------+\n");
            recuperer_champs(ch4,3,inter);
            printf("|  Date de naissance : %s",inter);
            gotoxy(55,wherey());
            printf("|       ");
            recuperer_champs(ch4,7,inter);
            printf("Grade : %s",inter);
            gotoxy(119,wherey());
            printf("|\n");
            recuperer_champs(ch4,4,inter);
            printf("|  Wilaya : %s",inter);
            gotoxy(55,wherey());
            printf("|       ");
            recuperer_champs(ch4,9,inter);
            printf("Diplome : %s",inter);
            gotoxy(119,wherey());
            printf("|\n");
            recuperer_champs(ch4,5,inter);
            printf("|  Sexe : %s",inter);
            gotoxy(55,wherey());
            printf("|       ");
            recuperer_champs(ch4,10,inter);
            printf("Specialite : %s",inter);
            gotoxy(119,wherey());
            printf("|\n");
            recuperer_champs(ch4,6,inter);
            printf("|  Groupe_Sanguin : %s",inter);
            gotoxy(55,wherey());
            printf("|");
            recuperer_champs(ch4,11,inter);
            printf(" %s",inter);
            gotoxy(119,wherey());
            printf("|\n");
            printf("|",inter);
            gotoxy(55,wherey());
            printf("|       ");
            recuperer_champs(ch4,12,inter);
            printf("Date de recuretment : %s",inter);
            gotoxy(119,wherey());
            printf("|\n");
            printf("|",inter);
            gotoxy(55,wherey());
            printf("|       ");
            recuperer_champs(ch4,8,inter);
            printf("Region : %s",inter);
            gotoxy(119,wherey());
            printf("|\n");
            printf("+---------------------------------------------------------------------------------------------------------------------+\n\n");
        }
    }
        Color(1,15);
        printf("                               Appuyez sur n'import quelle touche pour continuer   ");
        getche();
  }
  else/*dans le cas ou le fichier est vide on affiche un message d'erreur*/
  {
        affichage_erreur_vide();
  }
}
/*********************************************************************************************************************************************************/
/*                                  3)-   Affichage des enregistrements supprimes logiquement dans un ficier                                             */
/*********************************************************************************************************************************************************/
/*Fonction d'affichage du contenu du fichier(enregistrement par enregistrement en montrant tous ses champs*/
void afficher_supp(FILE *f)
{
    system("cls");
    char champs[1024]="";
    int i=entete_f(f,1);                  /*positionnement a la tete du fichier*/
    int j=0,l=0,aucun=0;                  /*positionnement au premier caractère*/
    BLOC B1;
    char *ch1=malloc(sizeof(char)*3);
    char *ch2=malloc(sizeof(char));
    char *ch3=malloc(sizeof(char)*6);
    char *ch4=malloc(sizeof(char)*1015);
    char *marque=malloc(sizeof(char));
    char *inter=malloc(sizeof(char)*1024);
    char *jour=malloc(sizeof(char)*2);
    char *mois=malloc(sizeof(char)*2);
    char *annee=malloc(sizeof(char)*4);
    liredir(f,i,&B1);    /*lecture du premier bloc*/
  if(entete_f(f,6)!=0)
  {
    Color(0,15);
    printf("+=====================================================================================================================+\n");
    Color(05,15);
    printf("|                               Affichage des enregistrements supprimes logiquement                                   |\n");
    Color(0,15);
    printf("+=====================================================================================================================+\n");
    for(l=0;l<=entete_f(f,6);l++)
    {
        recuperer_chaine(f,3,&i,&j,ch1,&B1); // on commence a recuperer les enregistrememnt un a un
        recuperer_chaine(f,1,&i,&j,marque,&B1);
        recuperer_chaine(f,1,&i,&j,ch2,&B1);
        recuperer_chaine(f,1,&i,&j,marque,&B1);
        recuperer_chaine(f,6,&i,&j,ch3,&B1);
        recuperer_chaine(f,1,&i,&j,marque,&B1);
        recuperer_chaine(f,atoi(ch1)-9,&i,&j,ch4,&B1);
        if(strcmp(ch2,"O")==0)/*meme traitement que afficher_fichier sauf qu on verifie maintenant que l'enregistrement a bien été supprimé logiquement*/
        {/*si c est le cas on affiche l'enregistrement avec tous ses champs*/
            aucun=1;
            Color(0,15);
            printf("+=====================================================================================================================+\n");
            recuperer_champs(ch4,1,inter);
            printf("|");
            Color(3,15);
            printf("        %s",inter);
            gotoxy(35,wherey());
            recuperer_champs(ch4,2,inter);
            Color(0,15);
            printf("|");
            Color(3,15);
            printf("        %s",inter);
            gotoxy(70,wherey());
            Color(0,15);
            printf("|");
            Color(3,15);
            printf("                   %s",ch3);
            gotoxy(119,wherey());
            Color(0,15);
            printf("|\n");
            printf("+=====================================================================================================================+\n");
            printf("|");
            Color(10,15);
            printf("          Informations personnelles ");
            gotoxy(55,wherey());
            Color(0,15);
            printf("|");
            printf("       ");
            Color(10,15);
            printf("           Parcours professionel ");
            gotoxy(119,wherey());
            Color(0,15);
            printf("|\n");
            printf("+---------------------------------------------------------------------------------------------------------------------+\n");
            recuperer_champs(ch4,3,inter);
            printf("|  Date de naissance : %s",inter);
            gotoxy(55,wherey());
            printf("|       ");
            recuperer_champs(ch4,7,inter);
            printf("Grade : %s",inter);
            gotoxy(119,wherey());
            printf("|\n");
            recuperer_champs(ch4,4,inter);
            printf("|  Wilaya : %s",inter);
            gotoxy(55,wherey());
            printf("|       ");
            recuperer_champs(ch4,9,inter);
            printf("Diplome : %s",inter);
            gotoxy(119,wherey());
            printf("|\n");
            recuperer_champs(ch4,5,inter);
            printf("|  Sexe : %s",inter);
            gotoxy(55,wherey());
            printf("|       ");
            recuperer_champs(ch4,10,inter);
            printf("Specialite : %s",inter);
            gotoxy(119,wherey());
            printf("|\n");
            recuperer_champs(ch4,6,inter);
            printf("|  Groupe_Sanguin : %s",inter);
            gotoxy(55,wherey());
            printf("|");
            recuperer_champs(ch4,11,inter);
            printf(" %s",inter);
            gotoxy(119,wherey());
            printf("|\n");
            printf("|",inter);
            gotoxy(55,wherey());
            printf("|       ");
            recuperer_champs(ch4,12,inter);
            printf("Date de recuretment : %s",inter);
            gotoxy(119,wherey());
            printf("|\n");
            printf("|",inter);
            gotoxy(55,wherey());
            printf("|       ");
            recuperer_champs(ch4,8,inter);
            printf("Region : %s",inter);
            gotoxy(119,wherey());
            printf("|\n");
            printf("+---------------------------------------------------------------------------------------------------------------------+\n\n");
            Color(1,15);

        }
    }
    if(aucun==1){/*si il existe un enregistrement supprimé logiquement*/
     printf("                                    Appuyez sur n'import quelle touche pour continuer   ");
     char c=getche();
    }
  }
  if(aucun==0){/*si aucun enregistrement n'a ete supprime logiquement on affiche un message d'erreur*/
    affichage_erreur_aucun_enreg();
  }
}

/*********************************************************************************************************************************************************/
/*                                                 La recherche dans un fichier par rapport a une clé                                                    */
/*********************************************************************************************************************************************************/
/*Fonction de recherche dun enregistrement donnee selon une cle bien precise en precisant le numero du champs de l enregistrement*/
void recherche_fichier(FILE *f,char cle[1024],int nb,int *trouve,int *a,int *b)
{/*les parametres la cle a rechercher,le nb represente le numero du critere de recherche si il est egale a 0 la recherche se fera selon la clee
    si il est superieur a 0 la recherche se fera selon le numro du chmaps de l enregistrement par exemple si nb==1 la recherche se fera selon le nom,
    si nb==10 la recherche se fera selon la specialite etc....*/
 /*trouve pour savoir si on a trouve ceque nous somme entrain de rechercher ,a pour le numro de bloc,b pour l indice de debut de l enregistrement a l'interieur
 du bloc*/
    int i=entete_f(f,1); /*recuperer l indice du premier bloc*/
    int j=0,l=0;
    BLOC B1;
    char *ch1=malloc(sizeof(char)*3);      /*ch1 pour recuperer la taille de l'enregistrement*/
    char *ch2=malloc(sizeof(char));        /*ch2 pour recuperer l'indice d effacement*/
    char *marque=malloc(sizeof(char));     /*marque pour recuperer les seperateurs*/
    char *ch3=malloc(sizeof(char)*6);      /*ch3 pour recuperer l'imatriculation*/
    char *ch4=malloc(sizeof(char)*1024);   /*ch4 pour recuperer tous l enregistrement*/
    char *champs=malloc(sizeof(char)*1024);/*pour recuperer les champs de l'enregistrement*/
    liredir(f,i,&B1);    /*Lecture du premier Bloc*/
if(entete_f(f,6)!=0)/*si le fichier n est pas vide */
{
while(l<=entete_f(f,6) && (*trouve)==0)/*tant que on est pas arriver a la fin c est a dire on pas depasser le nombre d'enregistrement et quon on pas retrouve
        la clé introduite*/
{
        recuperer_chaine(f,3,&i,&j,ch1,&B1); /*recuperation de taille*/
        recuperer_chaine(f,1,&i,&j,marque,&B1);/*recuperation du seperateur*/
        recuperer_chaine(f,1,&i,&j,ch2,&B1);/*recuperation de effacement*/
        recuperer_chaine(f,1,&i,&j,marque,&B1);
        recuperer_chaine(f,6,&i,&j,ch3,&B1);/*recuperation de matricule*/
        recuperer_chaine(f,1,&i,&j,marque,&B1);
        recuperer_chaine(f,atoi(ch1)-9,&i,&j,ch4,&B1);/*recuperation de tous l enregistrement*/
/****************************************/
        if(nb==0 && strcmp(ch2,"N")==0)/*si le numero de critere de recherche est egale a 0 c est a dire recherche par matricule*/
        {
            if(strcmp(ch3,cle)==0)/*on compare ch3 qui contient le matricule avec la clé introduite si elles sont egaux trouve recoit 1 */
            {
                (*trouve)=1;
                (j)=(j)-(atoi(ch1)+4);/*j doit etre positionner au debut la chaine taille*efface*matricule*enregistremnt| c est a dire au niveau de taille*/
            if(j<0)/*si la valeur de j devient negative on decremente i le nombre de bloc et on ajoute a j la taille du bloc*/
            {
               (i)--;
               (j)=1025+(j);
            }
            }
        }
/****************************************/
        if((nb>0) && (strcmp(ch2,"N")==0))/*si le numero de critere de recherche est different de 0*/
        {
            recuperer_champs(ch4,nb,champs);/*on recupere le champs souhaité dans la chaine de caractere champs*/
            if(strcmp(champs,cle)==0)/*meme traitement pour le cas du matricule*/
            {
                (*trouve)=1;
                (j)=(j)-(atoi(ch1)+4);
            if(j<0)
            {
               (i)--;
               (j)=1024+(j);
            }
            }

        }
l++;/*incrementer  le nombre d'enregistrements*/
}
*a=i;/*passage par variable de lindice du bloc ou se trouvait la clé*/
*b=j;/*passage par variable de lindice du ou debutait  la chaine taille*efface*matricule*enregistremnt| */
}
}
/*********************************************************************************************************************************************************/
/*                                         5)-  Suppression logique d'un enseignant donné pas sa clé                                                  */
/*********************************************************************************************************************************************************/
/*Fonction de suppression logique d un enregistrement en precisant la clé ainsi que le numero du champs associe a lenregistrement*/
int suppression_logique(FILE *f,char cle[1024],int nb)
{
    int i=1,j=0,trouv=0;
    BLOC    B1;
    char *ch1=malloc(sizeof(char)*3);
    char *marque=malloc(sizeof(char));
    recherche_fichier(f,cle,nb,&trouv,&i,&j); /* recherche de la cle dans le fichier*/
    if(trouv==1)                                /* si la cle a ete trouvee*/
    {
        liredir(f,i,&B1);   /* lecture du bloc dans lequel on a trouvé la clé*/
        recuperer_chaine(f,3,&i,&j,ch1,&B1); /* recuperation de la chaine correpondant a la taille de la clé*/
        recuperer_chaine(f,1,&i,&j,marque,&B1);/* recuperation de la chaine correpondant au seperateur de*/
        B1.chaine[j]='O';/*mettre a jour l effacement a 'O'*/
        ecriredir(f,i,&B1);/*reecrire le bloc dans le fichier afin d ecraser l ancien bloc et d effectuer la mise a jour*/
        aff_entete(f,4,entete_f(f,4)+atoi(ch1)+11); /* mise az jour du nombre de caractère supprimes*/
        return(1);
    }
    else/*dans le cas ou la clé n'existe pas on affiche un message d'erreur*/
    {
        affichage_erreur_cle_inexistante();
        return(0);
    }
}
/*********************************************************************************************************************************************************/
/*                                         4)-  Insertion d un nouveau enregistrement  dans le fichier                                                   */
/*********************************************************************************************************************************************************/
void insertion(FILE *f)
{
    system("cls");
    BLOC B1,B2;/*deux buffers*/
    struct enseignant Ens;/*Ens est de type enseignant*/
    int i=0,j=0,k=0,l=0,taille,trouve=0,a,b,c;
    char S[1024]="",chaine[256]="";
    char ch[1024]="",jour[2]="",mois[2]="",annee[4]="";
    Color(0,15);
    printf("+=====================================================================================================================+\n");
    Color(05,15);
    printf("|                                            Insertion dans le fichier                                                |\n");
    Color(0,15);
    printf("+=====================================================================================================================+\n");
    Color(0,15);
    printf("Veillez introduire les informations relatives a l enseignant   :  \n\n");
    printf("======================================");
    Color(2,15);
    printf("     Informations personnells    ");
    Color(0,15);
    printf("===============================================\n\n");
    printf("+=====================================================================================================================+\n");
            Color(13,15);
            int y=wherey();
            printf("| Matricule: \n");/*Remplissage de toutes les informations relatives a un enseignant*/
            Color(0,15);
            printf("==============\n          ");
            Ens.matricule=saisit_entier(Ens.matricule);
            turn_to_string(chaine,Ens.matricule,6);
            recherche_fichier(f,chaine,0,&trouve,&i,&j);/*recherche de l'enseignat par matricule*/
if(trouve==0)/*si le matricule de l'enseignat n' existe pas deja on va l inserer*/
{
            Color(13,15);
            gotoxy(40,y);
            printf("| Nom: \n");
            Color(0,15);
            gotoxy(40,y+1);
            printf("===========\n          ");
            gotoxy(40,y+2);
            saisie_chaine(Ens.nom);
            gotoxy(70,y);
            Color(13,15);
            printf("| Prenom: \n");
            Color(0,15);
            gotoxy(70,y+1);
            printf("=========\n          ");
            gotoxy(70,y+2);
            saisie_chaine(Ens.prenom);
            printf("\n");
            printf("+=====================================================================================================================+\n");
            Color(13,15);
            printf("| Date de naissance: \n");
            Color(0,15);
            printf("=========================\n          ");
            Color(2,15);
            printf("Jour : ");
            y=wherey();
            Color(0,15);
            Ens.date_naissance.jour=saisit_entier(Ens.date_naissance.jour);
            gotoxy(40,y);
            Color(2,15);
            printf("Mois :");
            Color(0,15);
            Ens.date_naissance.mois=saisit_entier(Ens.date_naissance.mois);
            gotoxy(70,y);
            Color(2,15);
            printf("Annee :");
            Color(0,15);
            Ens.date_naissance.annee=saisit_entier(Ens.date_naissance.annee);
            printf("\n");
            printf("+=====================================================================================================================+\n");
            Color(13,15);
            y=wherey();
            printf("| Wilaya: \n");
            Color(0,15);
            printf("==========\n          ");
            saisie_chaine(Ens.wilaya_naissance);
            Color(13,15);
            gotoxy(40,y);
            printf("| Sexe: \n");
            Color(0,15);
            gotoxy(40,y+1);
            printf("===========\n          ");
            gotoxy(40,y+2);
            saisie_chaine(Ens.sexe);
            gotoxy(70,y);
            Color(13,15);
            printf("| Groupe_Sanguin: \n");
            Color(0,15);
            gotoxy(70,y+1);
            printf("====================\n          ");
            gotoxy(70,y+2);
            saisie_chaine(Ens.groupe_sanguin);
            printf("\n+=====================================================================================================================+\n");
            printf("\n");
            printf("======================================");
            Color(2,15);
            printf("     Parcours professionel     ");
            Color(0,15);
            printf("===============================================\n\n");
            printf("+=====================================================================================================================+\n");
            Color(13,15);
            y=wherey();
            printf("| Grade: \n");
            Color(0,15);
            printf("==========\n          ");
            saisie_chaine(Ens.grade);
            Color(13,15);
            gotoxy(40,y);
            printf("| Diplome: \n");
            Color(0,15);
            gotoxy(40,y+1);
            printf("===========\n          ");
            gotoxy(40,y+2);
            saisie_chaine(Ens.diplome);
            Color(13,15);
            gotoxy(70,y);
            printf("| Specialite: \n");
            Color(0,15);
            gotoxy(70,y+1);
            printf("==============\n          ");
            gotoxy(70,y+2);
            saisie_chaine(Ens.specialite);
            printf("\n");
            printf("\n+=====================================================================================================================+\n");
            Color(13,15);
            printf("| Date de recrutement: \n");
            Color(0,15);
            printf("=========================\n          ");
            Color(2,15);
            printf("Jour : ");
            y=wherey();
            Color(0,15);
            Ens.date_recrutement.jour=saisit_entier(Ens.date_recrutement.jour);
            gotoxy(40,y);
            Color(2,15);
            printf("Mois :");
            Color(0,15);
            Ens.date_recrutement.mois=saisit_entier(Ens.date_recrutement.mois);
            gotoxy(70,y);
            Color(2,15);
            printf("Annee :");
            Color(0,15);
            Ens.date_recrutement.annee=saisit_entier(Ens.date_recrutement.annee);
            printf("\n");
            printf("+=====================================================================================================================+\n");
            Color(13,15);
            y=wherey();
            printf("| Region: \n");
            Color(0,15);
            printf("==========\n          ");
            saisie_chaine(Ens.region);
            Color(13,15);
            gotoxy(40,y);
            printf("| Etablissement: \n");
            Color(0,15);
            gotoxy(40,y+1);
            printf("==================\n          ");
            gotoxy(40,y+2);
            saisie_chaine(Ens.etablissement_universitaire);
            printf("\n");
            printf("+=====================================================================================================================+\n");
/*debut de la constructions de la chaine de la forme : taille*efface*taille*enregistrement| */
        strcpy(S,"N");
        turn_to_string(ch,Ens.matricule,6);
        strcat(S,"*");
        strcat(S,ch);
        strcat(S,"*");
        strcat(S,Ens.nom);
        strcat(S,"*");
        strcat(S,Ens.prenom);
        strcat(S,"*");
        a=Ens.date_naissance.jour;
        b=Ens.date_naissance.mois;
        c=Ens.date_naissance.annee;
        turn_to_string(jour,a,2);
        strcat(S,jour);
        strcat(S,"/");
        turn_to_string(mois,b,2);
        strcat(S,mois);
        strcat(S,"/");
        turn_to_string(annee,c,4);
        strcat(S,annee);
        strcat(S,"*");
        strcat(S,Ens.wilaya_naissance);
        strcat(S,"*");
        strcat(S,Ens.sexe);
        strcat(S,"*");
        strcat(S,Ens.groupe_sanguin);
        strcat(S,"*");
        strcat(S,Ens.grade);
        strcat(S,"*");
        strcat(S,Ens.region);
        strcat(S,"*");
        strcat(S,Ens.diplome);
        strcat(S,"*");
        strcat(S,Ens.specialite);
        strcat(S,"*");
        strcat(S,Ens.etablissement_universitaire);
        strcat(S,"*");
        a=Ens.date_recrutement.jour;
        b=Ens.date_recrutement.mois;
        c=Ens.date_recrutement.annee;
        turn_to_string(jour,a,2);
        strcat(S,jour);
        strcat(S,"/");
        turn_to_string(mois,b,2);
        strcat(S,mois);
        strcat(S,"/");
        turn_to_string(annee,c,4);
        strcat(S,annee);
        strcat(S,"|");
        taille=strlen(S);
        strcpy(ch,"");
        turn_to_string(ch,taille,3);
        strcat(ch,"*");
        strcat(ch,S);
/*Injection de la chaine dans le fichier*/
        j=entete_f(f,3)+1;/*recuperer l indice de la derniere postion */
        k=0;
        i=entete_f(f,2);/*recuperation de l indice de la queu*/
        liredir(f,i,&B1);/*lecture du bloc de la queu*/
        while(k<strlen(ch))/*traitement d insertion de la chaine comme dans le chargement*/
        {
            if(j<TAILLE_MAX)
            {
                B1.chaine[j]=ch[k];
                B1.chaine[j+1]='\0';
                aff_entete(f,3,j);
                j++;
                k++;
            }
            else
            {
                j=0;
                allocbloc(f,i+1,&B2);
                B1.suivant=i+1;
                ecriredir(f,i,&B1);
                B1=B2;
                strcpy(B1.chaine,"");
                i++;
             }
        }

                B1.chaine[j+1]='\0';
                B1.suivant=-1;
                ecriredir(f,i,&B1);
                aff_entete(f,6,entete_f(f,6)+1);
                fermer(f);
        Color(0,15);
        printf("\n\n+=====================================================================================================================+\n");
        Color(2,15);
        printf("|             --------------             Insertion effectue avec succee          ---------------                      |\n");
        Color(0,15);
        printf("+=====================================================================================================================+\n\n");
        Color(1,15);
        printf("                                      Appuyez sur n import quelle touche pour continuer !!!!!!!!   ");
        getche();
}
else/*si il existe deja  onaffiche un message d'erreur*/
{
    affichage_erreur_existe();
}
}
/*********************************************************************************************************************************************************/
/*                                         6)-  Affichage des enseignants exercant dans une region donnée                                                */
/*********************************************************************************************************************************************************/
/*Fonction d'affichage des enseigants exresant dans une region donnée*/
void afficher_region(FILE *f)
{
    int c=0;
    char cle[256];
    while((c!=3)&&(c!=2)&&(c!=1))/*tant que lutilisateur n a pas introduit 1 ou 2 ou 3 comem choix*/
    {
    system("cls");
    printf("+=====================================================================================================================+\n");
    Color(5,15);
    printf("|                                Affichage des enseignants d'une region donnee                                        |\n");
    Color(0,15);
    printf("+=====================================================================================================================+\n");
    printf("                                      +================================+\n");
    Color(5,15);
    printf("                                      |              Regions           |\n");
    Color(0,15);
    printf("                                      +================================+\n");
    printf("                                      |    1)    Est                   |\n");
    printf("                                      |    2)    West                  |\n");
    printf("                                      |    3)    Centre                |\n");
    printf("                                      +================================+\n");
    printf("+=====================================================================================================================+\n\n");
    printf("Veillez specifier  votre choix en introduisant un chiffre parmi ceux disponibles :  ");/*l utilisateur va choisir entre les trois choix :Est ,West et Centre*/
    scanf("%d",&c);
    switch(c)/*un switch pour le choix de la region vu que le nombre de possibilite est reduit a 3*/
    {
        case 1:
            {strcpy(cle,"Est");}

        break;
        case 2:
            {strcpy(cle,"West");}
        break;
        case 3:
            {strcpy(cle,"Centre");}
        break;
        default:/*dans le cas ou lutilsateur introduit un choix non valide on affiche un message d'erreur*/
            affichage_erreur_switch();
        break;
    }
}
     char champs[1024]="";
    int i=entete_f(f,1); /*positionnement a la tete du fichier*/
    int j=0,l=0,indicateur=0;/*Positionnement au premier enregistrement*/
    BLOC B1;
    char *ch1=malloc(sizeof(char)*3);/*meme chose que les traitement precedents*/
    char *ch2=malloc(sizeof(char));
    char *ch3=malloc(sizeof(char)*6);
    char *ch4=malloc(sizeof(char)*1024);
    char *inter=malloc(sizeof(char)*1024);
    char *marque=malloc(sizeof(char));
    liredir(f,i,&B1);/*lecture du premier bloc*/
  if(entete_f(f,6)!=0)/*si le fichier n est pas vide*/
  {
    system("cls");
    printf("+=====================================================================================================================+\n");
    Color(5,15);
    printf("|                                Affichage des enseignants d'une region donnee                                        |\n");
    Color(0,15);
    printf("+=====================================================================================================================+\n");

    for(l=0;l<=entete_f(f,6);l++)// parcourir le fichier séquentiellement
    {
        recuperer_chaine(f,3,&i,&j,ch1,&B1); /*on recupere la taille dans ch1*/
        recuperer_chaine(f,1,&i,&j,marque,&B1);/*le separateur dans marque*/
        recuperer_chaine(f,1,&i,&j,ch2,&B1);/*l effacement dans ch2*/
        recuperer_chaine(f,1,&i,&j,marque,&B1);
        recuperer_chaine(f,6,&i,&j,ch3,&B1);/*la taille dans ch3*/
        recuperer_chaine(f,1,&i,&j,marque,&B1);
        recuperer_chaine(f,atoi(ch1)-9,&i,&j,ch4,&B1);/*l'enregistrement dans ch4*/
        if((strcmp(ch2,"N")==0))/*si l enregistrement n est pas supprimé logiquement*/
        {
            recuperer_champs(ch4,8,champs);/*recuperer le champs de region a partir de l enregistrement actuel*/
            if(strcmp(champs,cle)==0)/*verifier si champs est egale a la clé chopisie par l'utilisateur*/
            {
            indicateur=1;
            /*si c est le cas on affiche l enregistrement avec tous ces champs*/
            printf("+=====================================================================================================================+\n");
            recuperer_champs(ch4,1,inter);
            printf("|");
            Color(3,15);
            printf("        %s",inter);
            gotoxy(35,wherey());
            recuperer_champs(ch4,2,inter);
            Color(0,15);
            printf("|");
            Color(3,15);
            printf("        %s",inter);
            gotoxy(70,wherey());
            Color(0,15);
            printf("|");
            Color(3,15);
            printf("                   %s",ch3);
            gotoxy(119,wherey());
            Color(0,15);
            printf("|\n");
            printf("+=====================================================================================================================+\n");
            printf("|");
            Color(10,15);
            printf("          Informations personnelles ");
            gotoxy(55,wherey());
            Color(0,15);
            printf("|");
            printf("       ");
            Color(0,15);
            printf("           Parcours professionel ");
            gotoxy(119,wherey());
            Color(0,15);
            printf("|\n");
            printf("+---------------------------------------------------------------------------------------------------------------------+\n");
            recuperer_champs(ch4,3,inter);
            printf("|  Date de naissance : %s",inter);
            gotoxy(55,wherey());
            printf("|       ");
            recuperer_champs(ch4,7,inter);
            printf("Grade : %s",inter);
            gotoxy(119,wherey());
            printf("|\n");
            recuperer_champs(ch4,4,inter);
            printf("|  Wilaya : %s",inter);
            gotoxy(55,wherey());
            printf("|       ");
            recuperer_champs(ch4,9,inter);
            printf("Diplome : %s",inter);
            gotoxy(119,wherey());
            printf("|\n");
            recuperer_champs(ch4,5,inter);
            printf("|  Sexe : %s",inter);
            gotoxy(55,wherey());
            printf("|       ");
            recuperer_champs(ch4,10,inter);
            printf("Specialite : %s",inter);
            gotoxy(119,wherey());
            printf("|\n");
            recuperer_champs(ch4,6,inter);
            printf("|  Groupe_Sanguin : %s",inter);
            gotoxy(55,wherey());
            printf("|");
            recuperer_champs(ch4,11,inter);
            printf(" %s",inter);
            gotoxy(119,wherey());
            printf("|\n");
            printf("|",inter);
            gotoxy(55,wherey());
            printf("|       ");
            recuperer_champs(ch4,12,inter);
            printf("Date de recuretment : %s",inter);
            gotoxy(119,wherey());
            printf("|\n");
            printf("|",inter);
            gotoxy(55,wherey());
            printf("|       ");
            recuperer_champs(ch4,8,inter);
            printf("Region : %s",inter);
            gotoxy(119,wherey());
            printf("|\n");
            printf("+---------------------------------------------------------------------------------------------------------------------+\n\n");
            }

       }
    }
            if(indicateur==1){
            Color(2,15);
            printf("                                  appuyez sur n importe quelle touche pour continuer   ");
            Color(0,15);
            getche();
            }else
            {
            affichage_erreur_trouve();
            }
}
else/*si il est vide on affiche un message d'erreur*/
{
         affichage_erreur_vide();
}
}
/*********************************************************************************************************************************************************/
/*                              7)-  Suppression logique de tous les enseignants exercant dans une specialite donnéé                                     */
/*********************************************************************************************************************************************************/
void supprim_specialite(FILE *f)
{   system("cls");
    printf("+=====================================================================================================================+\n");
    Color(5,15);
    printf("|                                Affichage des enseignants d'une region donnee                                        |\n");
    Color(0,15);
    printf("+=====================================================================================================================+\n");
    printf("                                      +================================+\n");
    Color(5,15);
    printf("                                      |    Exemples de specialites     |\n");
    Color(0,15);
    printf("                                      +================================+\n");
    printf("                                      |    -    Informatique           |\n");
    printf("                                      |    -    Architecture           |\n");
    printf("                                      |    -    Electronique           |\n");
    printf("                                      |    -    Mathematiques          |\n");
    printf("                                      |    -    Chimie                 |\n");
    printf("                                      +================================+\n");
    printf("+=====================================================================================================================+\n\n");
    char cle[1024]="",champs[1024]="";
    printf("Veillez saisir la specialite vise :  ");/*saisir la specialite souhaité*/
    saisie_chaine(cle);
    printf("\n");
    printf("\n                              Veillez pationter pendant le deroulement de l'operation  ");
    int i=entete_f(f,1); /*positionnement a la tete du fichier*/
    int j=0,l=0;
    BLOC B1;
    char *ch1=malloc(sizeof(char)*3);
    char *ch2=malloc(sizeof(char));
    char *marque=malloc(sizeof(char));
    char *ch3=malloc(sizeof(char)*6);
    char *ch4=malloc(sizeof(char)*1024);
    int indicateur=0;
    liredir(f,i,&B1);    /*lecture du premier bloc*/
    printf("\n\n");
if(entete_f(f,6)!=0)/*si le fichier n est pas vide*/
{
       for(l=0;l<=entete_f(f,6);l++)
       {
        recuperer_chaine(f,3,&i,&j,ch1,&B1); /*recuperation de taille,effacé,matrcicule et l'enregistrement*/
        recuperer_chaine(f,1,&i,&j,marque,&B1);
        recuperer_chaine(f,1,&i,&j,ch2,&B1);
        recuperer_chaine(f,1,&i,&j,marque,&B1);
        recuperer_chaine(f,6,&i,&j,ch3,&B1);
        recuperer_chaine(f,1,&i,&j,marque,&B1);
        recuperer_chaine(f,atoi(ch1)-9,&i,&j,ch4,&B1);
        if((strcmp(ch2,"N")==0))/*si l'enregistrement n'a pas été effacé logiquement*/
        {
            recuperer_champs(ch4,10,champs);/*recuperation du champs specialite de l'enregistrement dans la chaine de caractere champs*/

            if(strcmp(champs,cle)==0)/*on compare entre champs et cle saisit par l'utilisateur*/
            {
                indicateur=1;
             suppression_logique(f,ch3,0);/*si ils sont egaux on effectue une suppression logique de l'enregistrement en cours*/
            }

        }
        }
        if(indicateur==1){
        printf("\n\n+=====================================================================================================================+\n");
        Color(2,15);
        printf("|           Operation terminee . Suppression de tous les enseignats exercant dans la specialite choisis effectue      |\n");
        Color(0,15);
        printf("+=====================================================================================================================+\n\n");
        Color(1,15);
        printf("                                        Appuyez sur n import quelle touche pour continuer !!!!!!!!   ");
        getche();
        }
        else/*si aucun enregistrement corresponf a la specialite selectionnée on affiche un message d'erreur*/
        {
            affichage_erreur_trouve();
        }
}
else/*si le fichier est vide on affiche un message d'erreur*/
{
affichage_erreur_vide();
}
}
/*********************************************************************************************************************************************************/
/*                                                          8)-  Lancer des requettes a interval                                                         */
/*********************************************************************************************************************************************************/
void requete_interval(FILE *f)
{
    system("cls");
    int indicateur=0;
    int i=entete_f(f,1); /*positionnement a la tete du fichier*/
    int j=0,l=0,bi,bs;
    BLOC B1;
    int anciennete;
    char *ch1=malloc(sizeof(char)*3);
    char *ch2=malloc(sizeof(char));
    char *marque=malloc(sizeof(char));
    char *ch3=malloc(sizeof(char)*6);
    char *ch4=malloc(sizeof(char)*1024);
    char *inter=malloc(sizeof(char)*1024);
    char *inter1=malloc(sizeof(char)*1024);
    liredir(f,i,&B1);/*lecture du premier bloc*/
    char etab[256];
if(entete_f(f,6)!=0)/*si le fichier n'est pas vide*/
{
    printf("+=====================================================================================================================+\n");
    Color(05,15);
    printf("|                                            Requette a interval                                                      |\n");
    Color(0,15);
    printf("+=====================================================================================================================+\n");
    Color(0,15);
    printf("Donnez l'anciennte minimale et maximale (en annee):  \n\n");/*introduction de l'enciennté minimal et maximal*/
    int y=wherey();
    Color(2,15);
    printf("| borne inferieure :  ");
    Color(0,15);
    printf("\n=========================\n");
    gotoxy(22,y);
    scanf("%d",&bi);/*la borne inferieure*/
    Color(2,15);
    gotoxy(50,y);
    printf("| borne superieure :  ");
    Color(0,15);
    gotoxy(50,y+1);
    printf("=========================\n");
    gotoxy(71,y);
    scanf("%d",&bs);/*la borne superieure*/
    Color(2,15);
    printf("\n\n");
    y=wherey();
    printf("| Etablissement desire :  ");
    Color(0,15);
    printf("\n+====================================================================================================================+\n");
    Color(0,15);
    gotoxy(27,y);
    saisie_chaine(etab);/*lecture de l'etablissement*/
    system("cls");
    printf("+=====================================================================================================================+\n");
    Color(05,15);
    printf("|                                          Resultat de la requette a interval                                         |\n");
    Color(0,15);
    printf("+=====================================================================================================================+\n");
    for(l=0;l<=entete_f(f,6);l++)
    {
        recuperer_chaine(f,3,&i,&j,ch1,&B1); /*recuperation de taille,effacé,matricule ainsi que l'enregistrement*/
        recuperer_chaine(f,1,&i,&j,marque,&B1);
        recuperer_chaine(f,1,&i,&j,ch2,&B1);
        recuperer_chaine(f,1,&i,&j,marque,&B1);
        recuperer_chaine(f,6,&i,&j,ch3,&B1);
        recuperer_chaine(f,1,&i,&j,marque,&B1);
        recuperer_chaine(f,atoi(ch1)-9,&i,&j,ch4,&B1);
        if((strcmp(ch2,"N")==0))/*si l'enregistrement n est pas supprimé logiquement*/
        {
            recuperer_champs(ch4,11,inter1);/*recuperer le champs etablissement de  l'enregistrement en cours dans inter1*/

            if(strcmp(inter1,etab)==0)/*comparaison entre la clé introduite par l'utilisateur et celle recupéré*/
            {
             recuperer_champs(ch4,12,inter1);/*sil elle sont egaux on recupere maintenat la date de recuretement de l'enregistrement en cours*/
             anciennete=calcul_date("26/21/2019",inter1);/*on fait appelle a la fonction calcul_date qui va calculer la difference entre la date d'
             aujourdhui et celle de recutement afin de trouver l'ancienneté*/
             if((anciennete>=(bi*365))&&(anciennete<=(bs*365)))/*si l'ancienneté est comprise entre les bornes introduite par l'utilisateur
             on affiche l'enregistrement actuel ainsi que tous ses champs*/
                {
                indicateur=1;
                printf("+=====================================================================================================================+\n");
                recuperer_champs(ch4,1,inter);
                printf("|");
                Color(3,15);
                printf("        %s",inter);
                gotoxy(35,wherey());
                recuperer_champs(ch4,2,inter);
                Color(0,15);
                printf("|");
                Color(3,15);
                printf("        %s",inter);
                gotoxy(70,wherey());
                Color(0,15);
                printf("|");
                Color(3,15);
                printf("                   %s",ch3);
                gotoxy(119,wherey());
                Color(0,15);
                printf("|\n");
                printf("+=====================================================================================================================+\n");
                printf("|");
                Color(10,15);
                printf("          Informations personnelles ");
                gotoxy(55,wherey());
                Color(0,15);
                printf("|");
                printf("       ");
                Color(0,15);
                printf("           Parcours professionel ");
                gotoxy(119,wherey());
                Color(0,15);
                printf("|\n");
                printf("+---------------------------------------------------------------------------------------------------------------------+\n");
                recuperer_champs(ch4,3,inter);
                printf("|  Date de naissance : %s",inter);
                gotoxy(55,wherey());
                printf("|       ");
                recuperer_champs(ch4,7,inter);
                printf("Grade : %s",inter);
                gotoxy(119,wherey());
                printf("|\n");
                recuperer_champs(ch4,4,inter);
                printf("|  Wilaya : %s",inter);
                gotoxy(55,wherey());
                printf("|       ");
                recuperer_champs(ch4,9,inter);
                printf("Diplome : %s",inter);
                gotoxy(119,wherey());
                printf("|\n");
                recuperer_champs(ch4,5,inter);
                printf("|  Sexe : %s",inter);
                gotoxy(55,wherey());
                printf("|       ");
                recuperer_champs(ch4,10,inter);
                printf("Specialite : %s",inter);
                gotoxy(119,wherey());
                printf("|\n");
                recuperer_champs(ch4,6,inter);
                printf("|  Groupe_Sanguin : %s",inter);
                gotoxy(55,wherey());
                printf("|");
                recuperer_champs(ch4,11,inter);
                printf(" %s",inter);
                gotoxy(119,wherey());
                printf("|\n");
                printf("|",inter);
                gotoxy(55,wherey());
                printf("|       ");
                recuperer_champs(ch4,12,inter);
                printf("Date de recuretment : %s",inter);
                gotoxy(119,wherey());
                printf("|\n");
                printf("|",inter);
                gotoxy(55,wherey());
                printf("|       ");
                recuperer_champs(ch4,8,inter);
                printf("Region : %s",inter);
                gotoxy(119,wherey());
                printf("|\n");
                printf("+---------------------------------------------------------------------------------------------------------------------+\n\n");
                }
            }

        }
     }
        if(indicateur==0){/*si on ne trouve aucun enregistrement avec les specification on affiche un message d'erreur*/
        affichage_erreur_trouve();
         }
         else
         {
          Color(1,15);
          printf("                                      Appuyez sur n'import quelle touche pour continuer   ");
          Color(0,15);
          char c=getch();
         }
}else
{
    affichage_erreur_vide();/*si le fichier est vide*/
}
}
/*********************************************************************************************************************************************************/
/*                                    9)-  Modifications de l etablissement d un enseignant en raison de sa mutation                                    */
/*********************************************************************************************************************************************************/
void modification_etablissement(FILE *f)
{
    char matricule[1024];
    int i=1,j=0,k=0,trouv=0;
    BLOC    B1;
    char etab[100],champs[1024]="",taille_string[3]="",enregistrement[1024]="";
    char c;
    char *ch1=malloc(sizeof(char)*3);
    char *marque=malloc(sizeof(char));
    char *ch2=malloc(sizeof(char));
    char *ch3=malloc(sizeof(char)*6);
    char *ch4=malloc(sizeof(char)*1024);
    system("cls");
        Color(0,15);
        printf("+=====================================================================================================================+\n");
        Color(05,15);
        printf("|                     Modification de l'etablissement d'un enseignat en raison de sa mutation                         |\n");
        Color(0,15);
        printf("+=====================================================================================================================+\n");
        printf("Introduisez l'imatriculation de l enseignant pour la modification :  ");/*introduire le matricule de l'enseigant pour la modification*/
        saisie_chaine(matricule);/*saisir le matricule*/
        printf("\n");
        recherche_fichier(f,matricule,0,&trouv,&i,&j); /*recherche de la cle fans le fichier*/
if(trouv==1)/*si la cle existe*/
{
        liredir(f,i,&B1);   /*lecture du bloc dans lequel on a trouvé l'info*/
        recuperer_chaine(f,3,&i,&j,ch1,&B1);/*recuperation de la taille,effacement,matricule et l'enregistrement*/
        recuperer_chaine(f,1,&i,&j,marque,&B1);
        recuperer_chaine(f,1,&i,&j,ch2,&B1);
        recuperer_chaine(f,1,&i,&j,marque,&B1);
        recuperer_chaine(f,6,&i,&j,ch3,&B1);
        recuperer_chaine(f,1,&i,&j,marque,&B1);
        recuperer_chaine(f,atoi(ch1)-9,&i,&j,ch4,&B1);
        suppression_logique(f,matricule,0);/*suppression de l'enregistrement correspondant a la cléé*/
        printf("Introduisez l'etablissement pour la modification :  ");/*inroduire l'etablissement de la modification*/
        saisie_chaine(etab);
        printf("\n");
        strcat(enregistrement,"*");/*debut de construction d'un nouveau comme contenu taille*efface*matricule*nouveau enregistrement avec mise  a jour de
        de la taille */
        strcat(enregistrement,ch2);
        strcat(enregistrement,"*");
        strcat(enregistrement,ch3);
        strcat(enregistrement,"*");
        recuperer_champs(ch4,1,champs);
        strcat(enregistrement,champs);
        strcat(enregistrement,"*");
        recuperer_champs(ch4,2,champs);
        strcat(enregistrement,champs);
        strcat(enregistrement,"*");
        recuperer_champs(ch4,3,champs);
        strcat(enregistrement,champs);
        strcat(enregistrement,"*");
        recuperer_champs(ch4,4,champs);
        strcat(enregistrement,champs);
        strcat(enregistrement,"*");
        recuperer_champs(ch4,5,champs);
        strcat(enregistrement,champs);
        strcat(enregistrement,"*");
        recuperer_champs(ch4,6,champs);
        strcat(enregistrement,champs);
        strcat(enregistrement,"*");
        recuperer_champs(ch4,7,champs);
        strcat(enregistrement,champs);
        strcat(enregistrement,"*");
        recuperer_champs(ch4,8,champs);
        strcat(enregistrement,champs);
        strcat(enregistrement,"*");
        recuperer_champs(ch4,9,champs);
        strcat(enregistrement,champs);
        strcat(enregistrement,"*");
        recuperer_champs(ch4,10,champs);
        strcat(enregistrement,champs);
        strcat(enregistrement,"*");
        strcat(enregistrement,etab);
        strcat(enregistrement,"*");
        recuperer_champs(ch4,12,champs);
        strcat(enregistrement,champs);
        strcat(enregistrement,"|");
        recuperer_champs(ch4,11,champs);
        int taille=(atoi(ch1)-strlen(champs)+strlen(etab));/*mise a jour de la taille*/
        turn_to_string(taille_string,taille,3);
        strcat(taille_string,enregistrement);
        strcpy(enregistrement,taille_string);
        insertion_modifie(f,enregistrement);/*insertion de la nouvelle chaine a la fin du fichier*/
}
else/*si la cléé nexiste pas afficher une message d'erreur*/
{
affichage_erreur_cle_inexistante();
}
}
/*********************************************************************************************************************************************************/
/*                                   Insertion de l enregistrement avec modification a la fin du fichier                                                 */
/*********************************************************************************************************************************************************/
void insertion_modifie(FILE *f,char enreg[1024])
{
    BLOC B1,B2;
    int i=0,j=0,k=0,l=0,taille;
        i=entete_f(f,2);/*se positier au dernier bloc du fichier*/
        liredir(f,i,&B1);/*lire le dernier bloc dans le buffer*/
        j=entete_f(f,3)+1;
        while(k<strlen(enreg))/*Insertion de l'enregistrement comme precedemment*/
        {
            if(j<TAILLE_MAX)
            {
                B1.chaine[j]=enreg[k];
                B1.chaine[j+1]='\0';
                aff_entete(f,3,j);
                j++;
                k++;
            }
            else
            {
                j=0;
                allocbloc(f,i+1,&B2);
                B1.suivant=i+1;
                ecriredir(f,i,&B1);
                B1=B2;
                strcpy(B1.chaine,"");
                i++;
             }
        }

                B1.chaine[j+1]='\0';
                B1.suivant=-1;
                ecriredir(f,i,&B1);
                aff_entete(f,6,entete_f(f,6)+1);/*augmenter le nombre d'enregistrement inserés de l'entete*/
                Color(0,15);
printf("\n");
        printf("+=====================================================================================================================+\n");
        Color(2,15);
        printf("|                                          Operation effectue avec succes                                             |\n");
        Color(0,15);
        printf("+=====================================================================================================================+\n\n");
        Color(1,15);
        printf("                               Appuyez sur n'import quelle touche pour continuer   ");
        getche();
}
/*********************************************************************************************************************************************************/
/*                                                          10)-  Reorganisation d un fichier donné                                                      */
/*********************************************************************************************************************************************************/
void reorganisation(FILE *f)
{
    system("cls");
    Color(0,15);
    printf("+=====================================================================================================================+\n");
    Color(05,15);
    printf("|                                            Rorganisation du fichier                                                 |\n");
    Color(0,15);
    printf("+=====================================================================================================================+\n");
    char inter[1024];
    FILE *P=ouvrir('N');
    int i=entete_f(f,1); /*positionnement a la tete du fichier*/
    int j=0,k=0,l=0,m=0,n=0,cpt=0;
    BLOC B1,B2,B3;/*3 buffers en memoires centrale,B1 pour lire les bloc du fichier f,et B2et B3 pour ecrire dans le nouveau fichier a construire*/
    char *ch1=malloc(sizeof(char)*3);
    char *ch2=malloc(sizeof(char));
    char *ch3=malloc(sizeof(char)*6);
    char *ch4=malloc(sizeof(char)*1024);
    char *marque=malloc(sizeof(char));
    Color(5,15);
    printf("\n                                  L'operation de reorganisation va bientot commencer  \n\n");
    Sleep(2000);
    Color(0,15);
    printf("+=====================================================================================================================+\n\n");
    Color(2,15);
    printf("\n------------------                 Operation en cours . Veillez pationneter               ---------------------------\n\n\n");
    Color(0,15);
    liredir(f,i,&B1);    /* lecture du premier bloc*/
if(entete_f(f,6)!=0)/*si le fichier n'est pas vide*/
{
    for(n=0;n<=entete_f(f,6);n++)/*parcourir sequentiellement tous les enregistrements du fichier un par un*/
    {
        if(n%100==0){
         loading();
        }
        recuperer_chaine(f,3,&i,&j,ch1,&B1); /* on commence a recuperer taille dans ch1,efface dans ch2 ,matricule dans ch3,enregistrement dans ch4*/
        recuperer_chaine(f,1,&i,&j,marque,&B1);
        recuperer_chaine(f,1,&i,&j,ch2,&B1);
        recuperer_chaine(f,1,&i,&j,marque,&B1);
        recuperer_chaine(f,6,&i,&j,ch3,&B1);
        recuperer_chaine(f,1,&i,&j,marque,&B1);
        recuperer_chaine(f,atoi(ch1)-9,&i,&j,ch4,&B1);
              if(strcmp(ch2,"N")==0)/*si l enregistrement n a pas été supprimé logiquement*/
              {
                k=0;
                strcpy(inter,"");/*construction de la chaine inter contenant taille*efface*matricule*enregistrement*/
                strcat(inter,ch1);
                strcat(inter,marque);
                strcat(inter,ch2);
                strcat(inter,marque);
                strcat(inter,ch3);
                strcat(inter,marque);
                strcat(inter,ch4);
                cpt++;
                       while(k<strlen(inter))/*ecriture de inter dans le nouveau fichier*/
                       {
                             if(m<TAILLE_MAX)
                              {
                                B2.chaine[m]=inter[k];
                                B2.chaine[m+1]='\0';
                                aff_entete(P,3,m);
                                m++;
                                k++;

                             }
                             else
                             {
                                m=0;
                                allocbloc(P,l+2,&B3);
                                B2.suivant=l+2;
                                ecriredir(P,l+1,&B2);
                                B2=B3;
                                strcpy(B2.chaine,"");
                                l++;
                            }
                     }

             }
    }
                B2.chaine[m+1]='\0';
                B2.suivant=-1;
                ecriredir(P,l+1,&B2);
                aff_entete(P,6,cpt);/*recuperation du nombre d enregistrements de f*/
                fermer(P);
                fermer(f);
Color(0,15);
printf("\n");
        printf("+=====================================================================================================================+\n");
        Color(2,15);
        printf("|                                          Operation effectue avec succes                                             |\n");
        Color(0,15);
        printf("+=====================================================================================================================+\n\n");
        Color(1,15);
        printf("                               Appuyez sur n'import quelle touche pour continuer   ");
        getche();
}
else{
    affichage_erreur_vide();
}
}
/*********************************************************************************************************************************************************/
/*                                                          Fonctions d affichage                                                                        */
/*********************************************************************************************************************************************************/
/*********************************************************************************************************************************************************/
/*                                                          11)-  Affichage de l'ente d'un fichier                                                       */
/*********************************************************************************************************************************************************/
void afficher_entete(FILE*f) // affichage de l'entete
{
    system("cls");
    cadre();
    gotoxy(17,4);
    printf("L'indice de la tete");gotoxy(65,4);
    printf("²        %d",entete_f(f,1));
    gotoxy(17,5);
    printf("==================================================================================");
    gotoxy(17,6);
    printf("L'indice de la queu");gotoxy(65,6);
    printf("²        %d",entete_f(f,2));
    gotoxy(17,7);
    printf("==================================================================================");
    gotoxy(17,8);
    printf("L'indice de la derniere position dans la queu");gotoxy(65,8);
    printf("²        %d",entete_f(f,3));
    gotoxy(17,9);
    printf("==================================================================================");
    gotoxy(17,10);
    printf("Le nombre de caracteres effaces");gotoxy(65,10);
    printf("²        %d",entete_f(f,4));
    gotoxy(17,11);
    printf("==================================================================================");
    gotoxy(17,12);
    printf("Le nombre de blocs");gotoxy(65,12);
    printf("²        %d",entete_f(f,5));
    gotoxy(17,13);
    printf("==================================================================================");
    gotoxy(17,14);
    printf("Le nombre d'enregistrements");gotoxy(65,14);
    printf("²        %d",entete_f(f,6));
    gotoxy(17,15);
    printf("==================================================================================");
    gotoxy(17,16);
    printf("Le nombre de lectures");gotoxy(65,16);
    printf("²        %d",entete_f(f,7));
    gotoxy(17,17);
    printf("==================================================================================");
    gotoxy(17,18);
    printf("Le nombre d'ecritures");gotoxy(65,18);
    printf("²        %d",entete_f(f,8));
    gotoxy(15,20);
    Color(0,15);
    printf("²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²");
    gotoxy(17,21);
    Color(5,15);
    printf("                        Les caracteristiques de l'entete ");
    Color(1,15);
    gotoxy(15,26);
    printf("                        Appuyez sur n'import quelle touche pour continuer   ");
    char c=getch();
    system("cls");

}
/*********************************************************************************************************************************************************/
/*                                                          12)-  affichage des 3 premiere blocs du fichier                                              */
/*********************************************************************************************************************************************************/
void afficher_bloc(FILE*f) // affichage de l'entete
{
    system("cls");
    tres_grand_cadre();
    BLOC B1;
    int i=0,j=2,k=1;
while(k<4){/*tant que k est inferieur a 4 c est a dire on va utiliser cas comme indice des blocs*/
    gotoxy(4,j);
    Color(05,15);
    printf("                                                Bloc %d                                        ",k);
    j++;
    gotoxy(2,j);
    Color(0,15);
    printf("======================================================================================================================\n");
    j++;
    liredir(f,k,&B1);/*lire le bloc dans B1*/
    gotoxy(4,j);
    printf("%c",B1.chaine[i]);
    i++;
    for(i=1;i<1025;i++){
        printf("%c",B1.chaine[i]);/*ecrire caractere par caracteres juste pour un affichage obtimal*/
        if(i%114==0){
            j++;
            gotoxy(4,j);
        }
    }
    j=j+2;
    gotoxy(2,j);
    Color(3,15);
/***********************************/
    for(i=1;i<119;i++){/*affichage*/
        Sleep(20);
        printf("²");
    }
    j=j+2;
k++;
}
    Color(1,15);
    printf("\n\n                               Appuyez sur n'import quelle touche pour continuer   ");
    getche();

 }
 /*********************************************************************************************************************************************************/
