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

    // FILE *gameHeap;
    char playerName[100];
    int trouve, index;
    clearScreen();
    printf("▁ ▂ ▄ ▅ ▆ ▇ █ Jouer une partie prédéfinie █ ▇ ▆ ▅ ▄ ▂ ▁\n\n");
    // printf("Entrer le nom du fichier correspondant à la partie > ");
    // scanf("%s", gameName);
    // gameHeap = fopen(gameName, "rb");
    // if (gameHeap == NULL)
    //{
    //     printf("[ERREUR] Fichier introuvable\n");
    //     return;
    // }
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
        if (playersTab == NULL)
        {
            printf("Erreur d'allocation mémoire\n");
            return;
        }

        (*playersTab)[*nbPlayers - 1] = player;
    }

    // game();
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
void game(Player player, Player playersTab[100], Monster monstersTab[100], int nbMonstersGroup)
{
    printf("\n[CONTEXTE] Vous arrivez dans un corridor, bordé par deux falaises des monstres arrivent les uns après les autres.\n");
    int counterGroup1 = 0;
    Monster currentMonsterGroup1 = monstersTab[counterGroup1];
    int playerPoints = 0;
    while (nbMonstersGroup > 0)
    {
        int currentMonsterGroup1Pv = monstersTab[counterGroup1].pv;
        char currentMonsterGroup1Name[50];
        strcpy(currentMonsterGroup1Name, monstersTab[counterGroup1].name);
        int currentMonsterGroup1Damage = monstersTab[counterGroup1].damage;
        int currentMonsterGroup1Level = monstersTab[counterGroup1].level;

        printf("[INFO] Le monstre %s(%dptV, %dAtt) accoure et se prépare à t'attaquer %s(%dptV, %dAtt)\n", currentMonsterGroup1Name, currentMonsterGroup1Pv, currentMonsterGroup1Damage, player.nickname, player.nbPv, player.nbDamages);

        while (currentMonsterGroup1Pv > 0)
        {
            int nbWeapons = strlen(player.weapons);
            printf("%s(%dPts) choisis ton arme parmi", player.nickname, playerPoints);
            for (int i = 0; i < nbWeapons; i++)
            {
                printf(" %c", player.weapons[i]);
            }
            printf("> ");

            char weaponChoosen;
            scanf(" %c", &weaponChoosen);

            int monsterWeaponIndex = rand() % monstersTab[counterGroup1].nbWeapons;
            char monsterWeapon = monstersTab[counterGroup1].weapons[monsterWeaponIndex];

            printf("[INFO] %s(%c) attaque %s(%c)\n\n", player.nickname, weaponChoosen, currentMonsterGroup1Name, monsterWeapon);

            char winner = determineWinner(weaponChoosen, monsterWeapon);

            switch (winner)
            {
            case 'P':
            {
                currentMonsterGroup1Pv -= player.nbDamages;
                int winningPoints = 10;
                if (currentMonsterGroup1Pv <= 0)
                {
                    currentMonsterGroup1Pv = 0;
                    winningPoints = 50 * currentMonsterGroup1Level;
                    printf("\t[VICTOIRE] %s(%dptV) gagne contre %s(%dptV)\t\t+%dpts\n\n", player.nickname, player.nbPv, currentMonsterGroup1Name, currentMonsterGroup1Pv, winningPoints);
                    printf("\t[INFO] %s meurt sous le coup de l'attaque\t\t+%dpts\n\n", currentMonsterGroup1Name, winningPoints);
                }
                else
                {
                    playerPoints += winningPoints;
                    printf("\t[VICTOIRE] %s(%dptV) gagne contre %s(%dptV)\t\t+%dpts\n\n", player.nickname, player.nbPv, currentMonsterGroup1Name, currentMonsterGroup1Pv, winningPoints);
                }
                break;
            }
            case 'M':
            {
                player.nbPv -= currentMonsterGroup1Damage;
                if (player.nbPv <= 0)
                {
                    player.nbPv = 0;
                    printf("\t[DEFAITE] %s(%dptV) perd contre %s(%dptV)\n\n", player.nickname, player.nbPv, currentMonsterGroup1Name, currentMonsterGroup1Pv);
                    printf("[INFO] PERDU... Nombre de points acquis : %d\n\n", playerPoints);
                    return;
                }
                printf("\t[DEFAITE] %s(%dptV) perd contre %s(%dptV)\n", player.nickname, player.nbPv, currentMonsterGroup1Name, currentMonsterGroup1Pv);
                break;
            }
            case 'D':
            {
                printf("\t[EGALITE] Aucun de %s(%dptV) et %s(%dptV) ne gagne l'attaque\n\n", player.nickname, player.nbPv, currentMonsterGroup1Name, currentMonsterGroup1Pv);
                break;
            }
            }
        }
        nbMonstersGroup--;
        counterGroup1++;
    }
    printf("[INFO] Tous les monstres sont morts...\n\n");
    printf("[CONTEXTE] vous arrivez au bout du corridor, une plaine herbeuse apparaît. Malheureusement des monstres sortent de partout pour tous vous attaquer en même temps ou presque...");
    MonstersGroup group2;
    group2.monsters = monstersTab;
    group2.nbMonsters = nbMonstersGroup;
    group2.type = 2;
    Heap heap = heapEmpty();
    for (int i = 0; i < group2.nbMonsters; i++)
    {
        heap = add(heap, i);
    }
    while (length(heap) > 0)
    {
        int currentMonsterIndex = head(heap);
        printf("[INFO] Le monstre %s(%dptV, %dAtt) s'avance pour vous attaquer %s(%dptV, %dAtt)\n", group2.monsters[currentMonsterIndex].name, group2.monsters[currentMonsterIndex].pv, group2.monsters[currentMonsterIndex].damage, player.nickname, player.nbPv, player.nbDamages);
        int nbWeapons = strlen(player.weapons);
        printf("%s(%dPts) choisis ton arme parmi", player.nickname, playerPoints);
        for (int i = 0; i < nbWeapons; i++)
        {
            printf(" %c", player.weapons[i]);
        }
        printf("> ");

        char weaponChoosen;
        scanf(" %c", &weaponChoosen);

        int monsterWeaponIndex = rand() % group2.monsters[currentMonsterIndex].nbWeapons;
        char monsterWeapon = group2.monsters[currentMonsterIndex].weapons[monsterWeaponIndex];

        printf("[INFO] %s(%c) attaque %s(%c)\n", player.nickname, weaponChoosen, group2.monsters[currentMonsterIndex].name, monsterWeapon);

        char winner = determineWinner(weaponChoosen, monsterWeapon);

        switch (winner)
        {
        case 'P':
        {
            group2.monsters[currentMonsterIndex].pv -= player.nbDamages;
            int winningPoints = 10;
            if (group2.monsters[currentMonsterIndex].pv <= 0)
            {
                group2.monsters[currentMonsterIndex].pv = 0;
                winningPoints = 50 * group2.monsters[currentMonsterIndex].level;
                printf("\t[VICTOIRE] %s(%dptV) gagne contre %s(%dptV)\t\t+%dpts\n", player.nickname, player.nbPv, group2.monsters[currentMonsterIndex].name, group2.monsters[currentMonsterIndex].pv, winningPoints);
                printf("\t[INFO] %s meurt sous le coup de l'attaque\t\t+%dpts\n\n", group2.monsters[currentMonsterIndex].name, winningPoints);
            }
            else
            {
                playerPoints += winningPoints;
                printf("\t[VICTOIRE] %s(%dptV) gagne contre %s(%dptV)\t\t+%dpts\n", player.nickname, player.nbPv, group2.monsters[currentMonsterIndex].name, group2.monsters[currentMonsterIndex].pv, winningPoints);
            }
            break;
        }
        case 'M':
        {
            player.nbPv -= group2.monsters[currentMonsterIndex].damage;
            if (player.nbPv <= 0)
            {
                player.nbPv = 0;
                printf("\t[DEFAITE] %s(%dptV) perd l'attaque contre %s(%dptV)\n", player.nickname, player.nbPv, group2.monsters[currentMonsterIndex].name, group2.monsters[currentMonsterIndex].pv);
                printf("[INFO] PERDU... Nombre de points acquis : %d\n", playerPoints);
                return;
            }
            printf("\t[DEFAITE] %s(%dptV) perd contre %s(%dptV)\n", player.nickname, player.nbPv, group2.monsters[currentMonsterIndex].name, group2.monsters[currentMonsterIndex].pv);
            break;
        }
        case 'D':
        {
            printf("\t[EGALITE] Aucun de %s(%dptV) et %s(%dptV) ne gagne l'attaque\n", player.nickname, player.nbPv, group2.monsters[currentMonsterIndex].name, group2.monsters[currentMonsterIndex].pv);
            break;
        }
        }
    }
}

void createNewGameDisplay(int *nbPlayers, Player **playersTab, Monster monstersTab[100], int nbMonstersGroup)
{
    char playerName[50];
    clearScreen();
    int index, trouve;
    printf("▁ ▂ ▄ ▅ ▆ ▇ █ Créer une nouvelle partie █ ▇ ▆ ▅ ▄ ▂ ▁\n\n");
    printf("Entrer votre pseudo > ");
    scanf("%s", playerName);
    index = dichotomousSearch(playerName, *playersTab, *nbPlayers, &trouve);
    if (trouve == 0)
    {
        // charger les données du joueur
        Player player;
        strcpy(player.nickname, playerName);
        player.nbPv = 20;
        player.nbDamages = 1;
        player.nbGames = 0;
        player.scores = NULL;
        strcpy(player.weapons, "PFC");

        // realloc playersTab
        *nbPlayers = *nbPlayers + 1;
        *playersTab = (Player *)realloc(*playersTab, (*nbPlayers) * sizeof(Player));
        if (playersTab == NULL)
        {
            printf("Erreur d'allocation mémoire\n");
            return;
        }

        (*playersTab)[*nbPlayers - 1] = player;
    }
    Player player = *playersTab[index];
    game(player, playersTab, monstersTab, nbMonstersGroup);
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

Monster *loadMonsters(char *filename, int *nbMonsters)
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
        fscanf(file, " %c", &c);
        while (c != ',')
        {
            // Vérification de la taille du nom
            if (j >= 50)
            {
                printf("Erreur lors de la lecture du nom du monstre\n");
                fclose(file);
                return NULL;
            }
            monster->name[j] = c;
            j++;
            fscanf(file, "%c", &c);
        }
        // Ajout du caractère de fin de chaîne
        monster->name[j] = '\0';

        // Vérification de la lecture du nom
        if (j == 0)
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
Player *loadPlayersFromBinary(char *filename, int *nbPlayers)
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
    if (*nbPlayers < 0)
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

void showPlayers(Player *players, int nbPlayers)
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

void switchPlayers(Player *playersTab[], int i, int j)
{
    Player *temp = playersTab[i];
    playersTab[i] = playersTab[j];
    playersTab[j] = temp;
}

void sortPlayers(Player *playersTab[], int nbPlayers, char sortType)
{
    if (sortType == 'N')
    {
        for (int i = 0; i < nbPlayers - 1; i++)
        {
            for (int j = i + 1; j < nbPlayers; j++)
            {
                if (strcmp(playersTab[i]->nickname, playersTab[j]->nickname) > 0)
                {
                    switchPlayers(playersTab, i, j);
                }
            }
        }
    }
    else if (sortType == 'S')
    {
        while (nbPlayers > 1)
        {
            int max = biggestScore(playersTab, nbPlayers);
            switchPlayers(playersTab, max, nbPlayers - 1);
            nbPlayers--;
        }
    }
    else
    {
        printf("Type de tri invalide\n");
    }
}

int biggestScore(Player *PlayersTab[], int nbPlayers)
{
    int max = 0;
    for (int i = 1; i < nbPlayers; i++)
    {
        if (PlayersTab[i]->scores > PlayersTab[max]->scores)
        {
            max = i;
        }
    }
    return max;
}

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
        // showEveryMonsters(monsters, nbMonsters);
        showPlayers(playerTab, nbPlayers);
        // printf("Nombre de joueurs : %d\n", nbPlayers);
        scanf(" %d", &choice);
        switch (choice)
        {
        case 1:
            existingGameDisplay(&playerTab, &nbPlayers);
            break;
        case 2:
            createNewGameDisplay(&nbPlayers, &playerTab, monsters, nbMonsters);
            break;
        case 3:
            sortPlayers(&playerTab, nbPlayers, 'N');
            showPlayers(playerTab, nbPlayers);
            break;
        case 4:
            sortPlayers(&playerTab, nbPlayers, 'S');
            showPlayers(playerTab, nbPlayers);
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
