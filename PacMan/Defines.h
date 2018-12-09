#pragma once
//general included files, constants and enumerations

//struct point for boxes "coordinate"
struct Point
{
	int x;
	int y;

};


//struct point for common coordinate
struct PointTopLeft
{
	int top;
	int left;
	int right;
	int bottom;

};

#define BOXSIZE 40 //size of one box (square) in pixels
#define BOARDWIDTH 19 //width of game board - how many boxes in width
#define BOARDHEIGHT 21 //height of game boxes - how many boxes in height
#define	WINDOWIDTH BOARDWIDTH * BOXSIZE //window's width in pixels
#define WINDOWHEIGHT BOARDHEIGHT *BOXSIZE //window's height in pixels
 

// rgb colors

#define WHITE RGB(255, 255, 255)
#define GREY RGB (185, 185, 185)
#define BLACK RGB (0, 0, 0)
#define RED RGB (155, 0, 0) 
#define LIGHTRED RGB (175, 20, 20)
#define GREEN RGB (0, 155, 0) 
#define LIGHTGREEN RGB (20, 175, 20)
#define BLUE RGB (0, 0, 155) 
#define LIGHTBLUE RGB (20, 20, 175)
#define YELLOW RGB (155, 155, 0) 
#define LIGHTYELLOW RGB (175, 175, 20)
#define BORDERCOLOR BLUE
#define BGCOLOR  BLACK
#define TEXTCOLOR  WHITE
#define TEXTSHADOWCOLOR GREY
#define COLORS { BLUE, GREEN, RED, YELLOW }
#define LIGHTCOLORS { LIGHTBLUE, LIGHTGREEN, LIGHTRED, LIGHTYELLOW }


//game object's enumeration
enum Objects 
{
	EMPTY, 
	PACMAN, 
	TREASURE, 
	GHOST1, 
	GHOST2, 
	WALL, 
	GOUST1TREASURE, //when ghost takes a box with treasure
	GOUST2TREASURE, //when second ghost takes a box with treasure
	STARTPOINT,
	EXITPOINT
}; 

//direction enumeration
enum Direction
{
	LEFT,
	RIGHT,
	UP,
	DOWN
};