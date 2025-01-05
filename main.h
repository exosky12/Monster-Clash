#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED "\033[31m"
#define RESET "\033[0m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"
#define GREEN "\033[32m"
#define BOLD "\033[1m"
#define MAGENTA "\033[35m"

typedef enum
{
    False,
    True
} Boolean;

typedef struct Node
{
    int v;
    struct Node *suiv;
} Node, *Heap;

typedef struct
{
    char nickname[50]; // Surnom du joueur (maximum 50 caractères + caractère de fin de chaîne)
    int nbPv;          // Nombre de points de vie du joueur
    int nbDamages;     // Nombre total de dégâts infligés par le joueur
    int nbGames;       // Nombre de jeux/joues auxquels le joueur a participé
    int *scores;       // Scores
    char weapons[4];   // Liste des armes disponibles pour le joueur ('P', 'F', 'C', 'O', '#')
} Player;

typedef struct
{
    char name[50]; // Nom du monstre
    int level;     // Niveau du monstre (1, 2 ou 3)
    int pv;        // Points de vie du monstre
    int damage;    // Points de dégâts infligés par attaque
    int nbWeapons; // Nombre d'armes disponibles
    char *weapons; // Liste des armes disponibles ('P', 'F', 'C', 'O', '#')
} Monster;

typedef struct
{
    Monster *monsters; // Tableau dynamique de monstres
    int nbMonsters;    // Nombre de monstres dans le groupe
    int type;          // Type du groupe : 1 pour séquentiel, 2 pour simultané
} MonstersGroup;

typedef struct
{
    Player *players; // Tableau dynamique de joueurs
    int nbPlayers;   // Nombre total de joueurs
} Leaderboard;

Heap heapEmpty(void);
Heap add(Heap f, int x);
Heap deleteHead(Heap f);
Boolean isEmpty(Heap f);
int head(Heap f);
void display(Heap f);
int length(Heap f);

void global(void);
void clearScreen(void);
void existingGameDisplay(Player **playersTab, int *nbPlayers, char *filename, Monster monstersTab[100], int nbMonstersGroup);
void game(Player player, Player playersTab[100], Monster monstersTab[100], int nbMonstersGroup);
void createNewGameDisplay(int *nbPlayers, Player **playersTab, Monster monstersTab[100], int nbMonstersGroup);
char determineWinner(char weaponPlayer, char weaponMonster);
int dichotomousSearch(char playerName[50], Player playersTab[100], int nbPlayers, int *trouve);
Monster *loadMonsters(char *filename, int *nbMonsters);
// void showEveryMonsters(Monster *monsters, int nbMonsters);

Player *loadPlayersFromBinary(char *filename, int *nbPlayers);
void savePlayersToBinary(char *filename, Player *players, int nbPlayers);

void showPlayers(Player *players, int nbPlayers);
void sortPlayers(Player *playersTab[], int nbPlayers, char sortType);
void switchPlayers(Player *playersTab[], int i, int j);
int biggestScore(Player *PlayersTab[], int nbPlayers);
