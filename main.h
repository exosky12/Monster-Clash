#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {False, True} Boolean;

typedef struct Node
{
    int v;
    struct Node *suiv;
} Node, *Heap;

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

Heap heapEmpty(void);
Heap add(Heap f, int x);
Heap deleteHead(Heap f);
Boolean isEmpty(Heap f);
int head(Heap f);
void display(Heap f);
int length(Heap f);

void global(void);
void clearScreen(void);
void existingGameDisplay(void);
void existingGame(void);
void createNewGameDisplay();
void createNewGame(void);