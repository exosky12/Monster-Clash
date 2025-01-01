# SAE1.02

Devoir jeu en C

## Description  ```monsters.dat```

```
5
ChouinChouin,1,4,1
Dragonus,3,6,2
PetitePustule,2,6,1
LutinCordial,2,6,1
Chimere,3,6,2
```

Ici le fichier ```monsters.dat``` suis le format suivant:

```
<nombre de monstres>
<monstre1>,<niveau>,<nombre pv>,<nombre dégâts>
<monstre2>,<niveau>,<nombre pv>,<nombre dégâts>
...
```

## Description ```game.dat```

Fichier binaire contenant les données des joueurs

Le format ce présente comme suit:

```
<nombre de joueurs>
--struture de chaque joueur--
```

## Reste à faire

- Fonction combat à travers les niveaux
- Fonction d'affichage des statistiques des joueurs (trié par nom/score)