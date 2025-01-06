
#include "main.h"

File fileVide(void)
{
    return NULL;
}

File ajouter(File f, int x)
{
    Maillon *m;
    m = (Maillon *)malloc(sizeof(Maillon));

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

File supprimerTete(File f)
{
    Maillon *aux;
    if (f == NULL)
    {
        printf("pb opération interdite !");
        exit(1);
    }
    if (f == f->suiv)
    {
        free(f);
        return fileVide();
    }

    aux = f->suiv;
    f->suiv = f->suiv->suiv;
    free(aux);
    return f;
}

Boolean estVide(File f)
{
    return f == NULL;
}

int tete(File f)
{
    if (estVide(f))
    {
        printf("pbm File vide");
        exit(1);
    }
    return f->suiv->v;
}

void afficher(File f)
{
    Maillon *m;

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

int longueur(File f)
{
    int i = 0;
    Maillon *m;
    m = f->suiv;
    while (m != f)
    {
        i++;
        m = m->suiv;
    }
    i++;
    return i;
}

/*
void existingGameDisplay(Joueur **joueursTab, int *nbJoueurs, Monstre monstresTab[],  , int nbMonstresGroupe1)
{
    clearScreen();
    printf(GRAS VERT "▁ ▂ ▄ ▅ ▆ ▇ █ Jouer une partie prédéfinie █ ▇ ▆ ▅ ▄ ▂ ▁\n\n" RESET);

    // Demander le nom du fichier
    char filenom[100];
    printf("Entrez le nom du fichier > ");
    scanf("%s", filenom);
    if (filenom == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier\n");
        return;
    }

    // Charger les joueurs à partir du fichier binaire
    Joueur *loadedJoueurs = loadJoueursFromBinary(filenom, nbJoueurs);

    if (loadedJoueurs == NULL)
    {
        printf(BLEU "[ℹ️  INFO] Aucun joueur n'a été chargé ou le fichier est inexistant.\n" RESET);
        return;
    }

    // Mettre à jour le tableau dynamique des joueurs
    *joueursTab = loadedJoueurs;

    // Demander le pseudo du joueur
    char pseudoJoueur[50];
    printf("Entrez le pseudo du joueur > ");
    scanf("%s", pseudoJoueur);

    // Recherche du joueur dans le tableau
    int trouve;
    int index = rechercheDico(pseudoJoueur, *joueursTab, *nbJoueurs, &trouve);

    if (trouve == 0)
    {
        printf("Joueur non trouvé, création du joueur...\n");
        Joueur newJoueur;
        strcpy(newJoueur.pseudo, pseudoJoueur);
        newJoueur.nbPv = 20;
        newJoueur.nbDegats = 1;
        newJoueur.nbParties = 0;
        newJoueur.scores = NULL;
        strcpy(newJoueur.armes, "PFC");

        *nbJoueurs = *nbJoueurs + 1;
        *joueursTab = (Joueur *)realloc(*joueursTab, (*nbJoueurs) * sizeof(Joueur));
        if (*joueursTab == NULL)
        {
            printf("Erreur d'allocation mémoire\n");
            return;
        }

        (*joueursTab)[*nbJoueurs - 1] = newJoueur;
        index = *nbJoueurs - 1;
    }

    Joueur joueur = (*joueursTab)[index];
    showAllJoueurs(*joueursTab, *nbJoueurs);
    printf("\nDémarrage de la partie pour le joueur %s...\n", pseudoJoueur);
    game(joueur, *joueursTab, monstresTab, nbMonstresGroupe1);

    // Libérer la mémoire allouée pour les scores
    free(joueur.scores);
}
*/

int rechercheDico(char pseudoJoueur[50], Joueur joueursTab[], int nbJoueurs, int *trouve)
{
    int inf = 0, sup = nbJoueurs - 1;
    int m;
    while (inf <= sup)
    {
        m = (inf + sup) / 2;
        if (strcmp(pseudoJoueur, joueursTab[m].pseudo) == 0)
        {
            *trouve = 1;
            return m;
        }
        if (strcmp(pseudoJoueur, joueursTab[m].pseudo) < 0)
        {
            sup = m - 1;
        }
        else
        {
            inf = m + 1;
        }
    }
    *trouve = 0;
    return inf;
}

void showAllbybiggestScoresRecursive(Joueur *JoueursTab[], int currentIndex, int maxIndex, int nbJoueurs)
{
    if (currentIndex == nbJoueurs)
    {
        printf("Pseudo : %s\n", JoueursTab[maxIndex]->pseudo);
        printf("Points de vie : %d\n", JoueursTab[maxIndex]->nbPv);
        printf("Dégâts : %d\n", JoueursTab[maxIndex]->nbDegats);
        printf("Nombre de jeux : %d\n", JoueursTab[maxIndex]->nbParties);
        printf("Scores : ");
        for (int j = 0; j < JoueursTab[maxIndex]->nbParties; j++)
            printf("%d ", JoueursTab[maxIndex]->scores[j]);
        printf("\n");
        printf("Armes : %s\n\n", JoueursTab[maxIndex]->armes);
        return;
    }

    if (JoueursTab[currentIndex]->scores > JoueursTab[maxIndex]->scores)
    {
        maxIndex = currentIndex;
    }

    showAllbybiggestScoresRecursive(JoueursTab, currentIndex + 1, maxIndex, nbJoueurs);
}

void showAllbybiggestScores(Joueur *JoueursTab[], int nbJoueurs)
{
    showAllbybiggestScoresRecursive(JoueursTab, 1, 0, nbJoueurs);
}

// Ajouter type de retour et paramètres
void gameGroupe1(Joueur joueur, Joueur joueursTab[], Monstre monstresTab[], int indexMonstresTab[], int nbMonstres)
{
    printf("\n[CONTEXTE] Vous arrivez dans un corridor, bordé par deux falaises des monstres arrivent les uns après les autres.\n\n");

    // Points du joueur (par défaut à 0)
    int pointsJoueur = 0;

    // Tant qu'il y a des monstres dans le groupe 1
    while (nbMonstres > 0)
    {
        // index qui permet de parcourir les monstres
        int index = 0;

        // Monstre actuel
        Monstre montreActuel = monstresTab[indexMonstresTab[index]];

        printf(BLEU "[INFO] Le monstre %s(%dptV, %dAtt) accoure et se prépare à t'attaquer %s(%dptV, %dAtt)\n\n" RESET, 
        montreActuel.nom, montreActuel.pv, montreActuel.degats, joueur.pseudo, joueur.nbPv, joueur.nbDegats);

        while (montreActuel.pv > 0)
        {
            printf(JAUNE "[ACTION] %s(%dPts) choisis ton arme parmi %s" RESET, joueur.pseudo, pointsJoueur, joueur.armes);
            printf("> ");

            // Arme choisie par le joueur
            char armeChoisie;
            scanf(" %c", &armeChoisie);

            // Vérification de l'arme choisie dans les armes disponibles
            while (strchr(joueur.armes, armeChoisie) == NULL)
            {
                printf(ROUGE "[ERREUR] Arme invalide, veuillez choisir une arme parmi %s\n" RESET, joueur.armes);
                printf("> ");
                scanf(" %c", &armeChoisie);
            }

            // Index de l'arm du monstre choisie aléatoirement
            int indexArmeMonstre = rand() % montreActuel.nbArmes;

            // Arme du monstre
            char armeMonstre = montreActuel.armes[indexArmeMonstre];

            printf(BLEU "[INFO] %s(%c) attaque %s(%c)\n\n" RESET, joueur.pseudo, armeChoisie, montreActuel.nom , armeMonstre);

            // Détermination du gagnant
            char gagnant = determinerGagnant(armeChoisie, armeMonstre);

            switch (gagnant)
            {
            // Si le joueur gagne
            case 'P':
            {
                // Réduction des points de vie du monstre
                montreActuel.pv -= joueur.nbDegats;

                // Points gagnés par le joueur
                int pointsGagnees = 10;

                // Si le monstre est mort
                if (montreActuel.pv <= 0)
                {
                    // On met les points du monstre mort vie à 0
                    montreActuel.pv = 0;

                    // Points gagnés par le joueur
                    pointsGagnees = 50 * montreActuel.niveau;

                    printf(VERT "\t[VICTOIRE] %s(%dptV) gagne contre %s(%dptV)\t\t+%dpts\n\n" RESET
                    ,joueur.pseudo, joueur.nbPv, montreActuel.nom, montreActuel.pv , pointsGagnees);
                    printf(BLEU "\t[INFO] %s meurt sous le coup de l'attaque\t\t+%dpts\n\n\n" RESET, montreActuel.nom, pointsGagnees);
                }
                else
                {
                    // Ajout des points gagnés par le joueur
                    pointsJoueur += pointsGagnees;

                    printf(VERT "\t[VICTOIRE] %s(%dptV) gagne contre %s(%dptV)\t\t+%dpts\n\n" RESET
                    ,joueur.pseudo, joueur.nbPv, montreActuel.nom, montreActuel.pv, pointsGagnees);
                }
                break;
            }
            // Si le monstre gagne
            case 'M':
            {
                // Réduction des points de vie du joueur
                joueur.nbPv -= montreActuel.degats;

                // Si le joueur est mort
                if (joueur.nbPv <= 0)
                {
                    // On met les points de vie du joueur à 0
                    joueur.nbPv = 0;

                    printf(ROUGE "\t[DEFAITE] %s(%dptV) perd contre %s(%dptV)\n\n" RESET
                    ,joueur.pseudo, joueur.nbPv, montreActuel.nom, montreActuel.pv);

                    printf(BLEU "[INFO] PERDU... Nombre de points acquis : %d\n\n" RESET, pointsJoueur);
                    return;
                }
                printf(ROUGE "\t[DEFAITE] %s(%dptV) perd contre %s(%dptV)\n\n" RESET,
                joueur.pseudo, joueur.nbPv, montreActuel.nom, montreActuel.pv);
                break;
            }
            // Si égalité
            case 'E':
            {
                printf(MAGENTA "\t[EGALITE] Aucun de %s(%dptV) et %s(%dptV) ne gagne l'attaque\n\n" RESET,
                joueur.pseudo, joueur.nbPv, montreActuel.nom, montreActuel.pv);
                break;
            }
            }
        }
        // Passage au monstre suivant
        nbMonstres--;
        index++;
    }
}

void gameGroupe2(Joueur joueur, Joueur joueursTab[], Monstre monstresTab[], int indexMonstresTab[], int nbMonstres)
{
    printf(BLEU "[INFO] Tous les monstres sont morts...\n\n" RESET);
    printf("[CONTEXTE] vous arrivez au bout du corridor, une plaine herbeuse apparaît. Malheureusement des monstres sortent de partout pour tous vous attaquer en même temps ou presque...\n\n");

    // Création de la file des monstres du groupe 2
    File file = fileVide();

    // Ajout des monstres du groupe 2 dans la file
    for (int i = 0; i < nbMonstres; i++)
    {
        file = ajouter(file, i);
    }

    // Tant qu'il reste des monstres dans la file
    while (longueur(file) > 0)
    {
        // Index du monstre actuel
        int montreActuelIndex = tete(file);

        printf(BLEU "[INFO] Le monstre %s(%dptV, %dAtt) s'avance pour vous attaquer %s(%dptV, %dAtt)\n" RESET, monstresTab[indexMonstresTabGroupe2[montreActuelIndex]].nom, monstresTab[indexMonstresTabGroupe2[montreActuelIndex]].pv, monstresTab[indexMonstresTabGroupe2[montreActuelIndex]].degats, joueur.pseudo, joueur.nbPv, joueur.nbDegats);

        // Nombre d'armes du joueur
        int nbArmes = strlen(joueur.armes);
        printf(JAUNE "[ACTION] %s(%dPts) choisis ton arme parmi" RESET, joueur.pseudo, pointsJoueur);

        // Affichage des armes disponibles
        for (int i = 0; i < nbArmes; i++)
        {
            printf(" %c", joueur.armes[i]);
        }
        printf("> ");

        // Arme choisie par le joueur
        char armeChoisie;
        scanf(" %c", &armeChoisie);

        // Index de l'arm du monstre choisie aléatoirement
        int indexArmeMonstre = rand() % monstresTab[indexMonstresTabGroupe2[montreActuelIndex]].nbArmes;

        // Arme du monstre
        char armeMonstre = monstresTab[indexMonstresTabGroupe2[montreActuelIndex]].armes[indexArmeMonstre];

        printf(BLEU "[INFO] %s(%c) attaque %s(%c)\n" RESET, joueur.pseudo, armeChoisie, monstresTab[indexMonstresTabGroupe2[montreActuelIndex]].nom, armeMonstre);

        // Détermination du gagnant
        char gagnant = determinerGagnant(armeChoisie, armeMonstre);

        switch (gagnant)
        {
        // Si le joueur gagne
        case 'P':
        {
            // Réduction des points de vie du monstre
            monstresTab[indexMonstresTabGroupe2[montreActuelIndex]].pv -= joueur.nbDegats;

            // Points gagnés par le joueur
            int pointsGagnees = 10;

            // Si le monstre est mort
            if (monstresTab[indexMonstresTabGroupe2[montreActuelIndex]].pv <= 0)
            {
                // On met les points du monstre mort vie à 0
                monstresTab[indexMonstresTabGroupe2[montreActuelIndex]].pv = 0;

                // Points gagnés par le joueur, 100 fois le niveau du monstre
                pointsGagnees = 100 * monstresTab[indexMonstresTabGroupe2[montreActuelIndex]].niveau;

                // Si le monstre est mort, on le retire de la file
                file = supprimerTete(file);

                printf(VERT "\t[VICTOIRE] %s(%dptV) gagne contre %s(%dptV)\t\t+%dpts\n" RESET, joueur.pseudo, joueur.nbPv, monstresTab[indexMonstresTabGroupe2[montreActuelIndex]].nom, monstresTab[indexMonstresTabGroupe2[montreActuelIndex]].pv, pointsGagnees);
                printf(BLEU "\t[INFO] %s meurt sous le coup de l'attaque\t\t+%dpts\n\n" RESET, monstresTab[indexMonstresTabGroupe2[montreActuelIndex]].nom, pointsGagnees);
            }
            // Si le monsre n'est pas mort
            else
            {
                // Ajout des points gagnés par le joueur
                pointsJoueur += pointsGagnees;

                printf(VERT "\t[VICTOIRE] %s(%dptV) gagne contre %s(%dptV)\t\t+%dpts\n" RESET, joueur.pseudo, joueur.nbPv, monstresTab[indexMonstresTabGroupe2[montreActuelIndex]].nom, monstresTab[indexMonstresTabGroupe2[montreActuelIndex]].pv, pointsGagnees);
            }
            break;
        }
        // Si le monstre gagne
        case 'M':
        {
            // Réduction des points de vie du joueur
            joueur.nbPv -= monstresTab[indexMonstresTabGroupe2[montreActuelIndex]].degats;

            // Si le joueur est mort
            if (joueur.nbPv <= 0)
            {
                // On met les points de vie du joueur à 0
                joueur.nbPv = 0;

                printf(ROUGE "\t[DEFAITE] %s(%dptV) perd l'attaque contre %s(%dptV)\n" RESET, joueur.pseudo, joueur.nbPv, monstresTab[indexMonstresTabGroupe2[montreActuelIndex]].nom, monstresTab[indexMonstresTabGroupe2[montreActuelIndex]].pv);
                printf(BLEU "[INFO] PERDU... Nombre de points acquis : %d\n" RESET, pointsJoueur);
                return;
            }
            printf(ROUGE "\t[DEFAITE] %s(%dptV) perd contre %s(%dptV)\n" RESET, joueur.pseudo, joueur.nbPv, monstresTab[indexMonstresTabGroupe2[montreActuelIndex]].nom, monstresTab[indexMonstresTabGroupe2[montreActuelIndex]].pv);
            break;
        }
        // Si égalité
        case 'E':
        {
            printf(MAGENTA "\t[EGALITE] Aucun de %s(%dptV) et %s(%dptV) ne gagne l'attaque\n" RESET, joueur.pseudo, joueur.nbPv, monstresTab[indexMonstresTabGroupe2[montreActuelIndex]].nom, monstresTab[indexMonstresTabGroupe2[montreActuelIndex]].pv);
            break;
        }
        }

        // Si le monstre n'est pas mort, on le retire de la file et on le remet à la fin
        if (tete == tete(file))
        {
            file = supprimerTete(file);
            file = ajouter(tete, file);
        }
    }
}

void createNewGameDisplay(int *nbJoueurs, Joueur **joueursTab, Monstre monstresTab[], int indexMonstresTabGroupe1[], int indexMonstresTabGroupe2[], int nbMonstresGroupe1, int nbMonstresGroupe2)
{
    char pseudoJoueur[50];
    clearScreen();
    int index, trouve;
    printf(GRAS VERT "▁ ▂ ▄ ▅ ▆ ▇ █ Créer une nouvelle partie █ ▇ ▆ ▅ ▄ ▂ ▁\n\n" RESET);
    printf(JAUNE "[ACTION] Entrer votre pseudo > " RESET);
    scanf("%s", pseudoJoueur);
    index = rechercheDico(pseudoJoueur, *joueursTab, *nbJoueurs, &trouve);
    if (trouve == 0)
    {
        // charger les données du joueur
        Joueur joueur;
        strcpy(joueur.pseudo, pseudoJoueur);
        joueur.nbPv = 20;
        joueur.nbDegats = 1;
        joueur.nbParties = 0;
        joueur.scores = NULL;
        strcpy(joueur.armes, "PFC");

        // realloc joueursTab
        *nbJoueurs = *nbJoueurs + 1;
        *joueursTab = (Joueur *)realloc(*joueursTab, (*nbJoueurs) * sizeof(Joueur));
        if (joueursTab == NULL)
        {
            printf("Erreur d'allocation mémoire\n");
            return;
        }

        (*joueursTab)[*nbJoueurs - 1] = joueur;
        game((*joueursTab)[*nbJoueurs - 1], *joueursTab, monstresTab, indexMonstresTabGroupe1, indexMonstresTabGroupe2, nbMonstresGroupe1, nbMonstresGroupe2);
    }
    else
    {
        game((*joueursTab)[index], *joueursTab, monstresTab, indexMonstresTabGroupe1, indexMonstresTabGroupe2, nbMonstresGroupe1, nbMonstresGroupe2);
    }
}

char determinerGagnant(char armeJoueur, char armeMonstre)
{
    if (armeJoueur == armeMonstre)
    {
        return 'E';
    }
    if (armeJoueur == '#')
    {
        return 'P';
    }
    if (armeMonstre == '#')
    {
        return 'M';
    }
    if (armeJoueur == 'O')
    {
        return 'M';
    }
    if (armeMonstre == 'O')
    {
        return 'P';
    }
    if (armeJoueur == 'P' && armeMonstre == 'C')
    {
        return 'P';
    }
    if (armeJoueur == 'C' && armeMonstre == 'F')
    {
        return 'P';
    }
    if (armeJoueur == 'F' && armeMonstre == 'P')
    {
        return 'P';
    }
    if (armeMonstre == 'P' && armeJoueur == 'C')
    {
        return 'M';
    }
    if (armeMonstre == 'C' && armeJoueur == 'F')
    {
        return 'M';
    }
    if (armeMonstre == 'F' && armeJoueur == 'P')
    {
        return 'M';
    }
    return 'E';
}

Monstre *loadMonstres(char *filenom, int *nbMonstres, int *indexMonstresGroupe1, int *indexMonstresGroupe2, int *nbMonstresGroupe1, int *nbMonstresGroupe2)
{
    FILE *file = fopen(filenom, "r");
    if (file == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier\n");
        return NULL;
    }

    // Lecture du nombre de monstres (première ligne)
    fscanf(file, "%d", nbMonstres);

    if (*nbMonstres < 1)
    {
        printf("Erreur lors de la lecture du nombre de monstres\n");
        fclose(file);
        return NULL;
    }

    // Allocation dynamique pour le tableau des monstres
    Monstre *monstres = malloc(*nbMonstres * sizeof(Monstre));
    if (monstres == NULL)
    {
        printf("Erreur d'allocation mémoire\n");
        fclose(file);
        return NULL;
    }

    // Lecture des monstres
    for (int i = 0; i < *nbMonstres; i++)
    {
        Monstre *monster = &monstres[i];
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
            monster->nom[j] = c;
            j++;
            fscanf(file, "%c", &c);
        }
        // Ajout du caractère de fin de chaîne
        monster->nom[j] = '\0';

        // Vérification de la lecture du nom
        if (j == 0)
        {
            printf("Erreur lors de la lecture du nom du monstre\n");
            fclose(file);
            return NULL;
        }

        fscanf(file, "%d,%d,%d,%d",
               &monster->niveau,
               &monster->pv,
               &monster->degats,
               &monster->type);

        // Allocation dynamique pour les armes du monstre
        switch (monster->niveau)
        {
        case 1:
            monster->nbArmes = 4;
            monster->armes = malloc(monster->nbArmes * sizeof(char));

            monster->armes = "PFCO";
            break;
        case 2:
            monster->nbArmes = 3;
            monster->armes = malloc(monster->nbArmes * sizeof(char));

            monster->armes = "PFC";
            break;
        case 3:
            monster->nbArmes = 5;
            monster->armes = malloc(monster->nbArmes * sizeof(char));

            monster->armes = "PFCO#";
            break;
        default:
            printf("Niveau de monstre invalide\n");
            fclose(file);
            return NULL;
        }

        switch (monster->type)
        {
        case 1:
            *nbMonstresGroupe1++;
            indexMonstresGroupe1 = realloc(indexMonstresGroupe1, *nbMonstresGroupe1 * sizeof(int));
            indexMonstresGroupe1[*nbMonstresGroupe1 - 1] = i;

            break;
        case 2:
            *nbMonstresGroupe2++;
            indexMonstresGroupe2 = realloc(indexMonstresGroupe2, *nbMonstresGroupe2 * sizeof(int));
            indexMonstresGroupe2[*nbMonstresGroupe2 - 1] = i;

            break;
        }
    }
    fclose(file);
    return monstres;
}

/*
//Fonction de test pour afficher les monstres chargés depuis le fichier

void showEveryMonstres(Monstre *monstres, int nbMonstres)
{
    for (int i = 0; i < nbMonstres; i++)
    {
        printf("Nom : %s\n", monstres[i].nom);
        printf("Niveau : %d\n", monstres[i].niveau);
        printf("Points de vie : %d\n", monstres[i].pv);
        printf("Dégâts : %d\n", monstres[i].degats);
        printf("Nombre d'armes : %d\n", monstres[i].nbArmes);
        printf("Armes : ");
        for (int j = 0; j < monstres[i].nbArmes; j++)
            printf("%c ", monstres[i].armes[j]);
        printf("\n\n");
    }
}
*/

// Fonction pour charger les joueurs depuis un fichier binaire
Joueur *loadJoueursFromBinary(char *filenom, int *nbJoueurs)
{
    // Ouvre le fichier binaire en mode lecture
    FILE *file = fopen(filenom, "rb");

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
        file = fopen(filenom, "wb");
        if (file == NULL)
        {
            printf("Erreur lors de la création du fichier\n");
            return NULL;
        }

        // On écrit le nombre de joueurs (0) dans le fichier
        *nbJoueurs = 0;
        fwrite(nbJoueurs, sizeof(int), 1, file);

        // On ferme le fichier
        fclose(file);

        return NULL;
    }

    // Lecture du nombre de joueurs
    fread(nbJoueurs, sizeof(int), 1, file);

    // Vérification de la lecture du nombre de joueurs
    if (*nbJoueurs < 0)
    {
        printf("Erreur lors de la lecture du nombre de joueurs\n");
        fclose(file);
        return NULL;
    }

    // Allocation dynamique pour le tableau des joueurs
    Joueur *joueurs = malloc(*nbJoueurs * sizeof(Joueur));
    if (joueurs == NULL)
    {
        printf("Erreur d'allocation mémoire\n");
        fclose(file);
        return NULL;
    }

    // Lecture des données de chaque joueur
    for (int i = 0; i < *nbJoueurs; i++)
    {
        Joueur *joueur = &joueurs[i];

        // Lecture du pseudo
        fread(joueur->pseudo, sizeof(char), 50, file);

        // Lecture des caractéristiques simples
        fread(&joueur->nbPv, sizeof(int), 1, file);
        fread(&joueur->nbDegats, sizeof(int), 1, file);
        fread(&joueur->nbParties, sizeof(int), 1, file);

        // Allocation dynamique pour les scores
        joueur->scores = malloc(joueur->nbParties * sizeof(int));

        // Vérification de l'allocation
        if (joueur->scores == NULL)
        {
            printf("Erreur d'allocation mémoire pour les scores\n");
            fclose(file);
            return NULL;
        }

        // Lecture des scores
        fread(joueur->scores, sizeof(int), joueur->nbParties, file);

        // Lecture des armes
        fread(joueur->armes, sizeof(char), 5, file);
    }
    fclose(file);
    return joueurs;
}

void saveJoueursToBinary(char *filenom, Joueur *joueurs, int nbJoueurs)
{
    // Ouvre le fichier binaire en mode écriture
    FILE *file = fopen(filenom, "wb");
    if (file == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier\n");
        return;
    }

    // Écrit le nombre de joueurs en premier
    fwrite(&nbJoueurs, sizeof(int), 1, file);

    // Parcourt chaque joueur et écrit ses données
    for (int i = 0; i < nbJoueurs; i++)
    {
        Joueur *joueur = &joueurs[i];

        // Écrit le pseudo
        fwrite(joueur->pseudo, sizeof(char), 50, file);

        // Écrit les caractéristiques simples
        fwrite(&joueur->nbPv, sizeof(int), 1, file);
        fwrite(&joueur->nbDegats, sizeof(int), 1, file);
        fwrite(&joueur->nbParties, sizeof(int), 1, file);

        // Écrit les scores
        fwrite(joueur->scores, sizeof(int), joueur->nbParties, file);

        // Écrit les armes
        fwrite(joueur->armes, sizeof(char), 5, file);
    }
    fclose(file);
}

void ShowJoueur(Joueur *JoueursTab[], int currentIndex, int nbJoueurs)
{
    if (currentIndex == nbJoueurs)
        return;

    printf("Pseudo : %s\n", JoueursTab[currentIndex]->pseudo);
    printf("Points de vie : %d\n", JoueursTab[currentIndex]->nbPv);
    printf("Dégâts : %d\n", JoueursTab[currentIndex]->nbDegats);
    printf("Nombre de jeux : %d\n", JoueursTab[currentIndex]->nbParties);
    printf("Scores : ");
    for (int j = 0; j < JoueursTab[currentIndex]->nbParties; j++)
        printf("%d ", JoueursTab[currentIndex]->scores[j]);
    printf("\n");
    printf("Armes : %s\n\n", JoueursTab[currentIndex]->armes);

    ShowJoueur(JoueursTab, currentIndex + 1, nbJoueurs);
}

void ShowAllJoueurs(Joueur *JoueursTab[], int nbJoueurs)
{
    ShowJoueur(JoueursTab, 0, nbJoueurs);
}

void showAllbybiggestScores(Joueur *JoueursTab[], int nbJoueurs)
{
   int max = 0;
    for (int i = 1; i < nbJoueurs; i++)
    {
        if (JoueursTab[i]->scores > JoueursTab[max]->scores)
        {
            max = i;
        }
    }
    printf("Pseudo : %s\n", JoueursTab[max]->pseudo);
    printf("Points de vie : %d\n", JoueursTab[max]->nbPv);
    printf("Dégâts : %d\n", JoueursTab[max]->nbDegats);
    printf("Nombre de jeux : %d\n", JoueursTab[max]->nbParties);
    printf("Scores : ");
    for (int j = 0; j < JoueursTab[max]->nbParties; j++)
        printf("%d ", JoueursTab[max]->scores[j]);
    printf("\n");
    printf("Armes : %s\n\n", JoueursTab[max]->armes);
}

int biggestScore(Joueur *JoueursTab[], int nbJoueurs)
{
    int max = 0;
    for (int i = 1; i < nbJoueurs; i++)
    {
        if (JoueursTab[i]->scores > JoueursTab[max]->scores)
        {
            max = i;
        }
    }
    return max;
}

int MinScore(Joueur *JoueursTab[], int nbJoueurs)
{
    int min = 0;
    for (int i = 1; i < nbJoueurs; i++)
    {
        if (JoueursTab[i]->scores < JoueursTab[min]->scores)
        {
            min = i;
        }
    }
    return min;
}


void ShowJoueurPreciseStats(Joueur *JoueursTab[], int nbJoueurs)
{
    char pseudoJoueur[50];
    int trouve;
    printf("Entrez le pseudo du joueur:  ");
    scanf("%s", pseudoJoueur);
    int index = rechercheDico(pseudoJoueur, JoueursTab, nbJoueurs, &trouve);
    if (trouve == 0)
    {
        printf("Joueur non trouvé\n");
    }
    else
    {
        printf("Pseudo : %s\n", JoueursTab[index]->pseudo);
        printf("Points de vie : %d\n", JoueursTab[index]->nbPv);
        printf("Dégâts : %d\n", JoueursTab[index]->nbDegats);
        printf("Nombre de jeux : %d\n", JoueursTab[index]->nbParties);
        printf("Scores : ");
        for (int j = 0; j < JoueursTab[index]->nbParties; j++)
            printf("%d ", JoueursTab[index]->scores[j]);
        printf("%d",MinScore(JoueursTab, nbJoueurs));
        printf("%d",biggestScore(JoueursTab, nbJoueurs));
        printf("\n");
        printf("Armes : %s\n\n", JoueursTab[index]->armes);
    }
}

void global(void)
{
    Boolean quit = False;
    int choice, nbJoueurs, nbMonstres, *indexMonstresGroupe1, *indexMonstresGroupe2;
    int nbMonstresGroupe1, nbMonstresGroupe2;
    Joueur *joueursTab = loadJoueursFromBinary("game.dat", &nbJoueurs);
    Monstre *monstres = loadMonstres("monstres.txt", &nbMonstres, indexMonstresGroupe1, indexMonstresGroupe2, &nbMonstresGroupe1, &nbMonstresGroupe2);

    while (!quit)
    {
        clearScreen();
        printf(GRAS VERT "\n\t▁ ▂ ▄ ▅ ▆ ▇ █  MENU  █ ▇ ▆ ▅ ▄ ▂ ▁\n\n\n" RESET);
        printf("[1] Jouer une partie prédéfinie\n");
        printf("[2] Créer une nouvelle partie\n");
        printf("[3] Afficher la liste des joueurs triée par nom\n");
        printf("[4] Afficher la liste des joueurs triée par meilleur score\n");
        printf("[5] Afficher les statistiques d'un joueur précis\n");

        printf("[9] Quitter et sauvegarder\n\n");
        printf("Votre choix > ");
        // showEveryMonstres(monstres, nbMonstres);
        showAllJoueurs(joueursTab, nbJoueurs);
        // printf("Nombre de joueurs : %d\n", nbJoueurs);
        scanf(" %d", &choice);
        switch (choice)
        {
        case 1:
            // existingGameDisplay(&joueursTab, &nbJoueurs, monstres, nbMonstres);
            break;
        case 2:
            createNewGameDisplay(&nbJoueurs, &joueursTab, monstres, indexMonstresGroupe1, indexMonstresGroupe2, nbMonstresGroupe1, nbMonstresGroupe2);
            break;
        case 3:
            showAllJoueurs(joueursTab, nbJoueurs);
            break;
        case 4:
            showAllbybiggestScores(joueursTab, nbJoueurs);
            break;
        case 5:
            ShowJoueurPreciseStats(joueursTab, nbJoueurs);
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
    saveJoueursToBinary("game.dat", joueursTab, nbJoueurs);
}

void clearScreen(void)
{
    for (int i = 0; i < 20; i++)
    {
        printf("\n");
    }
}
