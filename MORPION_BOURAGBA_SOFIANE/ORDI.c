#include <stdlib.h>
#include <stdio.h>
#include "morpion.h"
#include "ORDI.h"


arbre_IA * initialisation_arbre()
 {
     arbre_IA* arbre = (arbre_IA*)malloc(sizeof(arbre_IA));
     arbre->colonne = 3;
     arbre->ligne=3;
     arbre->poids = 0;
     arbre->fils = NULL;
     arbre->frere = NULL;
     arbre->fils_au_pere = NULL;
     arbre->frere_au_pere = NULL;

    return arbre;
 }


int gain_vertical_IA_ORDI(int** morpion)
{
    int gagne = 0;
    int colonne=0;
    for(colonne = 0; colonne<3;colonne++)
    {
        if((morpion[0][colonne]==2 && morpion[1][colonne]==2 && morpion[2][colonne]== 2))
        {
            gagne = 1;
            printf("\nCombinaison verticale");
        }
        if((morpion[0][colonne]==1 && morpion[1][colonne]==1 && morpion[2][colonne]== 1))
        {
            gagne = -1;
            printf("\nCombinaison verticale");
        }
    }
    return gagne;
}



int gain_horizontal_IA_ORDI(int** morpion)
{
    int gagne = 0;
    int ligne=0;
    for(ligne = 0; ligne<3;ligne++)
    {
        if((morpion[ligne][0]==2 && morpion[ligne][1]==2 && morpion[ligne][2]==2))
        {
            gagne = 1;
            printf("\nCombinaison horizontale");
        }
        if((morpion[ligne][0]==1 && morpion[ligne][1]==1 && morpion[ligne][2]==1))
        {
            gagne = -1;
            printf("\nCombinaison horizontale");
        }
    }
    return gagne;
}


int gain_diagonal_IA_ORDI(int** morpion)
{
    int gagne=0;
    if((morpion[0][0]==2 && morpion[1][1]==2 && morpion[2][2]==2)||(morpion[2][0]==2 && morpion[1][1]==2 && morpion[0][2]==2))
    {
        gagne = 1;
        printf("\nCombinaison diagonale");
    }
    if((morpion[0][0]==1 && morpion[1][1]==1 && morpion[2][2]==1)||(morpion[2][0]==1 && morpion[1][1]==1 && morpion[0][2]==1))
    {
        gagne = -1;
        printf("\nCombinaison diagonale");
    }
    return gagne;
}



int fin_jeu_IA_ORDI(int** morpion)
{
    int fin = 0;
    if(gain_diagonal_IA_ORDI(morpion) == -1|| gain_horizontal_IA_ORDI(morpion) ==-1 || gain_vertical_IA_ORDI(morpion) == -1)
    {
        fin = -1;
    }
    else
    {
        if(gain_diagonal_IA_ORDI(morpion) == 1|| gain_horizontal_IA_ORDI(morpion) == 1 || gain_vertical_IA_ORDI(morpion) == 1)
        {
            fin = 1;
        }
    }
    return fin;
}


void affichage_arborescence(arbre_IA* arbre,int compteur)
{
  if(arbre != NULL)
  {
        int i=0;
         printf("\n");
        for(i = 0; i<= compteur;i++)
            printf("   ");
        if(arbre->joueur == 1)
        {
            printf("|-L : %d C : %d Joueur : TOI ",arbre->ligne, arbre->colonne);
        }
        else
        {
            if (arbre->joueur == 2)
            {
                 printf("|-L : %d C : %d Joueur : ORDI ",arbre->ligne, arbre->colonne);
            }
            else
            {
                printf("Arbre en Arborescence : ");
            }
           
        }
        
      
      affichage_arborescence(arbre->fils,compteur+1);
      affichage_arborescence(arbre->frere,compteur+1);
  }
  if( arbre == NULL)
  {
        int i=0;
         printf("\n");
        for(i = 0; i<= compteur;i++)
            printf("   ");

      printf("|-x ");
  }

}




int nombre_de_frere(arbre_IA* racine)
{
    int frere = 0;
    if(racine->frere == NULL)
    {
        frere = 0;
    }
    else
    {
        if(racine->frere->frere == NULL)
        {
            frere = 1;
        }
        else
        {
            arbre_IA* temp = racine;
            while(temp != NULL)
            {
                frere++;
                temp=temp->frere;
            }
            frere--;
        }
    }
    return frere;
}


arbre_IA* IA_ordi(int ** morpion,int joueur) // permet de creer l'arbre
{
    int nombre_case_vid = nombre_case_vide(morpion);
    int ligneH2 = 3;
    int colonneH2 = 3;
    arbre_IA * racine = initialisation_arbre();
    arbre_IA* temp_h1_fils = racine;
    arbre_IA* temp = racine;
    int hauteur = 1;
    int** copie_h1_fils = NULL;
    copie_h1_fils = copier_matrice(morpion);
    int ** copie_h1 = NULL;
    int ** copie_h2 = NULL;
    for(int i=0; i<3 && hauteur !=3;i++)
    {
        for(int j=0;j<3 && hauteur !=3;j++)
        {

            if(morpion[i][j] == 0)
            {
                int ligne = i;
                int colonne = j;
                morpion[ligne][colonne] = joueur;
                if(hauteur == 2)
                {
                    //afficher(morpion);
                    
                    hauteur++;
                }
                if(hauteur == 1)
                {
                    copie_h1 = copier_matrice(morpion);
                    copie_h2 = copier_matrice(morpion);
                    hauteur++;
                }
                arbre_IA* fils = initialisation_arbre();
                fils->colonne=colonne;
                fils->ligne = ligne; 
                fils->poids = fin_jeu_IA_ORDI(morpion);
                if(fils->poids == 1)
                {
                    racine->ligne = ligne;
                    racine->colonne = colonne;
                    return racine;
                }
                fils->fils_au_pere = temp;      // retour  
                if(hauteur == 3)
                {
                    fils->joueur = 1;
                }
                else
                {
                    if(hauteur == 2)
                    {
                        fils->joueur = 2;
                    }
                }
                joueur = joueur%2+1;
                temp->fils = fils;
                temp=temp->fils;
               // printf("\nLES FILS 1 ET 2 \n");
                //afficher(morpion);
            }
        }
    } // Fin des fils de racine !!! On s'arrête a la hauteur 2 
    // On s'occupe maintenant des freres !
    
    //Frere pour la hauteur 1 !!!
    int nombre_cases_vides_h1 = nombre_case_vide(copie_h1);
    int nombre_cases_vides_h2 = nombre_case_vide(copie_h2);
    
    arbre_IA* temp_h1 = racine->fils;
    while(nombre_cases_vides_h1 != 0)
    {
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                if(copie_h1[i][j] == 0)
                {
                    int ligne = i;
                    int colonne = j;
                    morpion[ligne][colonne] = joueur;
                    arbre_IA* frere = initialisation_arbre();
                    frere->colonne=colonne;
                    frere->ligne = ligne;
                    frere->joueur = 2;
                    //frere->frere_au_pere = temp ;
                    temp_h1->frere = frere;
                    temp_h1=temp_h1->frere;
                    nombre_cases_vides_h1--;
                   
                }
            }
        }
    }
    
    // Frere pour la hauteur 2 !!
    arbre_IA* temp_h2 = racine->fils->fils;
    // afficher(copie_h2);
    while(nombre_cases_vides_h2 != 0)
    {
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                if(copie_h2[i][j] == 0)
                {
                    int ligne = i;
                    int colonne = j;
                    morpion[ligne][colonne] = joueur;
                    copie_h2[ligne][colonne] = 1;
                  //  printf("\nH2 !!!\n");
                  //   afficher(copie_h2);
                    arbre_IA* frere = initialisation_arbre();
                    frere->colonne=colonne;
                    frere->ligne = ligne;
                    frere->joueur = 1;
                    frere->poids = fin_jeu_IA_ORDI(copie_h2); 
                    temp_h2->frere = frere;
                    temp_h2=temp_h2->frere;
                    nombre_cases_vides_h2--;
                    copie_h2[ligne][colonne] = 0;
                    
                }
            }
        }
    }
    arbre_IA* temp_pods_h2 = racine;
    int min = 0;
    if(racine->fils->fils != NULL)
    {
        temp_pods_h2 =racine->fils->fils;
        min = temp_pods_h2->poids;
        while(temp_pods_h2!=NULL)
        {
            if(temp_pods_h2->poids<=min)
            {
                min = temp_pods_h2->poids;
                ligneH2 = temp_pods_h2->ligne;
                colonneH2 = temp_pods_h2->colonne;
                racine->fils->poids = min ; // On suppose que racine->fils != NULL car lui meme possede un fils on lui donne le min de H2
                racine->fils->colonne = temp_pods_h2->colonne;
                racine->fils->ligne = temp_pods_h2->ligne;
            }
            temp_pods_h2=temp_pods_h2->frere;
        }
        
    }
    
    // Fin des freres pour les hauteurs 1 et 2 !!!
    //Comme on a decider de s'arreter a la hauteur deux, on doit aussi faire les fils de chaque morpion de la hauteur 1 !!
    //On s'occupe donc maintenant des fils de la hauteur 1 !! Sauf pour le premier element car lui possede deja son fils, c'est le fils du fils de la racine
    
    temp_h1_fils = racine->fils;
    temp_h1_fils->poids= fin_jeu_IA_ORDI(copie_h1_fils);
    //printf("\n\n*******LES POIDS EST DE : %d",temp_h1_fils->poids);
    int nombre_frere = nombre_de_frere(temp_h1_fils);
   // printf("Il y a %d frere",nombre_frere);
    temp_h1_fils=temp_h1_fils->frere;
    //afficher(copie_h1_fils);
    for(int i=0;i<nombre_frere;i++)
    { 
        int continuer = 1;
        int ligne = temp_h1_fils->ligne;
        int colonne = temp_h1_fils -> colonne;
        copie_h1_fils[ligne][colonne] = joueur;
       // afficher(copie_h1_fils);
        for(int k=0;k<3 && continuer;k++)
        {
            for(int j=0;j<3 && continuer;j++)
            {
                if(copie_h1_fils[k][j]==0)
                {
                    int ligne1 = k;
                    int colonne1 = j;
                    arbre_IA* fils_h1 = initialisation_arbre();
                    fils_h1->colonne=colonne1;
                    fils_h1->ligne = ligne1;
                    fils_h1->fils_au_pere=temp_h1_fils;
                    fils_h1->joueur=1;
                   
                    
                    copie_h1_fils[ligne1][colonne1]=1; // On fait jouer TOI pour evaluer le poids
                    //printf("\nMorpion h1_fils__fils\n");
                   // afficher(copie_h1_fils);
                    fils_h1->poids = fin_jeu_IA_ORDI(copie_h1_fils);
                    copie_h1_fils[ligne1][colonne1]=0; // On enleve
                   // printf("\nMorpion h1_fils_initial\n");
                    //afficher(copie_h1_fils);
                    temp_h1_fils->fils = fils_h1;
                    temp_h1_fils->poids = temp_h1_fils->fils->poids;
                    continuer = 0;
                }
            }
        }
         copie_h1_fils[ligne][colonne] = 0; // On enleve celui de H1
        
        temp_h1_fils = temp_h1_fils->frere;
    }
    arbre_IA* temp_poids_h1 = racine;
    int max_h1 = 0;
    int continuer = 1;
    if(racine->fils != NULL)
    {
        temp_poids_h1 =racine->fils;
        max_h1 = temp_poids_h1->poids;
        while(temp_poids_h1!=NULL && continuer)
        {
            if(temp_poids_h1->poids>=max_h1)
            {
                max_h1 = temp_poids_h1->poids;
                if(max_h1==1)
                {
                    racine->poids = max_h1 ; // On suppose que racine->fils != NULL car lui meme possede un fils on lui donne le min de H2
                    racine->colonne = temp_poids_h1->colonne;
                    racine->ligne = temp_poids_h1->ligne;
                    continuer = 0;
                }
            }
            temp_poids_h1=temp_poids_h1->frere;
        }
    }
    if(racine->fils->fils != NULL && continuer)
    {
        racine->poids = min ; // On suppose que racine->fils != NULL car lui meme possede un fils on lui donne le min de H2
        racine->colonne = colonneH2;
        racine->ligne = ligneH2;
    }
    //afficher(copie_h1);
    //afficher(copie_h2);
    
    return racine;
}


