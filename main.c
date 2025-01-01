#include "main.h"

Heap heapEmpty(void)
{
    return NULL;
}

Heap add(Heap f, int x)
{
    Node *m;
    m = (Node *)malloc(sizeof(Node));

    if (m == NULL)
    {
        printf("Pb malloc!");
        exit(1);
    }

    m->v = x;

    if (f == NULL)
    {
        m->suiv = m;
        return m;
    }

    m->suiv = f->suiv;
    f->suiv = m;
    return m;
}

Heap deleteHead(Heap f)
{
    Node *aux;
    if (f == NULL)
    {
        printf("pb opération interdite !");
        exit(1);
    }
    if (f == f->suiv)
    {
        free(f);
        return heapEmpty();
    }

    aux = f->suiv;
    f->suiv = f->suiv->suiv;
    free(aux);
    return f;
}

Boolean isEmpty(Heap f)
{
    return f == NULL;
}

int head(Heap f)
{
    if (isEmpty(f))
    {
        printf("pbm Heap vide");
        exit(1);
    }
    return f->suiv->v;
}

void display(Heap f)
{
    Node *m;

    if (f == NULL)
        return;
    m = f->suiv;

    while (m != f)
    {
        printf("%d", m->v);
        m = m->suiv;
    }
    printf("%d\n", m->v);
}

int length(Heap f)
{
    int i = 0;
    Node *m;
    m = f->suiv;
    while (m != f)
    {
        i++;
        m = m->suiv;
    }
    i++;
    return i;
}

void existingGameDisplay(Player **playersTab, int *nbPlayers)
{
    //
    // Ici beaucoup en commentaire car c'était pour tester si l'ajout et la sauvegarde de nouveau fonctionnait
    //
    
    //FILE *gameHeap;
    char gameName[100], playerName[100];
    int trouve, index;
    clearScreen();
    printf("▁ ▂ ▄ ▅ ▆ ▇ █ Jouer une partie prédéfinie █ ▇ ▆ ▅ ▄ ▂ ▁\n\n");
    //printf("Entrer le nom du fichier correspondant à la partie > ");
    //scanf("%s", gameName);
    //gameHeap = fopen(gameName, "rb");
    //if (gameHeap == NULL)
    //{
    //    printf("[ERREUR] Fichier introuvable\n");
    //    return;
    //}
    printf("Enter le pseudo du joueur > ");
    scanf("%s", playerName);
    // vérifier si le joueur est dans la liste des joueurs
    index = dichotomousSearch(playerName, *playersTab, *nbPlayers, &trouve);
    if (trouve == 0)
    {
        // charger les données du joueur
        Player player;
        strcpy(player.nickname, playerName);

        int nbPv;
        printf("Entrer le nombre de points de vie de votre joueur > ");
        scanf("%*c %d%*c", &nbPv);

        player.nbPv = nbPv;
        player.nbDamages = 0;
        player.nbGames = 0;
        player.scores = NULL;
        strcpy(player.weapons, "PFC");

        // realloc playersTab
        *nbPlayers = *nbPlayers + 1;
        *playersTab = (Player *)realloc(*playersTab, (*nbPlayers) * sizeof(Player));
        if(playersTab == NULL)
        {
            printf("Erreur d'allocation mémoire\n");
            return;
        }

        (*playersTab)[*nbPlayers - 1] = player;
    }

    //printf("\n[CONTEXTE] Vous arrivez dans un corridor, bordé par deux falaises des monstres arrivent les uns après les autres.\n");
    //game();
}

int dichotomousSearch(char playerName[50], Player playersTab[100], int nbPlayers, int *trouve)
{
    int start = 0, end = nbPlayers - 1;
    int m;
    while (start <= end)
    {
        m = (start + end) / 2;
        if (strcmp(playerName, playersTab[m].nickname) == 0)
        {
            *trouve = 1;
            return m;
        }
        if (strcmp(playerName, playersTab[m].nickname) < 0)
        {
            end = m - 1;
        }
        else
        {
            start = m + 1;
        }
    }
    *trouve = 0;
    return start;
}

// Ajouter type de retour et paramètres
void game(void)
{
    // Ajouter code
}

void createNewGameDisplay()
{
    char nickname[50];
    clearScreen();
    printf("▁ ▂ ▄ ▅ ▆ ▇ █ Créer une nouvelle partie █ ▇ ▆ ▅ ▄ ▂ ▁\n\n");
    printf("Entrer votre pseudo > ");
    scanf("%s", nickname);
    // createNewGame(nickname, playersTab);
}


char determineWinner(char weaponPlayer, char weaponMonster)
{
    if (weaponPlayer == weaponMonster)
    {
        return 'D';
    }
    if (weaponPlayer == '#')
    {
        return 'P';
    }
    if (weaponMonster == '#')
    {
        return 'M';
    }
    if (weaponPlayer == 'O')
    {
        return 'M';
    }
    if (weaponMonster == 'O')
    {
        return 'P';
    }
    if (weaponPlayer == 'P' && weaponMonster == 'C')
    {
        return 'P';
    }
    if (weaponPlayer == 'C' && weaponMonster == 'F')
    {
        return 'P';
    }
    if (weaponPlayer == 'F' && weaponMonster == 'P')
    {
        return 'P';
    }
    if (weaponMonster == 'P' && weaponPlayer == 'C')
    {
        return 'M';
    }
    if (weaponMonster == 'C' && weaponPlayer == 'F')
    {
        return 'M';
    }
    if (weaponMonster == 'F' && weaponPlayer == 'P')
    {
        return 'M';
    }
    return 'D';
}

Player *loadPlayers(int *nbPlayers)
{
    Player *playersTab;

    // charger nbPlayers

    playersTab = (Player*)malloc(*nbPlayers * sizeof(Player));
    return playersTab;
}

Monster* loadMonsters(char *filename, int *nbMonsters) 
{
    FILE *file = fopen(filename, "r");
    if (file == NULL) 
    {
        printf("Erreur lors de l'ouverture du fichier\n");
        return NULL;
    }

    // Lecture du nombre de monstres (première ligne)
    fscanf(file, "%d", nbMonsters);

    if (*nbMonsters < 1) 
    {
        printf("Erreur lors de la lecture du nombre de monstres\n");
        fclose(file);
        return NULL;
    }

    // Allocation dynamique pour le tableau des monstres
    Monster *monsters = malloc(*nbMonsters * sizeof(Monster));
    if (monsters == NULL) 
    {
        printf("Erreur d'allocation mémoire\n");
        fclose(file);
        return NULL;
    }

    // Lecture des monstres
    for (int i = 0; i < *nbMonsters; i++) 
    {
        Monster *monster = &monsters[i];
        int j = 0;
        char c;
        
        // Lecture du nom du monstre
        fscanf(file," %c",&c);
        while(c != ',')
        {
            // Vérification de la taille du nom
            if(j >= 50)
            {
                printf("Erreur lors de la lecture du nom du monstre\n");
                fclose(file);
                return NULL;
            }
            monster->name[j] = c;
            j++;
            fscanf(file,"%c",&c);
        }
        // Ajout du caractère de fin de chaîne
        monster->name[j] = '\0';

        // Vérification de la lecture du nom
        if(j == 0)
        {
            printf("Erreur lors de la lecture du nom du monstre\n");
            fclose(file);
            return NULL;
        }

        fscanf(file, "%d,%d,%d",
                   &monster->level,
                   &monster->pv,
                   &monster->damage);

        // Allocation dynamique pour les armes du monstre
        switch (monster->level) 
        {
            case 1:
                monster->nbWeapons = 4;
                monster->weapons = malloc(monster->nbWeapons * sizeof(char));

                monster->weapons = "PFCO";
                break;
            case 2:
                monster->nbWeapons = 3;
                monster->weapons = malloc(monster->nbWeapons * sizeof(char));

                monster->weapons = "PFC";
                break;
            case 3:
                monster->nbWeapons = 5;
                monster->weapons = malloc(monster->nbWeapons * sizeof(char));

                monster->weapons = "PFCO#";
                break;
            default:
                printf("Niveau de monstre invalide\n");
                fclose(file);
                return NULL;
        }
    }
    fclose(file);
    return monsters;
}

/*
//Fonction de test pour afficher les monstres chargés depuis le fichier

void showEveryMonsters(Monster *monsters, int nbMonsters)
{
    for (int i = 0; i < nbMonsters; i++)
    {
        printf("Nom : %s\n", monsters[i].name);
        printf("Niveau : %d\n", monsters[i].level);
        printf("Points de vie : %d\n", monsters[i].pv);
        printf("Dégâts : %d\n", monsters[i].damage);
        printf("Nombre d'armes : %d\n", monsters[i].nbWeapons);
        printf("Armes : ");
        for (int j = 0; j < monsters[i].nbWeapons; j++)
            printf("%c ", monsters[i].weapons[j]);
        printf("\n\n");
    }
}
*/

// Fonction pour charger les joueurs depuis un fichier binaire
Player* loadPlayersFromBinary(char *filename, int *nbPlayers) 
{
    // Ouvre le fichier binaire en mode lecture
    FILE *file = fopen(filename, "rb");

    // Vérification de l'ouverture du fichier
    if (file == NULL) 
    {
        clearScreen();
        printf("Fichier de sauvegarde non crée ou non ouvrable\n\n");
        fclose(file);

        // Variable pour la sauvegarde du choix de l'utilisateur
        char choice;

        // Demande à l'utilisateur s'il veut créer un nouveau fichier
        printf("Voulez-vous créer un nouveau fichier de sauvegarde ? (O/n) > ");

        // Lecture du choix de l'utilisateur
        scanf(" %c", &choice);

        // Si l'utilisateur ne veut pas créer de fichier, on retourne NULL
        if (choice == 'n' || choice == 'N') 
        {
            return NULL;
        }
        
        // Sinon on crée un nouveau fichier
        file = fopen(filename, "wb");
        if (file == NULL) 
        {
            printf("Erreur lors de la création du fichier\n");
            return NULL;
        }

        // On écrit le nombre de joueurs (0) dans le fichier
        *nbPlayers = 0;
        fwrite(nbPlayers, sizeof(int), 1, file);

        // On ferme le fichier
        fclose(file);

        return NULL;
    }

    // Lecture du nombre de joueurs
    fread(nbPlayers, sizeof(int), 1, file);

    // Vérification de la lecture du nombre de joueurs
    if(*nbPlayers < 0) 
    {
        printf("Erreur lors de la lecture du nombre de joueurs\n");
        fclose(file);
        return NULL;
    }

    // Allocation dynamique pour le tableau des joueurs
    Player *players = malloc(*nbPlayers * sizeof(Player));
    if (players == NULL) 
    {
        printf("Erreur d'allocation mémoire\n");
        fclose(file);
        return NULL;
    }

    // Lecture des données de chaque joueur
    for (int i = 0; i < *nbPlayers; i++) 
    {
        Player *player = &players[i];

        // Lecture du pseudo
        fread(player->nickname, sizeof(char), 50, file);

        // Lecture des caractéristiques simples
        fread(&player->nbPv, sizeof(int), 1, file);
        fread(&player->nbDamages, sizeof(int), 1, file);
        fread(&player->nbGames, sizeof(int), 1, file);
        

        // Allocation dynamique pour les scores
        player->scores = malloc(player->nbGames * sizeof(int));

        // Vérification de l'allocation
        if (player->scores == NULL) 
        {
            printf("Erreur d'allocation mémoire pour les scores\n");
            fclose(file);
            return NULL;
        }

        // Lecture des scores
        fread(player->scores, sizeof(int), player->nbGames, file);

        // Lecture des armes
        fread(player->weapons, sizeof(char), 5, file);
    }
    fclose(file);
    return players;
}

void savePlayersToBinary(char *filename, Player *players, int nbPlayers) 
{
    // Ouvre le fichier binaire en mode écriture
    FILE *file = fopen(filename, "wb");
    if (file == NULL) 
    {
        printf("Erreur lors de l'ouverture du fichier\n");
        return;
    }

    // Écrit le nombre de joueurs en premier
    fwrite(&nbPlayers, sizeof(int), 1, file);

    // Parcourt chaque joueur et écrit ses données
    for (int i = 0; i < nbPlayers; i++) 
    {
        Player *player = &players[i];

        // Écrit le pseudo
        fwrite(player->nickname, sizeof(char), 50, file);

        // Écrit les caractéristiques simples
        fwrite(&player->nbPv, sizeof(int), 1, file);
        fwrite(&player->nbDamages, sizeof(int), 1, file);
        fwrite(&player->nbGames, sizeof(int), 1, file);

        // Écrit les scores
        fwrite(player->scores, sizeof(int), player->nbGames, file);

        // Écrit les armes
        fwrite(player->weapons, sizeof(char), 5, file);
    }
    fclose(file);
}

/*
//Fonction de test pour afficher les joueurs chargés

void showEveryPlayers(Player *players, int nbPlayers)
{
    for (int i = 0; i < nbPlayers; i++)
    {
        printf("Pseudo : %s\n", players[i].nickname);
        printf("Points de vie : %d\n", players[i].nbPv);
        printf("Dégâts : %d\n", players[i].nbDamages);
        printf("Nombre de jeux : %d\n", players[i].nbGames);
        printf("Scores : ");
        for (int j = 0; j < players[i].nbGames; j++)
            printf("%d ", players[i].scores[j]);
        printf("\n");
        printf("Armes : %s\n\n", players[i].weapons);
    }
}
*/

void global(void)
{
    Boolean quit = False;
    int choice, nbPlayers, nbMonsters;
    Player *playerTab = loadPlayersFromBinary("game.dat", &nbPlayers);
    Monster *monsters = loadMonsters("monsters.txt", &nbMonsters);

    while (!quit)
    {
        clearScreen();
        printf("\n\t▁ ▂ ▄ ▅ ▆ ▇ █  MENU  █ ▇ ▆ ▅ ▄ ▂ ▁\n\n\n");
        printf("[1] Jouer une partie prédéfinie\n");
        printf("[2] Créer une nouvelle partie\n");
        printf("[3] Afficher la liste des joueurs triée par nom\n");
        printf("[4] Afficher la liste des joueurs triée par meilleur score\n");
        printf("[9] Quitter et sauvegarder\n\n");
        printf("Votre choix > ");
        //showEveryMonsters(monsters, nbMonsters);
        //showEveryPlayers(playerTab, nbPlayers);
        //printf("Nombre de joueurs : %d\n", nbPlayers);
        scanf(" %d", &choice);
        switch (choice)
        {
        case 1:
            existingGameDisplay(&playerTab,&nbPlayers);
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
    savePlayersToBinary("game.dat", playerTab, nbPlayers);
}

void clearScreen(void)
{
    for (int i = 0; i < 50; i++)
    {
        printf("\n");
    }
}
