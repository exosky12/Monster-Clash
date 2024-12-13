#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {False, True} Boolean;

typedef struct maillon2
{
    int v;
    struct maillon2 *suiv;
} Maillon2, *File;

typedef struct {
    char nom[50];           // Nom du monstre
    int niveau;             // Niveau du monstre (1, 2 ou 3)
    int pointsVie;          // Points de vie du monstre
    int pointsDegats;       // Points de dégâts infligés par attaque
    char armes[5];          // Liste des armes disponibles ('P', 'F', 'C', 'O', '#')
    int nbArmes;            // Nombre d'armes disponibles
} Monstre;

typedef struct {
    Monstre *monstres;      // Tableau dynamique de monstres
    int nbMonstres;         // Nombre de monstres dans le groupe
    int type;               // Type du groupe : 1 pour séquentiel, 2 pour simultané
} GroupeMonstres;

File FileVide(void);
File adjq(File f, int x);
File supprimerEnTete(File f);
Boolean estVide2(File f);
int tete2(File f);
void affiche(File f);
int longueur2(File f);

void global(void);
void clearScreen(void);
void existingGameDisplay(void);
void existingGame(void);
void createNewGameDisplay();
void createNewGame(void);