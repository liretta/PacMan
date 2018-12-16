#include "stdafx.h"
#include "Defines.h"
#include "ObjectPacman.h"
#include "GameObject.h"

ObjectPacman::ObjectPacman()
{};

//   FUNCTION: StartInitialize(Point startBoxPosition)
//
//   PURPOSE: initialize start PacMan's position and direction
//
//   COMMENTS: 
//		start pacman position determined in Board, when initialized all game map.
//		then that start point must be passed to this function for initialize start position.
//		Start direction always is up
//

void ObjectPacman::StartInitialize(Point startBoxPosition)
{
	mpCurBox = startBoxPosition;
	int top = startBoxPosition.y*BOXSIZE;
	int left = startBoxPosition.x*BOXSIZE;
	int right = left + BOXSIZE;
	int bottom = top + BOXSIZE;
	mpCurPoint = { top, left, right, bottom };
	mpCurDirection = UP;

};

ObjectPacman::~ObjectPacman() {};

//   FUNCTION: Draw(HDC hDC)
//
//   PURPOSE: Draw PacMan's figure on passed device (HDC)
//
//   COMMENTS: 
//		function gets some divece context
//		then on this divice will be drawing pacman's figure: yellow round and black mouth
//		all coordinates are converted from user-coordinate to standard
//
void ObjectPacman::Draw(HDC hDC)
{
	HDC hdc = hDC;
	HBRUSH hBr;
	HBRUSH hOldBr;

	hBr = CreateSolidBrush(YELLOW);
	hOldBr = (HBRUSH)SelectObject(hdc, hBr);

	int x = mpCurBox.x*BOXSIZE, 
		y = mpCurBox.y*BOXSIZE,
		x2 = x+BOXSIZE,
		y2 = y+BOXSIZE;
	
	Ellipse(hdc, x, y, x2, y2);
	SelectObject(hdc, hOldBr);
	DeleteObject(hBr);

	//poligon - pacman's mouth 
	//central point
	int x1 = x + BOXSIZE / 2;
	int y1 = y + BOXSIZE / 2;
	x2 = 0;
	y2 = 0;
	int x3, y3; //loweer border of pacman's mouth

	switch (mpCurDirection)
	{
	case LEFT:
	{
		x2 = x;
		y2 = y;
		x3 = x2;
		y3 = y + BOXSIZE;
	}
		break;
	case RIGHT:
	{
		x2 = x + BOXSIZE;
		y2 = y;
		x3 = x2;
		y3 = y + BOXSIZE;
	}
		break;
	case UP:
	{
		x2 = x;
		y2 = y;
		x3 = x2+BOXSIZE;
		y3 = y;	
	}
		break;
	case DOWN:
	{
		x2 = x;
		y2 = y+BOXSIZE;
		x3 = x+BOXSIZE;
		y3 = y2;
	}
		break;
	default:
		break;
	}

	POINT poly[3] = { { x1, y1 },{ x2,y2 },{ x3,y3 } };

	hBr = CreateSolidBrush(BLACK);
	hOldBr = (HBRUSH)SelectObject(hdc, hBr);
	Polygon(hdc, poly, 3);

	SelectObject(hdc, hOldBr);
	DeleteObject(hBr);
};

//   FUNCTION: (Objects NextObject, Point& NewBoxPosition, unsigned int &mCurTreasureCount, bool &GameStatus, GamerStatus &gamer)
//
//   PURPOSE: try to move PacMan. always 1 step in the current direction
//
//   COMMENTS: 
//		return true if position could be changed and we need to rewrite mpBoard. Return false if pacman can't move
//1. check, what object there are in next ghost's position in current directions
//2. if there is threasure in the next position: decrease qountity of threasure by one and change pacman's coordinate to the next box
//new ghost's box in mpBoard must assigned as ghost+threasure 
//it is necessary that the ghost does not eat the treasure and we could draw it after the ghost leaves
//3. if there is ghost1 or ghost2, ghost+treasure in the next position - change game and gamer status. Game is over, gamer is loser
//4. if there is start-point in the next position, move ghost to another side of this line - one step to exit point
//5. if there is exit-point in the next position, check qountity of threasure. If there aren't any threaure on game map, 
//games is winner, game is over. Else - move ghost to another side of this line - one step to start point
//6. if wall - just update window
//
bool ObjectPacman::Move(Objects NextObject, Point& NewBoxPosition, unsigned int &mCurTreasureCount, bool &GameStatus, GamerStatus &gamer)
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
		mCurTreasureCount = (mCurTreasureCount != 0) ? --mCurTreasureCount : 0;
		mpCurBox = NewBoxPosition;//location objects on board 
		mpCurPoint.top = NewBoxPosition.y*BOXSIZE; //current coordinate in pixel
		mpCurPoint.left = NewBoxPosition.x*BOXSIZE;
		mpCurPoint.right = mpCurPoint.left + BOXSIZE;
		mpCurPoint.bottom = mpCurPoint.top + BOXSIZE;
		return true;
	}
		break;
	case GHOST1:
	{	
		gamer = LOSER;
		GameStatus = false;
		return false;
	}
		break;
	case GHOST2:
	{
		gamer = LOSER;
		GameStatus = false;
		return false;
	}
		break;
	case WALL:
		return false;
		break;
	case GHOST1TREASURE:
	{
		gamer = LOSER;
		GameStatus = false;
		return false;
	}
		break;
	case GHOST2TREASURE:
	{
		gamer = LOSER;
		GameStatus = false;
		return false;
	}
		break;
	case STARTPOINT:
	{
		//pacman stay on same line, but moving to the another side of this line,
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
		if (mCurTreasureCount == 0)
		{
			gamer = WINNER;
			GameStatus = false;
			return false;
		}
		else
		{
			mpCurBox.x = 1;//pacman stay on same line, but moving to the another side of this line,
			mpCurPoint.top = mpCurBox.y*BOXSIZE; //current coordinate in pixel
			mpCurPoint.left = mpCurBox.x*BOXSIZE;
			mpCurPoint.right = mpCurPoint.left + BOXSIZE;
			mpCurPoint.bottom = mpCurPoint.top + BOXSIZE;
			return true;
		}
	}
		break;
	default:
		break;
	}
	return false;
}
;

void ObjectPacman::SetNewDirection(Direction newDirect)
{
	mpCurDirection = newDirect;
};

