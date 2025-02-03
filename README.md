# Monster Clash (JEU EN LIGNE DE COMMANDES)

(ce projet est un projet scolaire dans lequel on devait créer un jeu en C en ligne de commandes qui faisait s'affronter un joueur contre différents groupes de monstres avec différentes spécificités)

# ⚠ Suppimer ancien `game.dat` par précaution

Bug pourrait survenir car non trié du à ancienne version

Devoir jeu en C

## Description `monsters.txt`

```
5
ChouinChouin,1,4,1,1
Dragonus,3,6,2,1
PetitePustule,2,6,1,2
LutinCordial,2,6,1,2
Chimere,3,6,2,2
```

Ici le fichier `monsters.txt` suis le format suivant:

```
<nombre de monstres>
<monstre1>,<niveau>,<nombre pv>,<nombre dégâts>,<groupe du monstre>
<monstre2>,<niveau>,<nombre pv>,<nombre dégâts>,<groupe du monstre>
...
```

## Description `game.dat`

Fichier binaire contenant les données des joueurs

Le format ce présente comme suit:

```
<nombre de joueurs>
--struture de chaque joueur--
```
