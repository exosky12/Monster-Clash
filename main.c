#include "main.h"

void global(void){
  bool quit = False;
  int choix;
  while(!quit){
    printf("▁ ▂ ▄ ▅ ▆ ▇ █  MENU  █ ▇ ▆ ▅ ▄ ▂ ▁\n");
    printf("\t1. jouer une partie prédéfinie\n");
    printf("\t2. créer une nouvelle partie\n");
    printf("\t3. afficher la liste des joueurs triée par nom\n");
    printf("\t4. afficher la liste des joueurs triée par meilleur score\n");
    printf("\t9. quitter\n");
    printf("------------------------\n");
    printf("Votre choix : ");
    scanf("%d", &choix);
    switch(choix){
      case 1:
        printf("Jouer une partie prédéfinie\n");
        break;
      case 2:
        printf("Créer une nouvelle partie\n");
        break;
      case 3:
        printf("Afficher la liste des joueurs triée par nom\n");
        break;
      case 4:
        printf("Afficher la liste des joueurs triée par meilleur score\n");
        break;
      case 9:
        quit = True;
        break;
      default:
        printf("Choix invalide\n");
        break;
    }
  }
}