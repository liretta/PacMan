#include "stdafx.h"
#include "Defines.h"
#include "Ghost.h"
#include "GameObject.h"

//
ObjectGhost::ObjectGhost()
{};

//   FUNCTION: StartInitialize(Point startBoxPosition)
//
//   PURPOSE: initialize start ghost's position and direction
//
//   COMMENTS: 
//		start ghost position determined in Board, when initialized all game map.
//		then that start point must be passed to this function for initialize start position.
//		Start direction is randomly selected
//
void ObjectGhost::StartInitialize(Point startBoxPosition)
{
	mpCurBox = startBoxPosition;
	int top = startBoxPosition.y*BOXSIZE;
	int left = startBoxPosition.x*BOXSIZE;
	int right = left + BOXSIZE;
	int bottom = top + BOXSIZE;
	mpCurPoint = { top, left, right, bottom };
	mpCurDirection = DOWN;
	//int tempDirection = rand() % 4; //randrom direction for chost
	//mpCurDirection = (Direction) tempDirection;
};

ObjectGhost::~ObjectGhost() {};

//   FUNCTION: Draw(HDC hDC)
//
//   PURPOSE: Draw chost-figure on passed device (HDC)
//
//   COMMENTS: 
//		function gets some divece context
//		then on this divice will be drawing ghost figure: round red head and 2 red legs
//		all coordinates are converted from user to standard
//
void ObjectGhost::Draw(HDC hDC)
{
	HDC hdc = hDC;
	HBRUSH hBr;
	HBRUSH hOldBr;

	hBr = CreateSolidBrush(RED);
	hOldBr = (HBRUSH)SelectObject(hdc, hBr);
	

	int x = mpCurBox.x*BOXSIZE, 
		y = mpCurBox.y*BOXSIZE,
		x_2= x+BOXSIZE,
		y_2 = y+BOXSIZE;

	Ellipse(hdc, x, y, x_2, y_2);

	//bottom square for legs
	Rectangle(hdc, x, y + BOXSIZE / 2, x + BOXSIZE, y + BOXSIZE);
	SelectObject(hdc, hOldBr);
	DeleteObject(hBr);

	//small rectangles for legs
	int x1, y1;
	int x2, y2;
	hBr = CreateSolidBrush(BLACK);
	hOldBr = (HBRUSH)SelectObject(hdc, hBr);

	x1 = x + BOXSIZE / 5;
	y1 = y + BOXSIZE / 4 * 3;
	x2 = x1 + BOXSIZE / 5;
	y2 = y + BOXSIZE;
	Rectangle(hdc, x1, y1, x2, y2);

	x1 = x + BOXSIZE / 5 * 3;
	y1 = y + BOXSIZE / 4 * 3;
	x2 = x1 + BOXSIZE / 5;
	y2 = y + BOXSIZE;
	Rectangle(hdc, x1, y1, x2, y2);

	SelectObject(hdc, hOldBr);
	DeleteObject(hBr);
};


//   FUNCTION: Move(Objects NextObject, Point& NewBoxPosition, bool &GameStatus, GamerStatus &gamer)
//
//   PURPOSE: try to move ghost. 1 step in the current direction
//
//   COMMENTS: 
//		return true if position could be changed. Return false if ghost can't move
		//1. check, what object there are in next ghost's position in current directions
		//2. if there is threasure in the next position : change ghost coordinate to the next box
		//new ghost's box in mpBoard must assigned as ghost+threasure 
		//it is necessary that the ghost does not eat the treasure and we could draw it after the ghost leaves
		//3. if there is ghost1 or ghost2, ghost+treasure in the next position - ignore, update window withour change position
		//4. if there is start-point in the next position, move ghost to another side of this line - one step to exit point
		//5. if there is exit-point in the next position, move ghost to another side of this line - one step to start point
		//6. if wall - just update window
		//7. if pacman = change game and gamer status. Game is over, gamer is loser
//
bool ObjectGhost::Move(Objects NextObject, Point& NewBoxPosition, bool &GameStatus, GamerStatus &gamer)
{
	
	switch (NextObject)
	{
	case EMPTY:
	{
		mpCurBox = NewBoxPosition;//location objects on board 
		mpCurPoint.top = NewBoxPosition.y*BOXSIZE; //current coordinate in pixel
		mpCurPoint.left = NewBoxPosition.x*BOXSIZE;
		mpCurPoint.right = mpCurPoint.left + BOXSIZE;
		mpCurPoint.bottom = mpCurPoint.top + BOXSIZE;
		return true;
	}
	break;
	case TREASURE:
	{
		mpCurBox = NewBoxPosition;//location objects on board 
		mpCurPoint.top = NewBoxPosition.y*BOXSIZE; //current coordinate in pixel
		mpCurPoint.left = NewBoxPosition.x*BOXSIZE;
		mpCurPoint.right = mpCurPoint.left + BOXSIZE;
		mpCurPoint.bottom = mpCurPoint.top + BOXSIZE;
		return true;
	}
	break;
	case GHOST1:
		return false;
	break;
	case GHOST2:
		return false;
	break;
	case WALL:
		return false;
	break;
	case GHOST1TREASURE:
		return false;
	break;
	case GHOST2TREASURE:
		return false;
	break;
	case STARTPOINT:
	{
		//ghost stay on the same line, but moving to the another side of this line,
		mpCurBox.x = BOARDWIDTH - 2;
		mpCurPoint.top = mpCurBox.x*BOXSIZE; //current coordinate in pixel
		mpCurPoint.left = mpCurBox.y*BOXSIZE;
		mpCurPoint.right = mpCurPoint.left + BOXSIZE;
		mpCurPoint.bottom = mpCurPoint.top + BOXSIZE;
		return true;
	}
	break;
	case EXITPOINT:
	{
		mpCurBox.x = 1; //ghost stay on same line, but moving to the another side of this line,
		mpCurPoint.top = mpCurBox.x*BOXSIZE; //current coordinate in pixel
		mpCurPoint.left = mpCurBox.y*BOXSIZE;
		mpCurPoint.right = mpCurPoint.left + BOXSIZE;
		mpCurPoint.bottom = mpCurPoint.top + BOXSIZE;
		return true;
	}
	break;
	case PACMAN:
	{
		gamer = LOSER;
		GameStatus = false;
		return false;
	}
	default:
		break;
	}
	return false;
}



