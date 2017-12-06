#include "morpion.h"
#include "ORDI.h"
#include <time.h>

int** creer_morpion()
{
    int** morp=(int**)malloc(3*sizeof(int*));

    int i=0;
    for(i=0;i<3;i++)
    {
        morp[i] = (int*)malloc(3*sizeof(int));
    }
    return morp;
}

void initiliser(int** morpion)
{
    int i,j;
    for(i=0; i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            morpion[i][j]=0;
        }
    }
}

void afficher(int** morpion)
{
    int i=0;
    int j=0;
    char joueur1 = 'X';
    char joueur2 = 'O';
    printf("\n| \\ | a | b | c |\n");
    printf("-----------------\n");
    for(i=0; i<3;i++)
    {
        printf("| %d |",i+1 );

        for(j=0;j<3;j++)
        {
            if(morpion[i][j]==1)
            {
                printf(" %c |",joueur1);
            }
            else
            {
                if(morpion[i][j]==2)
                {
                    printf(" %c |",joueur2);
                }
                else
                {
                    printf("   |");
                }
            }
        }
        printf("\n");
         printf("-----------------\n");
    }
}

int verifier(int ligne, int colonne,int** morpion,int valeur_joueur) // retourne 1 si on peut placer
{
    int occupe = 1 ;
    if(morpion[ligne][colonne] != 0 )
    {
        occupe = 0;
        if(valeur_joueur == 0)
        {
            printf("\nCase deja prise");
        }
    }
    return occupe;
}

int demander_ligne()
{
    int ligne=0;
    do
    {
        printf("Quelle ligne ?\n");
        scanf("%d",&ligne);
    }while(ligne != 1 && ligne != 2 && ligne != 3);

    return ligne-1;
}

int nombre_case_vide(int** morpion)
{
    if(morpion == NULL)
    {
        printf("\nRien a faire ...");
    }
    else
    {
            int nombre = 0;
        int i,j;
        for(i=0;i<3;i++)
        {
            for(j=0;j<3;j++)
            {
                if(morpion[i][j]==0)
                {
                    nombre +=1;
                }
            }
        }
        //printf("\nIl reste %d case(s) libre(s)",nombre);
        return nombre;
    }
}



int** copier_matrice(int** morpion)
{
    int** copie=creer_morpion();
    int i,j;
    for(i =0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            copie[i][j]=morpion[i][j];
        }
    }
    return copie;
}

int demander_colonne()
{
    char colonne = " ";
    int nombre = 0;
    printf("\n");
    do
    {
        printf("Quelle colonne ?\n");
        scanf("%c",&colonne);

    }while(colonne != 'a' && colonne != 'b' && colonne != 'c' && colonne != 'A' && colonne != 'B' && colonne != 'C');
    if(colonne == 'a' || colonne == 'A')
    {
        nombre = 1;
    }
    if(colonne == 'b' || colonne == 'B')
    {
        nombre = 2;
    }
    if(colonne == 'c' || colonne == 'C')
    {
        nombre = 3;
    }
    return nombre-1;
}

void placer(int** morpion,int valeur_joueur)
{
    srand(time(NULL));
    int ligne = 0;
    int colonne = 0;

    do
    {
        if(valeur_joueur == 1)
        {
            ligne = demander_ligne();
            colonne = demander_colonne();
        }
        else
        {
            arbre_IA * racine = NULL;
            int ** copie_morpion_pour_arbre = copier_matrice(morpion);
            int ** copie_morpion_pour_poids_arbre = copier_matrice(morpion);
            racine = IA_ordi(copie_morpion_pour_arbre,valeur_joueur);
            int choix = 0;
            do{
                 printf("\nCreation de l'arbe, voulez vous l'afficher ?: 1 - OUI 2- NON\n");
                 scanf("%d",&choix);
            }while(choix != 1 && choix !=2);
            if(choix==1)
            {
                affichage_arborescence(racine,0);
            }
            
             printf("\nFin choix ordi\n");
            ligne = racine->ligne;
            colonne = racine->colonne;
            /*if(morpion[0][0]==0)
            {
                ligne = 0;
                colonne = 0;
            }
            else
            {
                ligne = rand() % 3;
                colonne = rand() %3;
            }*/
           // printf("\n Il reste apres la racine %d cases libres",nombre_case_vide(morpion));
        }

    }while(verifier(ligne,colonne,morpion,valeur_joueur) == 0);


    if(verifier(ligne,colonne,morpion,valeur_joueur) == 1)
    {
        morpion[ligne][colonne] = valeur_joueur;
    }

}

int gain_vertical(int** morpion)
{
    int gagne = 0;
    int colonne=0;
    for(colonne = 0; colonne<3;colonne++)
    {
        if((morpion[0][colonne]==1 && morpion[1][colonne]==1 && morpion[2][colonne]== 1) || (morpion[0][colonne]==2 && morpion[1][colonne]==2 && morpion[2][colonne]== 2))
        {
            gagne = 1;
            printf("\nCombinaison verticale");
        }
    }
    return gagne;
}

int gain_horizontal(int** morpion)
{
    int gagne = 0;
    int ligne=0;
    for(ligne = 0; ligne<3;ligne++)
    {
        if((morpion[ligne][0]==1 && morpion[ligne][1]==1 && morpion[ligne][2]==1) || (morpion[ligne][0]==2 && morpion[ligne][1]==2 && morpion[ligne][2]==2))
        {
            gagne = 1;
            printf("\nCombinaison horizontale");
        }
    }
    return gagne;
}

int gain_diagonal(int** morpion)
{
    int gagne=0;
    if(((morpion[0][0]==1 && morpion[1][1]==1 && morpion[2][2]==1)||(morpion[0][0]==2 && morpion[1][1]==2 && morpion[2][2]==2)) ||((morpion[2][0]==1 && morpion[1][1]==1 && morpion[0][2]==1)||(morpion[2][0]==2 && morpion[1][1]==2 && morpion[0][2]==2)))
    {
        gagne = 1;
        printf("\nCombinaison diagonale");
    }
    return gagne;
}

int fin_jeu(int** morpion)
{
    int fin = 1;
    if(gain_diagonal(morpion) || gain_horizontal(morpion) || gain_vertical(morpion))
    {
        fin = 0;
    }
    return fin;
}

int plateau_full(int** morpion)
{
    int full = 1;
    int i,j;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            if(morpion[i][j]==0)
            {
                full = 0;
            }
        }
    }
    return full;
}

void jeu_morpion_2VS()
{
     int** morpion = creer_morpion();
    initiliser(morpion);
    int nb_joueur = 0;
    int joueur = 1;
    afficher(morpion);
    do
    {
        printf("\nJoueur %d : ",joueur);
        placer(morpion,joueur);
        afficher(morpion);
        nb_joueur +=1;
        joueur = nb_joueur %2+1;
        nombre_case_vide(morpion);
    }while(fin_jeu(morpion) && !plateau_full(morpion));
    if(plateau_full(morpion))
    {
        printf("\nMatch nul...");
    }
    else
    {
        nb_joueur +=1;
        joueur = nb_joueur %2+1;
        printf("\nLe joueur %d a gagne",joueur);
    }
}

void jeu_morpion_VS_ordi()
{
    int** morpion = creer_morpion();
    initiliser(morpion);
    int nb_joueur = 0;
    int joueur = 1; // 1 homme 0 ordi 
    int choix = 0;
    do
    {
        printf("\nVeux-tu jouer en premier ? 1: OUI 2: NON");
        scanf("%d",&choix);
    }while(choix != 1 && choix !=2);
 
    if(choix == 1)
    {
        joueur = 1;
    }
    else
    {
        joueur = 2;
        nb_joueur = 1;
    }
    afficher(morpion);
    do
    {
        if(joueur == 1)
        {
            printf("\nJoueur %d : ",joueur);
        }
        else
        {
            printf("\nL'ordi a ton tour :\n");
        }

        placer(morpion,joueur);
        afficher(morpion);
        nb_joueur +=1;
        joueur = nb_joueur %2+1;
        //nombre_case_vide(morpion);
    }while(fin_jeu(morpion) && !plateau_full(morpion));
    if(plateau_full(morpion))
    {
        printf("\nMatch nul...");
    }
    else
    {
        nb_joueur +=1;
        joueur = nb_joueur %2+1;
        printf("\nLe joueur %d a gagne",joueur);
    }
}
