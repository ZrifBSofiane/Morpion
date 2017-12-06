
#include <stdio.h>



int** creer_morpion();
void initiliser(int** morpion);
void afficher(int** morpion);
void placer(int** morpion,int valeur_joueur);
int verifier(int ligne, int colonne,int** morpion,int valeur_joueur);
int demander_ligne();
int demander_colonne();
int gain_horizontal(int** morpion);
int gain_vertical(int** morpion);
int gain_diagonal(int** morpion);
int fin_jeu(int** morpion);
int plateau_full(int** morpion);
void jeu_morpion();
int nombre_case_vide(int** morpion);
int** copier_matrice(int** morpion);
