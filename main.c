#include "main.h"

File file1Vide(void)
{
    File f;
    f.t = NULL;
    f.q = NULL;
    return f;
}

File emphiler(File f, int x)
{
    Maillon *m;
    m = (Maillon *)malloc(sizeof(Maillon));
    if (m == NULL)
    {
        printf("Opération interdite");
        exit(1);
    }
    m->v = x;
    m->suiv = NULL;
    if (estVide(f))
    {
        f.t = m;
        f.q = m;
    }
    f.q->suiv = m;
    f.q = m;
    return f;
}

File supprimer(File f)
{
    Maillon *m;
    if (f.t == NULL && f.q == NULL)
    {
        printf("Opération interdite");
        exit(1);
    }
    if (f.t == f.q)
    {
        free(f.t);
        return file1Vide();
    }
    m = f.t;
    f.t = f.t->suiv;
    free(m);
    return f;
}

Boolean estVide(File f)
{
    return f.t == NULL && f.q == NULL;
}

int longueur(File f)
{
    int l = 0;
    while (f.t != NULL)
    {
        l++;
        f.t = f.t->suiv;
    }
    return l;
}

void afficher(File f)
{
    while (f.t != NULL)
    {
        printf("%d", f.t->v);
        f.t = f.t->suiv;
    }
}

int tete(File f)
{
    if (estVide(f))
    {
        printf("Opération interdite");
        exit(1);
    }
    return f.t->v;
}

void existingGameDisplay(void)
{
  FILE *gameFile;
  char gameName[100], playerName[100];
  clearScreen();
  printf("▁ ▂ ▄ ▅ ▆ ▇ █ Jouer une partie prédéfinie █ ▇ ▆ ▅ ▄ ▂ ▁\n\n");
  printf("Entrer le nom du fichier correspondant à la partie > ");
  scanf("%s", gameName);
  gameFile = fopen(gameName, "rb");
  if (gameFile == NULL){
    printf("[ERREUR] Fichier introuvable\n");
    return;
  }
  printf("Enter le pseudo du joueur > ");
  scanf("%s", playerName);
  printf("\n[CONTEXTE] Vous arrivez dans un corridor, bordé par deux falaises des monstres arrivent les uns après les autres.\n");
  existingGame();
}

// Ajouter type de retour et paramètres
void existingGame(void)
{
    // Ajouter code
}

void createNewGameDisplay()
{
  char playerName[100];
  clearScreen();
  printf("▁ ▂ ▄ ▅ ▆ ▇ █ Créer une nouvelle partie █ ▇ ▆ ▅ ▄ ▂ ▁\n\n");
  printf("Entrer votre pseudo > ");
  scanf("%s", playerName);
  createNewGame();
}

// Ajouter type de retour et paramètres
void createNewGame(void)
{
    // Ajouter code
}

void global(void){
  Boolean quit = False;
  int choice;
  while(!quit){
    clearScreen();
    printf("\n\t▁ ▂ ▄ ▅ ▆ ▇ █  MENU  █ ▇ ▆ ▅ ▄ ▂ ▁\n\n\n");
    printf("[1] Jouer une partie prédéfinie\n");
    printf("[2] Créer une nouvelle partie\n");
    printf("[3] Afficher la liste des joueurs triée par nom\n");
    printf("[4] Afficher la liste des joueurs triée par meilleur score\n");
    printf("[9] Quitter\n\n");
    printf("Votre choix > ");
    scanf("%d", &choice);
    switch(choice){
      case 1:
        existingGameDisplay();
        break;
      case 2:
        createNewGameDisplay();
        break;
      case 3:
        printf("Afficher la liste des joueurs triée par nom\n");
        break;
      case 4:
        printf("Afficher la liste des joueurs triée par meilleur score\n");
        break;
      case 9:
        printf("Au revoir...\n");
        quit = True;
        break;
      default:
        printf("Choix invalide\n");
        break;
    }
  }
}

void clearScreen(void)
{
    for (int i = 0; i < 50; i++) {
        printf("\n");
    }
}