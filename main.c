#include "main.h"

File FileVide(void)
{
    return NULL;
}

File adjq(File f, int x)
{
    Maillon2 *m;
    m=(Maillon2*)malloc(sizeof(Maillon2));

    if(m==NULL)
    {
        printf("Pb malloc!");
        exit(1);
    } 

    m->v=x;

    if(f==NULL)
    {
        m->suiv=m;
        return m;
    }

    m->suiv = f->suiv;
    f->suiv=m;
    return m;
}

File supprimerEnTete(File f)
{
    Maillon2 *aux;
    if(f==NULL)
    {
        printf("pb opération interdite !");
        exit(1);
    }
    if(f==f->suiv)
    {
        free(f);
        return FileVide();
    }

    aux = f->suiv;
    f->suiv = f-> suiv->suiv;
    free(aux);
    return f;
}

Boolean estVide2(File f)
{
    return f==NULL;
}

int tete2(File f)
{
    if(estVide2(f))
    {
        printf("pbm file vide");
        exit(1);
    }
    return f->suiv->v;
}

void affiche(File f)
{
    Maillon2 *m;

    if(f==NULL)
        return;
    m=f->suiv;

    while(m != f)
    {
        printf("%d",m->v);
        m=m->suiv;
    } 
    printf("%d\n",m->v);
}

int longueur2(File f)
{
    int i = 0;
    Maillon2 *m;
    m = f->suiv;
    while(m != f)
    {
        i++;
        m = m->suiv;
    }
    i++;
    return i;
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