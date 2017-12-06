typedef struct _arbre_IA
{
    int poids;
    int ligne;
    int colonne;
    int joueur;
    struct _arbre_IA* fils;
    struct _arbre_IA* frere;
    struct _arbre_IA* fils_au_pere;
    struct _arbre_IA* frere_au_pere;
}arbre_IA;



arbre_IA * initialisation_arbre();
int gain_vertical_IA_ORDI(int** morpion);
int gain_horizontal_IA_ORDI(int** morpion);
int gain_diagonal_IA_ORDI(int** morpion);
int fin_jeu_IA_ORDI(int** morpion);

int gain_vertical_IA_TOI(int** morpion);
int gain_horizontal_IA_TOI(int** morpion);
int gain_diagonal_IA_TOI(int** morpion);
int fin_jeu_IA_TOI(int** morpion);

arbre_IA* IA_ordi(int ** morpion,int joueur);
void initialisation_arbre_IA(arbre_IA* arbre);
int nombre_de_frere(arbre_IA* racine);
void affichage_arborescence(arbre_IA* arbre,int compteur);