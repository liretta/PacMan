# About PacMan
It is a simple version of game PacMan (1 lvl) with using WIN API. 

## How it works

The player controls the PacMan via arrows. The goal is to collect all treasure on game board, to avoid monsters, and ton die .
The game would end when PacMan will collect all treasure and reach the exit, or when one of the monsters will touch PacMan.

# Instalation instruction

1. Download archive **Release.rar**.
2. There ia exe-file, so you may receive the warning message from your browser or firewall. Ignore it =) 
3. Open the folder.
4. Run **PacMan.exe**

**Profit!**
<hr>

# Exsample of interface
![1](https://user-images.githubusercontent.com/38506033/61370073-363e6700-a89a-11e9-9e39-cd62d8d861fb.JPG)

![2](https://user-images.githubusercontent.com/38506033/61370135-5c640700-a89a-11e9-89e1-6fc9dce78d4c.JPG)

![3](https://user-images.githubusercontent.com/38506033/61370149-6980f600-a89a-11e9-86fc-8aa03ab91de2.JPG)

# Features of implementation

## Game Board
Game board is a table 19X20. Each box on the table has size BOXSIZE in pixel (look #define) 
Game board emplemented as two-demensional dynamic array. In the Array first demensional (i-loop) is COLUMNS on board, second demensional (j-loop) is LINES on board
Board keeps all game objects (PacMan, ghosts), and has methods for drawing the PacMan, ghosts and treasure.
Also there are methods for moving game object.

Board has public methods: *StartGame*, *IsGameOn*, *NewLevelGenerate* (for the future implementation), *Draw* - here called all Draw-method for all game objects, *SetPacman* - set new PacMan location after moving or teleportation from enter to exit and oposit, *GetCurObject* - return object type in specified position.

## Game Object
All game objects has parent class **GameObject** with common functionality: *GeCurrentDirection*, *GetCurrentBox*, *SetNewDirection* etc. 
And virtual funtions: *StartInisialize* and *Draw*.

### PacMan
PacMan is implemented as **ObjectPacman** with public methods: *StartInitialize*, *Draw*, *SetNewDirection* and *Move*.

### Chosts
Currently game has two same ghosts with same behavior - they are moving in random direction at all time. But we have two different classes for ghosts for future improvement their movement.

## Other files

## Defines.h
There are all common macroses: struct **Point**, struct **PointTopLeft** for boxes coordinate. Also there are difined values for colors in RGB-format, and enumeration **Objects** for code reading improvements.
There also defined eenumeration for direction and for gamer status.




