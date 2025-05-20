# 🧟‍♂️ Monster Clash

Monster Clash is a command-line monster battle game written in C as part of a school project. The player faces off against various groups of monsters with unique attributes.

> ⚠️ Important  
> Delete any existing `game.dat` file before running the game.  
> Bugs may occur due to unsorted data from older versions.

## 📄 Description

This project simulates battles between a player and monsters, defined via text and binary files.

### monsters.txt

This file defines the monsters used in the game. Format:
```
<number of monsters>  
<name>,<level>,<HP>,<damage>,<group>
```

Example:
```
5  
ChouinChouin,1,4,1,1  
Dragonus,3,6,2,1  
PetitePustule,2,6,1,2  
LutinCordial,2,6,1,2  
Chimere,3,6,2,2
```

### game.dat

Binary file used to store player data.

Format:
```
<number of players>  
-- structure of each player --
```

This file is automatically created and updated by the program.

## 🛠️ Compilation

To build and run the program:
```
gcc -o monster_clash main.c  
./monster_clash
```

(Replace `main.c` with your actual source file if needed.)

## 🏫 Context

This game was developed during a C programming course and focuses on file I/O, structures, and command-line gameplay.

## 📬 Contact

Email: exosky.dev@gmail.com <br>
Twitter/X: https://x.com/exosky12_
